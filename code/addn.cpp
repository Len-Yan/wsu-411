#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// test if the # of item in list are power of 2 or not
bool testn(int n) {
	while (n >= 2) {
		n %= 2;
		if (n == 1) {
			cout << "numbers in list not power of 2 \n";
			return false;
		}
	}
	return true;
}

// make a fake list of random numbers by using rand()
int* generateInput(int n) {
	int i = 0;
	int* A;
	A = new int[n];

	while (i < n) {
		//srand()
		int r = rand();
		A[i] = r;
		i++;
	}
	//delete [] a;
	// a = NULL;
	return A;
}


// return sum from serialSum
int serialSum(int A[], int n) {
	int i = 0;
	int sum = 0;

	while (i < n) {
		sum += A[i];
		i++;
	}
	return sum;
}

//return int of sum of list
int parallelSumSimulator(int A[], int n, int p) {
	int i;
	int sum = 0;
	int step;
	int base = 2;
	//loop step needed base on p
	// base<<(step-1) = 2^step, for 1st loop, it may not work for p = 2
	// mean to have 2^(step -1 ) || base<<(step-2) here, but base<<(step-2) will error on step =1
	for (step = 1; (base << (step-1)) <= p; step++) {

		// find out how many p skip to do add base on step #
		for (i = 0; i < p; i += (base<<step-1)) {
			// this will destory the value in this original list

			if (step == 1) {
				// cause 2 << 0 = 2, but i need p0 + p1 for 1st step
				A[i] = A[i] + A[i + 1];
			}
			else {
				// 2^x = 2<< (x -1), I need 2^(step - 1) here for the skip adding value
				A[i] = A[i] + A[i + (base << (step - 2))];     
			}
			//in code test
			//cout << "A[" << i << "]: " << A[i] << "\n";
		}
	}
	sum = A[0];
	return sum;
}

//test function
// this test assume the serialSum will always get the right sum
void test() {
	int* A;
	clock_t start_t, end_t, total_t;
	int L[5] = { 8192, 524288, 2097152, 4194304, 16777216 };


	// loop mack list and test speed
	for(int i = 0; i < 5; i++) {
		// test if # of list not power of 2, break
		bool f = testn(L[i]);
		if (f == false) break;

		A = generateInput(L[i]);

		// test speed for serial
		cout << "# of number in list = "<< L[i] <<endl;
		start_t = clock();
		printf("LIST A%d: Strat Clock for Serial code = %ld\n", i, start_t);

		int sSum = serialSum(A, L[i]);
		end_t = clock();
		printf("LIST A%d: End Clock for Serial code = %ld\n", i, end_t);
		total_t = (double)(end_t - start_t);
		cout << "LIST A" << i <<": TOTAL Clock Time For sSum: " << total_t << "\n\n";


		// test speed for parallel
		start_t = clock();
		printf("LIST A%d: Strat Clock for Parallel code = %ld\n", i, start_t);

		int pSum = parallelSumSimulator(A, L[i], L[i]);
		end_t = clock();
		printf("LIST A%d: End Clock for Parallel code = %ld\n", i, end_t);
		total_t = (double)(end_t - start_t);
		cout << "LIST A" << i << ": TOTAL Clock Time For pSum: " << total_t << "\n";

		// test if sum is right
		cout << "Sum for A"<< i << " by serial sum is: " << sSum << " | Sum for A"<<i<<" by parallel sum is: " << pSum << "\n";
		if (sSum == pSum) cout << "|Test PASS|, A"<<i<<" match\n\n";
		else { cout << "|Test FAIL|, A"<<i<<" did not match\n\n"; }
		cout << "---------------------------------------------------\n";
	}

	delete[] A;
}


//run the alg
int main() {
	test();
	//int x;


	//cout << "pleace enter a number n to make n size list: ";
	//cin >> x;
	//if(testn(x) == true){

	//int* A;
	//A = generateInput(x);

	//int sSum = serialSum(A, x);
	//cout << "sSum: " << sSum << " \n";
	//int pSum = parallelSumSimulator(A, x, x);
	//cout << "pSum: " << pSum << " \n";
	//}


	cin.get();
	//delete [] A;
	return 0;
}