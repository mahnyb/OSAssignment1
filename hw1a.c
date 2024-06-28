// Mahny Barazandehtar - 20210702004 - CSE 331 - Assignment 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>	
#include <sys/types.h> 
#include <time.h>
#include <sys/wait.h>

#define N 800 // the matrix size

void randomMatrixGenerator(int matrix[N][N]){
        
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            matrix[i][j] = rand() % (10 + 1); 
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

    // initializes the matrices to zero
    int matrix1[N][N] = {0};
    int matrix2[N][N] = {0};
    int result[N][N] = {0};
    
    // generate two random matrices
    randomMatrixGenerator(matrix1);
    randomMatrixGenerator(matrix2);
    

    pid_t child_pid;
    int child_status;

    for (int i = 0; i < N; i++){
        
        child_pid = fork();

        switch (child_pid){
        
        case -1: // checks if fork has failed to successfully create a child
            perror("fork");
            exit(1);
            break;
        
        case 0: // encapsulate every row multiplication into a single child process
            for (int j = 0; j < N; j++){                            
                result[i][j] = 0;           
                for (int z = 0; z < N; z++){
                    result[i][j] += matrix1[i][z] * matrix2[z][j];
                }
            }
            exit(0);
            break;

        default:
            wait(&child_pid);
            break;
        }
    }
    
    // print all the elements of the matrix multiplied
	printResult(result);

    clock_gettime(CLOCK_MONOTONIC, &end);
    
    // calculates the run time in seconds
    runtime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
      
    printf("Runtime: %f seconds\n", runtime);

    return 0;
}