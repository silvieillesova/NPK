#include <stdio.h>
#include <cblas.h>
#include <string.h>
#include <fstream>
#include <unistd.h>
#include <chrono>
#include <iostream>


double* get_matrix(std::string filename, double coeff, int* dim_x, int* dim_y)
{

    std::ifstream matrix;
    matrix.open(filename);
    matrix >> *dim_x;
    matrix >> *dim_y;

    double* arr = new double[(*dim_x) * (*dim_y)];
    for (int i = 0; i < *dim_x; ++i) {
        for (int j = 0; j < *dim_y; ++j) {
            matrix >> arr[i * (*dim_x) +j];
	    arr[i* (*dim_x) +j] = arr[i * (*dim_x) +j]*coeff;
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


void print_array(double* arr, int dim_x, int dim_y)
{
    for(int i = 0; i < dim_x; i++){
    	for(int j = 0; j < dim_y; j++){
		printf("%f ", arr[i * (dim_x) +j]);
	}
	printf("\n");

    }
}

void print_vector(double * vec, int dim)
{
    for(int i = 0; i< dim; i++){
    	printf("%f ", vec[i]);
    }
    printf("\n");

}

void my_dgemv(double* x, double* y, double* mat, int dim_x, int dim_y, double alpha, double beta)
{
//alpha*A*x + beta*y
    for(int i = 0; i < dim_x; i++){
    	double tmp =0;
	for(int j =0; j< dim_y; j++){
	    tmp = tmp + mat[i * dim_x +j]*alpha*x[j];
	}
	y[i] = beta*y[i] + tmp;
    }

}


int main()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    std::string matrix_filename[2] = {"matrix/dgemv_small_mat.txt", "matrix/dgemv_big_mat.txt"};
    std::string vector_filename[2] = {"matrix/dgemv_small_vec.txt", "matrix/dgemv_big_vec.txt"};

    int dim_x, dim_y;
    double* matrix_small = get_matrix(matrix_filename[0], 1, &dim_x, &dim_y);

    int dim = 0;
    double* vector_small_x = get_vector(vector_filename[0], 1, &dim);
    double* vector_small_y = get_vector(vector_filename[0], 2, &dim);
    double* vector_small_y_blas = get_vector(vector_filename[0], 2, &dim);
    double alpha = 2.1;
    double beta =3.21;


    printf("SMALL EXAMPLE TO SHOW CORRECTNESS\n");
    printf("Vector X\n");
    print_vector(vector_small_x, dim);
    printf("Vector Y\n");
    print_vector(vector_small_y, dim);
    printf("Matrix\n");
    print_array(matrix_small, dim_x, dim_y);

    my_dgemv(vector_small_x, vector_small_y, matrix_small, dim_x, dim_y, alpha, beta);

    cblas_dgemv(CblasRowMajor, CblasNoTrans, dim_x, dim_y, alpha, matrix_small, dim_y, vector_small_x, 1, beta, vector_small_y_blas, 1);

    printf("Result basic:\n");
    print_vector(vector_small_y, dim);
    printf("Result BLAS:\n");
    print_vector(vector_small_y_blas, dim);


    printf("\n BIG EXAMPLE\n");

    double* matrix_big = get_matrix(matrix_filename[1], 1, &dim_x, &dim_y);
    double* vector_big_x = get_vector(vector_filename[1], 1, &dim);
    double* vector_big_y = get_vector(vector_filename[1], 2, &dim);
    double* vector_big_y_blas = get_vector(vector_filename[1], 2, &dim);

    auto t1 = high_resolution_clock::now();
    my_dgemv(vector_big_x, vector_big_y, matrix_big, dim_x, dim_y, alpha, beta);
    auto t2 = high_resolution_clock::now();

    auto t3 = high_resolution_clock::now();
    cblas_dgemv(CblasRowMajor, CblasNoTrans, dim_x, dim_y, alpha, matrix_big, dim_y, vector_big_x, 1, beta, vector_big_y_blas, 1);
    auto t4 = high_resolution_clock::now();
    
    duration<double, std::milli> ms_double_1 = t2 - t1;
    duration<double, std::milli> ms_double_2 = t4 - t3;
    
    std::cout << "BASIC TIME:" << ms_double_1.count() << "ms\n";
    std::cout << "BLAS TIME:" << ms_double_2.count() << "ms\n";


    return 0;

}
