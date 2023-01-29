#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <clocale>
#include <omp.h>
#include <iomanip>


using namespace std;

int main() {

	cout << "Executing" << endl << endl;

	int n = 20000;
	int* x = new int[n];
	int* y = new int[n];

	int** A = new int* [n];
	for (int i = 0; i < n; i++)
		A[i] = new int[n];

	for (int i = 0; i < n; i++) {
		x[i] = 2;
		y[i] = 0;
		for (int j = 0; j < n; j++)
			A[i][j] = 2;
	}

	double clock_start_static = clock();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			y[i] += A[i][j] * x[j];
		}
	}
	clock_start_static = clock() - clock_start_static;

	cout << "\x1B[31mTime without parallelism: \033[0m" << clock_start_static / (double)CLOCKS_PER_SEC << endl;

	double clock_start_parallel = clock();
#pragma omp parallel for schedule(static) 
	for (int i = 0; i < n; i++)
	{
		int sum = 0;
		for (int j = 0; j < n; j++)
		{
			sum += A[i][j] * x[j];
		}
		y[i] = sum;
	}
	clock_start_parallel = clock() - clock_start_parallel;

	cout << "\x1B[32mTime with parallelism: \033[0m" << clock_start_parallel / (double)CLOCKS_PER_SEC << endl;

	cout << "\x1B[33mParallelism coefficient: \033[0m" << clock_start_static / clock_start_parallel;

	cin.get();

	return 0;
}
