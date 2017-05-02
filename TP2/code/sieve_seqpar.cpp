#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <iomanip>
#include <time.h>
#include <bits/stdc++.h>
#include <cstdlib>
#include <string>

using namespace std;

#define SYSTEMTIME clock_t

long long pPrimes(vector<bool> &nums) {
    cout << "The prime numbers in the range are: " << endl;

    for(long long i = 0; i < nums.size(); i++) {
        if(nums[i] == true)
            cout << " " << (i+2) << " ";
    }
    cout << endl;
}

void sieve_sequential(long long n) {
    
    SYSTEMTIME init_time, fin_time;
    init_time = clock();

    char st[100];
    vector<bool> nums(n-1, true);
    long long k = 2;
    long long smallest = 3;

    while(k*k <= n) {
        // Mark all the multiples of k between k*k and n
        for(long long i = k*k; i <=n; i += k) {
            nums[i-2] = false;
            }
            
        // Set k as the smallest unmarked number bigger than k
        for(long long i = k+1; i <= n; i++) {
            if(nums[i-2]) {
                smallest = i;
                break;
            }
        }
        k = smallest;
    }

    fin_time = clock();
    pPrimes(nums);
    sprintf(st, "Execution Time: %3.3f seconds\n", (double)(fin_time - init_time) / CLOCKS_PER_SEC);
	cout << st;
}

int sieve_parallel(long long n, int n_threads) {
    double init_time, fin_time;
    init_time = omp_get_wtime();

    char st[100];
    vector<bool> nums(n-1, true);
    long long k = 2;
    long long smallest = 3;

    while(k*k <= n) {
        // Mark all the multiples of k between k*k and n
        #pragma omp parallel for num_threads(n_threads)
        for(long long i = k*k; i <=n; i += k) {
            nums[i-2] = false;
            }
            
        // Set k as the smallest unmarked number bigger than k
        for(long long i = k+1; i <= n; i++) {
            if(nums[i-2]) {
                smallest = i;
                break;
            }
        }
        k = smallest;
    }

    fin_time = omp_get_wtime();
    pPrimes(nums);
    sprintf(st, "Execution Time: %3.3f seconds\n", (fin_time - init_time));
	cout << st;

}

int main(int argc, const char* argv[]) {
    if(argc < 3) {
        cerr << "Invalid input: Expected at least 2 arguments." << endl;
        return 1;
    }

    // Algorithm type: Sequential is 0; Parallel is 1
    int alg_type = atoi(argv[1]);
    cout << alg_type;
    if(alg_type < 0 || alg_type > 2) {
        cerr << "Invalid input: Expected algorithm type. 0 for sequential, 1 for parallel." << endl;
        return 1;
    }
    
    // Number of threads: Number of threads running in the parallel version of the algorithm
    int n_threads;
    if(alg_type == 1) {
        if(argc < 4) {
            cerr << "Invalid input: Expected at least 3 arguments when algorithm type is parallel." << endl;
            return 1;
        }
        n_threads = atoi(argv[3]);
        if(n_threads < 1) {
            cerr << "Invalid number of threads: Must be equal or greater than 1." << endl;
            return 1;
        }
    }

    // i: Exponent for n = 2^i
    long long exp = stoll(argv[2]);
    if(exp < 1) {
        cerr << "Invalid exponent: Exponent must be equal or greater than 0." << endl;
        return 1;
    }

    long long n = pow(2, exp);

    switch(alg_type) {
        case 0:
            sieve_sequential(n);
            return 0;
            break;
        case 1:
            sieve_parallel(n, n_threads);
            return 0;
            break;
    }
}