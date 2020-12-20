#include "linalg.h"

#include <stdio.h>
#include <string>
#include <math.h>

using namespace linalg;

template <typename T> 
Array<T>::Array(size_t dim, size_t dim_vals[]) {

    this->dim = dim;
    this->dim_vals = (size_t*) malloc(dim * sizeof(size_t));

    // calculate the size needed for the array
    size_t size = 1;
    for(int i = 0; i < dim; i++){
        this->dim_vals[i] = dim_vals[i];
        size *= dim_vals[i];
    }

    this->ptr = (T*) calloc(size, sizeof(T));
}

template <typename T> 
Array<T>::~Array(){
    free(this->ptr);
    free(this->dim_vals);
}

template <typename T> 
T Array<T>::get_element(size_t* idx){

    if(checkEntery(idx) == false){
        printf("Invalid index sequence\n");
        exit(0);                    // add my own errors
    }

    // scalar array
    if(dim == 0)
        return ptr[0];

    // map N-dim indices to 1D
    size_t id = idx[0];
    for(int i = 1; i < dim; i++)
        id = id * dim_vals[i] + idx[i];

    return ptr[id];
}

template <typename T> 
void Array<T>::set_element(size_t* idx, T val){

    if(checkEntery(idx) == false){
        printf("Invalid index sequence\n");
        return;
    }

    // scalar array
    if(dim == 0)
        ptr[0] = val;

    // map N-dim indices to 1D
    size_t id = idx[0];
    for(int i = 1; i < dim; i++)
        id = id * dim_vals[i] + idx[i];

    ptr[id] = val;
}

template <typename T> 
void Array<T>::from_list(T* list, size_t s){
    if(s != size()){
        printf("Not matching size\n");
        return;
    }

    for(int i = 0; i < size(); i++)
        ptr[i] = list[i];
}

template <typename T> 
size_t Array<T>::size(){
    size_t size = 1;
    for(size_t i=0; i<dim; i++) 
        size *= dim_vals[i];
    return size;
}

const char* indent(int s){
    std::string p = "";
    for(int i=1; i<s; i++) p += " ";
    return p.c_str();
}

template <typename T> 
void Array<T>::print(){

    std::string res = "Array(" + std::to_string(dim) + ")["; 
    // print dimensions of the array               -- string to c_string example
    if(dim == 0) res += ",";
    else{ 
        res += std::to_string(dim_vals[0]);
        for(int i=1; i<dim; i++)
            if (dim_vals[i] == 0) res += ",";
            else res += "," + std::to_string(dim_vals[i]);
    }
    res += "] :\n";
    printf("%s", res.c_str());

    // print indent '[[...['
    for (int i=0; i<dim; i++) printf("{");
    int ind = dim;

    if(dim == 0) printf("%10f \n", ptr[0]);
    else {
        size_t idx[dim] = {0};
        bool flag = false;                                  // to open another brace
        int flagc = 0;
        for(size_t i=0; i < size(); i++){
            for(int d = 1; d <= dim; d++){
                if(idx[dim - d] == dim_vals[dim - d]){
                    idx[dim - d - 1] += 1;
                    printf("}");
                    flagc++;
                    flag = true;
                    idx[dim - d] = 0;
                    continue;
                }
                break;
            }
            
            if(flag){
                for(int m = 0; m < flagc; m++) printf("\n");
                printf("%s{", indent(ind));
                flag = false;
                flagc = 0;
            }

            printf("%10.4f ", get_element(idx));
            
            idx[dim - 1] += 1;
                
        }
        for (int i=0; i<dim; i++) printf("}");
        printf("\n");
    }
}

template <typename T> 
bool Array<T>::checkEntery(size_t* idx){
    for(int i = 0; i < dim; i++)
        if (idx[i] >= dim_vals[i])
            return false;
    return true;
}

template<typename T>
Array<T> Array<T>::operator + (Array<T> const &a){

    if (a.dim != dim){
        printf("Not matching dimensions\n");
        exit(1);
    }
    for(int i=0; i<a.dim; i++){
        if(a.dim_vals[i] != dim_vals[i]){
            printf("Not matching dimensions\n");
            exit(1);
        }
    }

    Array<T> c(dim, dim_vals);
    for(int i = 0; i < size(); i++){
        c.ptr[i] = a.ptr[i] + ptr[i];
    }
    return c;
}

template<typename T>
Array<T> Array<T>::operator - (Array<T> const &a){

    if (a.dim != dim){
        printf("Not matching dimensions\n");
        exit(1);
    }
    for(int i=0; i<a.dim; i++){
        if(a.dim_vals[i] != dim_vals[i]){
            printf("Not matching dimensions\n");
            exit(1);
        }
    }

    Array<T> c(dim, dim_vals);
    for(int i = 0; i < size(); i++){
        c.ptr[i] = ptr[i] - a.ptr[i];
    }
    return c;
}

template<typename T>
Array<T> Array<T>::operator ^ (T p){

    Array<T> c(dim, dim_vals);
    for(int i = 0; i < size(); i++){
        c.ptr[i] = pow(ptr[i], p);
    }
    return c;
}

template<typename T>
Array<T> Array<T>::operator * (Array<T> const &a){

    if (a.dim != dim){
        printf("Not matching dimensions\n");
        exit(1);
    }
    for(int i=0; i<a.dim; i++){
        if(a.dim_vals[i] != dim_vals[i]){
            printf("Not matching dimensions\n");
            exit(1);
        }
    }

    Array<T> c(dim, dim_vals);
    for(int i = 0; i < size(); i++){
        c.ptr[i] = ptr[i] * a.ptr[i];
    }
    return c;
}

template<typename T>
Array<T> Array<T>::operator / (Array<T> const &a){

    if (a.dim != dim){
        printf("Not matching dimensions\n");
        exit(1);
    }
    for(int i=0; i<a.dim; i++){
        if(a.dim_vals[i] != dim_vals[i]){
            printf("Not matching dimensions\n");
            exit(1);
        }
    }

    Array<T> c(dim, dim_vals);
    for(int i = 0; i < size(); i++){
        c.ptr[i] = ptr[i] / a.ptr[i];
    }
    return c;
}