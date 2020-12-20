#pragma once

#include <stdlib.h>

namespace linalg {

    template <typename T>
    class Array {
    public:
        Array(size_t dim, size_t* dim_vals);
        ~Array();

        T get_element(size_t* idx);
        void set_element(size_t* idx, T val);
        void from_list(T* list, size_t s);

        size_t get_axis_length(size_t a);

        void printShape();
        void print();

        Array<T> operator + (Array<T> const &a);
        Array<T> operator - (Array<T> const &a);
        Array<T> operator ^ (T p);
        Array<T> operator * (Array<T> const &a);
        Array<T> operator / (Array<T> const &a);

    protected:
        size_t dim;
        size_t* dim_vals;
        T* ptr;

        size_t size();

    private:
        bool checkEntery(size_t*);
    };

    template class Array<double>;
}