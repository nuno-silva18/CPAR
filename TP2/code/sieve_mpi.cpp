#include <iostream>
#include <stdio.h>
#include <time.h>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <string>
#include "mpi.h"

#define BLOCK_LOW(i,n,p) ((i)*(n)/(p))
#define BLOCK_HIGH(i,n,p) (BLOCK_LOW((i)+1,n,p)-1)
#define BLOCK_SIZE(i,n,p) (BLOCK_LOW((i)+1,n,p)-BLOCK_LOW(i,n,p))
#define BLOCK_OWNER(index,n,p) ((((p)*(index)+1)-1)/(n))

using namespace std;

#define SYSTEMTIME clock_t

void pPrimes(vector<bool> &nums) {
	cout << "The prime numbers in the range are: " << endl;

	for(long long i = 0; i < nums.size(); i++) {
		if(nums[i] == true)
			cout << " " << (i+2) << " ";
	}
	cout << endl;
}

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
	
	SYSTEMTIME init_time, fin_time;
    int rank, size, root = 0;
   
   	MPI_Init(&argc, &argv);
   	MPI_Comm_size(MPI_COMM_WORLD, &size);
   	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Parse input
	if(argc != 2) {
		cerr << "Invalid input: Expected exponent." << endl;
		return 1;
	}

	// i: Exponent for n = 2^i
	long long exp = atol(argv[1]);
	if(exp < 1) {
		cerr << "Invalid exponent: Exponent must be equal or greater than 0." << endl;
		return 1;
	}

	long long n = pow(2,exp);

	if (rank == root) {
		init_time = clock();
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
	int b_primes = cPrimes(nums);

	MPI_Reduce(&b_primes, &t_primes, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

	if (rank == root) {
        fin_time = clock();
        printf("Execution Time: %3.3f seconds\n", (double)(fin_time - init_time) / CLOCKS_PER_SEC);
        cout << b_primes << " primes" << endl;
	}

	MPI_Finalize();
}