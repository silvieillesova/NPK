# Setting PHONY
.PHONY: all daxpy dgemv dgemm matrix clean

# Variables 

CC=g++

# Targets needed to bring the executable up to date

all: daxpy dgemv dgemm make_matrix

daxpy: daxpy_time.cpp 
	$(CC) daxpy_time.cpp -o daxpy_time -lblas -lstdc++

dgemv: dgemv_time.cpp 
	$(CC) dgemv_time.cpp -o dgemv_time -lblas -lstdc++

dgemm: dgemm_time.cpp
	$(CC) dgemm_time.cpp -o dgemm_time -lblas -lstdc++

matrix: generate_matrices.cpp
	$(CC) generate_matrices.cpp -o gen -lstdc++

make_matrix: matrix
	mkdir -p matrix
	./gen

clean:
	rm -rf daxpy_time dgemv_time dgemm_time gen matrix

