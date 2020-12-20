#include <stdio.h>

#include "Math/linalg.h"

int main(int argc, char** argv){

    size_t dims[] = {2, 3};
    linalg::Array<double> a(2, dims);
    linalg::Array<double> b(2, dims);

    double ar[] = {1, 2, 3, 4, 5, 6};
    double br[] = {6, 5, 4, 3, 2, 1};
    a.from_list(ar, 6);
    b.from_list(br, 6);
    
    a.print();
    b.print();

    linalg::Array<double> c = a ^ 2;
    c.print();

    printf("Hello World!\n");
    return 0;
}