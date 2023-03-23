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

void my_dgemm(double* A, double* B, double *C, double alpha, double beta, int x, int y, int z)
{
//alpha*op( A )*op( B ) + beta*C

	for(int i =0; i< x; i++){
	    for(int j=0; j<z; j++){
		double tmp = 0;
	        for(int k = 0; k<y; k++){
		    tmp = tmp + alpha * A[i * y + k] * B[k*z + j];
		
		}
		C[i * x + j] = C[i * x + j]* beta +tmp;
	    
	    }
	
	}

}

int main()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    std::string matrix_filename[4] = {"matrix/dgemv_small_mat.txt", "matrix/dgemv_big_mat.txt", "matrix/dgemm.txt", "matrix/dgemm_o.txt"};

    int dim_x, dim_y, dim_z;
    double* A_small = get_matrix(matrix_filename[0], 1, &dim_x, &dim_y);
    double* B_small = get_matrix(matrix_filename[0], 2, &dim_y, &dim_z);
    double* C_small = get_matrix(matrix_filename[0], 0.1, &dim_x, &dim_z);
    double* C_small_blas = get_matrix(matrix_filename[0], 0.1, &dim_x, &dim_z);

    double alpha = 2.0;
    double beta =3.2;


    printf("SMALL EXAMPLE TO SHOW CORRECTNESS\n");
    printf("Matrix A\n");
    print_array(A_small, dim_x, dim_y);
    printf("Matrix B\n");
    print_array(B_small, dim_y, dim_z);
    printf("Matrix C\n");
    print_array(C_small, dim_x, dim_z);

    my_dgemm(A_small, B_small, C_small, alpha, beta, dim_x, dim_y, dim_z);

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, dim_x, dim_z, dim_y, alpha, A_small, dim_x, B_small, dim_y, beta, C_small_blas, dim_z );
    printf("Result basic:\n");
    print_array(C_small, dim_x, dim_z);
    printf("Result BLAS:\n");
    print_array(C_small_blas, dim_x, dim_z);

    printf("\n BIG EXAMPLE\n");

    double* A = get_matrix(matrix_filename[1], 1, &dim_x, &dim_y);
    double* B = get_matrix(matrix_filename[2], 1, &dim_y, &dim_z);
    double* C = get_matrix(matrix_filename[3], 1, &dim_x, &dim_z);
    double* C_blas = get_matrix(matrix_filename[3], 1, &dim_x, &dim_z);


    auto t1 = high_resolution_clock::now();
    my_dgemm(A,B,C,alpha, beta, dim_x, dim_y, dim_z);
    auto t2 = high_resolution_clock::now();

    auto t3 = high_resolution_clock::now();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, dim_x, dim_z, dim_y, alpha, A, dim_x, B, dim_y, beta, C_blas, dim_z );
    auto t4 = high_resolution_clock::now();
    
    duration<double, std::milli> ms_double_1 = t2 - t1;
    duration<double, std::milli> ms_double_2 = t4 - t3;
    
    std::cout << "BASIC TIME:" << ms_double_1.count() << "ms\n";
    std::cout << "BLAS TIME:" << ms_double_2.count() << "ms\n";


    return 0;

}
