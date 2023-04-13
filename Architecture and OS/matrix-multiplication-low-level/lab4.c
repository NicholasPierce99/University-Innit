#include <stdlib.h>
#include <stdio.h>
#include "cblas.h"
#include <math.h>
#include <x86intrin.h>
#include "c_timer.h"
#define UNROLL (4)

//initiaize matrices passed in with random values from math.h
void init_matrix(int n, double* A) {
	int i, j;
	
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			*(A + i*n + j) = rand() / (RAND_MAX * 1.0);
		}
	}
}

//unoptimized matrix multiplication
//multiplies two passed in pointers to a matrix and stores their multiplication inside of a matrix c
void unoptimized_dgemm (int n, double* A, double* B, double* C) {
	int i, j, k;
	for (i = 0; i < n; ++i) {
         for (j = 0; j < n; ++j) {
           double cij = C[i+j*n];
           for(k = 0; k < n; k++ ) {
				cij += A[i+k*n] * B[k+j*n]; 
				C[i+j*n] = cij;
           }
        }
    }
}
//giga-optimized parallel dgemm from book
void sse_dgemm (int n, double* A, double* B, double* C) {
  int i, j, k;
  for (i = 0; i < n; i+=4 )
    for (j = 0; j < n; j++ ) {
      __m256d c0 = _mm256_load_pd(C+i+j*n); /* c0 = C[i][j] */
      for(k = 0; k < n; k++ )
        c0 = _mm256_add_pd(c0, /* c0 += A[i][k]*B[k][j] */
               _mm256_mul_pd(_mm256_load_pd(A+i+k*n),
               _mm256_broadcast_sd(B+k+j*n)));
      _mm256_store_pd(C+i+j*n, c0); /* C[i][j] = c0 */
    }
}
void unroll_dgemm(int n, double* A, double* B, double* C){

    int i, j, x, k;
    for(i = 0; i < n; i+= UNROLL*4)
        for(j = 0; j < n; j++){
            __m256d c[4];
            for(x = 0; x < UNROLL; x++)
                c[x] = _mm256_load_pd(C+i+x*4+j*n);
            for(k = 0; k<n; k++){
                __m256d b = _mm256_broadcast_sd(B+k+j*n);
                for( x = 0; x < UNROLL; x++)
                    c[x] = _mm256_add_pd(c[x], _mm256_mul_pd(_mm256_load_pd(A+n*k+x*4+i), b));
            }
            for(x = 0; x <UNROLL; x++)
                _mm256_store_pd(C+i+x*4+j*n, c[x]);
        }
}
//compares the two matrices 
void compare_matrix(int n, double* A1, double* A2) {
	int i, j;
	double d1, d2;
	
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			d1 = *(A1 + i*n + j);
			d2 = *(A2 + i*n + j);
			if(fabs(d2-d1)/(d2) > 1e-6) {
				printf("error: %f(my)<>%f(dgemm)\n", d1, d2);
				exit(1);
			}
		}
	}
	printf("corect result! (╯°□°）╯︵ ┻━┻");
}
//converts resulting time to gflops
double convert_gflops(int n, double time) {
	double temp_n = 2 * pow(n, 3);
	double gflops = (temp_n / (time * pow(10, 9)));

	return gflops;
}
//main function, creates matrices, n, alpha, beta 
//runs init matrix for two matricies
//runs dgemm from book and cblas_dgemm from cblas library
int main() {
	
	//variables for matrix size and cblas dgemm
	int n = 1024;
	int i;
	int j;
	double alpha = 1.0;
	double beta = 1.0;
	
	//allocate aligned memory
	double *A; 
	posix_memalign((void**)&A, 32, n*n*sizeof(double));
	double *B;
	posix_memalign((void**)&B, 32, n*n*sizeof(double));
	double *C; 
	posix_memalign((void**)&C, 32, n*n*sizeof(double));
	double *F;
	posix_memalign((void**)&F, 32, n*n*sizeof(double));
	double *G;
	posix_memalign((void**)&G, 32, n*n*sizeof(double));
	double *H;
	posix_memalign((void**)&H, 32, n*n*sizeof(double));
	
	//initialize matrices
	init_matrix(n, A);
	init_matrix(n, B);

	//use cblas dgemm to check for correctness
	cblas_dgemm (CblasColMajor, CblasNoTrans, CblasNoTrans, n, n, n, alpha, A, n, B, n, beta, C, n);

	//get time for optimized ss dgemm
	double t0 = get_cur_time();
	sse_dgemm(n, A, B, F);
	double t1 = get_cur_time();
	double ExecutionTime_Optimized = t1 - t0; 

	printf("optimized: ");
	printf("%f", convert_gflops(n, ExecutionTime_Optimized));
	printf("\n");

	//get time for unoptimized dgemm
	double t2 = get_cur_time();
	unoptimized_dgemm(n, A, B, G);
	double t3 = get_cur_time();
	double ExecutionTime_Unoptimized = t3 - t2;

	printf("unoptimized: ");
	printf("%f",convert_gflops(n, ExecutionTime_Unoptimized));
	printf("\n");

	double t4 = get_cur_time();
	unroll_dgemm(n, A, B, H);
	double t5 = get_cur_time();
	double ExecutionTime_Unroll= t5 - t4;

	printf("unroll: ");
	printf("%f",convert_gflops(n, ExecutionTime_Unroll));
	printf("\n");

	//check for correctness
	compare_matrix(n, C, H);
	printf("\n");
	
	return 0;
}