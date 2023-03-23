#include <iostream>
#include <random>
#include <fstream>
#include <ctime>



int main()
{
    int dim_x;
    int dim_y;
    double mymin = -15.0;
    double mymax = 15.0;

    std::uniform_real_distribution<double> dist(mymin, mymax);  //(min, max)
    //Mersenne Twister: Good quality random number generator
    std::mt19937 rng;
    //Initialize with non-deterministic seeds
    rng.seed(std::random_device{}());

    // DAXPY Big
    dim_y = 5000000;
    std::ofstream daxpy_big;
    daxpy_big.open("matrix/daxpy_big.txt");
    daxpy_big << dim_y << "\n";
    for(int i =0; i < dim_y; i++ ){
        daxpy_big << dist(rng) << " ";
    }

    daxpy_big.close();
    
    //DAXPY Small
    dim_y = 10;
    std::ofstream daxpy_small;
    daxpy_small.open("matrix/daxpy_small.txt");
    daxpy_small << dim_y << "\n";
    for(int i =0; i < dim_y; i++ ){
        daxpy_small << dist(rng) << " ";
    }

    daxpy_small.close();


    // DGEMV Small matrix
    dim_x = 5;
    dim_y = 5;
    std::ofstream matrix_A;
    matrix_A.open("matrix/dgemv_small_mat.txt");
    matrix_A << dim_x << " " << dim_y << "\n";
    for(int i =0; i < dim_x; i++ ){
    	for(int j = 0; j< dim_y; j++){
	matrix_A << dist(rng) << " ";
	}
	matrix_A << "\n";
    
    } 
    
    matrix_A.close();

    //DGEMV Small vector
    std::ofstream vector_A;
    vector_A.open("matrix/dgemv_small_vec.txt");
    vector_A << dim_y << "\n";
    for(int i =0; i < dim_y; i++ ){
        vector_A << dist(rng) << " ";
    }

    vector_A.close();


    // DGEMV big mat
    dim_x = 7000;
    dim_y = 5000;
    std::ofstream matrix_B;
    matrix_B.open("matrix/dgemv_big_mat.txt");
    matrix_B << dim_x << " " << dim_y << "\n";
    for(int i =0; i < dim_x; i++ ){
        for(int j = 0; j< dim_y; j++){
        matrix_B << dist(rng) << " ";
        }
        matrix_B << "\n";

    }

    matrix_B.close();

    //DGEMV big vec
    dim_y = 5000;
    std::ofstream vector_B;
    vector_B.open("matrix/dgemv_big_vec.txt");
    vector_B << dim_y << "\n";
    for(int i =0; i < dim_y; i++ ){
        vector_B << dist(rng) << " ";
    }

    vector_B.close();


    //DGEMM big matrix
    dim_x = 5000;
    dim_y = 60;
    std::ofstream matrix_C;
    matrix_C.open("matrix/dgemm.txt");
    matrix_C << dim_x << " " << dim_y << "\n";
    for(int i =0; i < dim_x; i++ ){
        for(int j = 0; j< dim_y; j++){
        matrix_C << dist(rng) << " ";
        }
        matrix_C << "\n";

    }

    matrix_C.close();

    //DGEMM output matrix
    dim_x = 7000;
    dim_y = 60;
    std::ofstream matrix_O;
    matrix_O.open("matrix/dgemm_o.txt");
    matrix_O << dim_x << " " << dim_y << "\n";
    for(int i =0; i < dim_x; i++ ){
        for(int j = 0; j< dim_y; j++){
        matrix_O << dist(rng) << " ";
        }
        matrix_O << "\n";

    }

    matrix_O.close();



    return 0;

}
