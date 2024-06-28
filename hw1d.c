// Mahny Barazandehtar - 20210702004 - CSE 331 - Assignment 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>	
#include <sys/types.h> 
#include <time.h>

#define N 800 // the matrix size

void randomMatrixGenerator(int matrix[N][N]){    
    
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            matrix[i][j] = rand() % (10 + 1); 
        }
    }
}

void MatrixMultiplier(int matrix1[N][N], int matrix2[N][N], int result[N][N]){

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){            
            result[i][j] = 0;           
            for (int z = 0; z < N; z++){
                result[i][j] += matrix1[i][z] * matrix2[z][j];
            }
        }
    }
}

void printResult(int matrix[N][N]){
    	
        for (int i = 0; i < N; i++){
		    for(int j = 0; j < N; j++){			
			    
                printf("%d\t", matrix[i][j]);
		    }
		
		printf("\n");
	}
}

int main(){
    
    struct timespec start, end;
    double runtime;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // seeds the random number generator
    srand(time(NULL));     

    int matrix1[N][N], matrix2[N][N], result[N][N];
    
    // generate two random matrices
    randomMatrixGenerator(matrix1);
    randomMatrixGenerator(matrix2);
    
    // multiply the two random matrices and store them in the result matrix
    MatrixMultiplier(matrix1, matrix2, result);
    
    // print all the elements of the matrix multiplied
	printResult(result);

    clock_gettime(CLOCK_MONOTONIC, &end);
    
    // calculates the run time in seconds
    runtime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    
    printf("Runtime: %f seconds\n", runtime);


    return 0;
}