#include <stdio.h>
#include <cblas.h>
#include <string.h>
#include <fstream>
#include <unistd.h>
#include <chrono>
#include <iostream>


double** get_matrix(std::string filename, double coeff, int* dim_x, int* dim_y)
{

    std::ifstream matrix;
    matrix.open(filename);
    matrix >> *dim_x;
    matrix >> *dim_y;

    double** arr = new double*[*dim_x];
    for (int i = 0; i < *dim_x; ++i) {
        arr[i] = new double[*dim_y];
        for (int j = 0; j < *dim_y; ++j) {
            matrix >> arr[i][j];
	    arr[i][j] = arr[i][j]*coeff;
        }
    }
    matrix.close();
    return arr;
}

double* get_vector(std::string filename, double coeff, int* dim)
{

    std::ifstream vector;
    vector.open(filename);
    vector >> *dim;

    double* arr = new double[*dim];
    for (int i = 0; i < *dim; ++i) {
            vector >> arr[i];
	    arr[i] = arr[i]* coeff;
    }
    vector.close();
    return arr;
}

void my_daxpy(double *x, double*y, int dim, double alpha)
{
    for(int i = 0; i < dim; i++){
        y[i] = y[i] + alpha * x[i];
    }

}

void print_vector(double * vec, int dim)
{
    for(int i = 0; i< dim; i++){
    	printf("%f ", vec[i]);
    }
    printf("\n");

}


int main()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    std::string vector_filename[2] = {"matrix/daxpy_small.txt", "matrix/daxpy_big.txt"};


    int dim = 0;
    double* vector_square_small_x = get_vector(vector_filename[0], 1, &dim);
    double* vector_square_small_y_my = get_vector(vector_filename[0], 2, &dim);
    double* vector_square_small_y_blas = get_vector(vector_filename[0], 2, &dim);
    
    double alpha = 3.0;


    printf("SMALL EXAMPLE TO SHOW CORRECTNESS\n");
    printf("Vector X\n");
    print_vector(vector_square_small_x, dim);
    printf("Vector Y\n");
    print_vector(vector_square_small_y_my, dim);


    my_daxpy(vector_square_small_x, vector_square_small_y_my, dim, alpha);
    cblas_daxpy(dim, alpha, vector_square_small_x, 1, vector_square_small_y_blas, 1);

    printf("Result basic:\n");
    print_vector(vector_square_small_y_my, dim);
    printf("Result BLAS:\n");
    print_vector(vector_square_small_y_blas, dim);


    printf("\n BIG EXAMPLE\n");

    double* vector_square_big_x = get_vector(vector_filename[1], 1, &dim);
    double* vector_square_big_y_my = get_vector(vector_filename[1], 2, &dim);
    double* vector_square_big_y_blas = get_vector(vector_filename[1], 2, &dim);


    auto t1 = high_resolution_clock::now();
    my_daxpy(vector_square_big_x, vector_square_big_y_my, dim, alpha);

    auto t2 = high_resolution_clock::now();

    auto t3 = high_resolution_clock::now();
    cblas_daxpy(dim, alpha, vector_square_big_x, 1, vector_square_big_y_blas, 1);
    auto t4 = high_resolution_clock::now();
    
    duration<double, std::milli> ms_double_1 = t2 - t1;
    duration<double, std::milli> ms_double_2 = t4 - t3;
    
    std::cout << "BASIC TIME:" << ms_double_1.count() << "ms\n";
    std::cout << "BLAS TIME:" << ms_double_2.count() << "ms\n";


    return 0;

}
