#include <iostream>
#include <stdio.h>
#include <time.h>
#include <iomanip>
#include <bits/stdc++.h>
#include <cstdlib>
#include <string>
#include <omp.h>
#include "mpi.h"

#define BLOCK_LOW(i,n,p) ((i)*(n)/(p))
#define BLOCK_HIGH(i,n,p) (BLOCK_LOW((i)+1,n,p)-1)
#define BLOCK_SIZE(i,n,p) (BLOCK_LOW((i)+1,n,p)-BLOCK_LOW(i,n,p))
#define BLOCK_OWNER(index,n,p) ((((p)*(index)+1)-1)/(n))

using namespace std;

#define SYSTEMTIME clock_t

long long cPrimes(vector<bool> &nums) {
    long long count = 0;
    
    for(long long i = 0; i < nums.size(); i++)
    {
        if (nums[i] == true)
        count++;
	}
    
    return count;
}

int main(int argc, char* argv[]) {
	
	double init_time, fin_time;
    int rank, size, root = 0;
   
   	MPI_Init(&argc, &argv);
   	MPI_Comm_size(MPI_COMM_WORLD, &size);
   	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Parse input
	if(argc != 3) {
		cerr << "Invalid input: Expected exponent and number of threads." << endl;
		return 1;
	}

	// i: Exponent for n = 2^i
	long long exp = atol(argv[1]);
	if(exp < 1) {
		cerr << "Invalid exponent: Exponent must be equal or greater than 0." << endl;
		return 1;
	}
	
	// Number of threads: Number of threads running in the parallel version of the algorithm
	int n_threads = atol(argv[2]);
	if(n_threads < 1) {
		cerr << "Invalid exponent: Exponent must be equal or greater than 1." << endl;
		return 1;
	}

	long long n = pow(2,exponent);

	if (rank == root) {
		init_time = omp_get_wtime();
	}

	long long block_size = BLOCK_SIZE(rank, n-1, size);
	long long block_low = 2 + BLOCK_LOW(rank, n-1, size);
	long long block_high = 2 + BLOCK_HIGH(rank, n-1, size);

    char st[100];
	vector<bool> nums(block_size, true);

	long long k = 2;
	long long j;
    
	while (k*k <= n) {

		if (k*k < block_low) {
			
			if (block_low % k == 0)
				j = block_low;
			else  
				j = block_low + (k - (block_low % k));

		} else {
			j = k*k;
		}
		
		// Mark all multiples of k between k*k and n:
		#pragma omp parallel for num_threads(n_threads)
		for (long long i = j; i <= block_high; i += k) {
			nums[i - block_low] = false;
		}

		// Set k as the smallest urmarked number > k:
		if (rank == root) {

			for(long long i = k + 1; i < block_high; i++) {
				if (nums[i - block_low]) {
					k = i;
					break;
				}
			}
		}

		MPI_Bcast(&k, 1, MPI_INT, root, MPI_COMM_WORLD);
	}

	int t_primes = 0;
	int b_primes = cPrimes(nums, block_size);

	MPI_Reduce(&b_primes, &t_primes, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

	if (rank == root) {
        fin_time = omp_get_wtime();
        sprintf(st, "Execution Time: %3.3f seconds\n", (fin_time - init_time));
        cout << st;
	}

	delete [] nums;
	MPI_Finalize();
}