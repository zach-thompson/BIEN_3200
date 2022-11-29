#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

/*
* Zach Thompson
* Date Created: 10/27/20
* Purpose: C file for utility header
*/

double* add_arrays(double* arr1, double* arr2) {
	int rows = sizeof(arr1);
	double* sum = calloc(rows, sizeof(double));
	
	for (int i = 0; i < rows; i++) {
		sum[i] = arr1[i] + arr2[i];
	}
	return sum;
}

double* subract_arrays(double* arr1, double* arr2) {
	int rows = sizeof(arr1);
	double* difference = calloc(rows, sizeof(double));

	for (int i = 0; i < rows; i++) {
		difference[i] = arr1[i] - arr2[i];
	}
	return difference;
}

double* multiply_arrays(double* arr1, double* arr2) {
	int rows = sizeof(arr1);
	double* product = calloc(rows, sizeof(double));

	for (int i = 0; i < rows; i++) {
		product[i] = arr1[i] * arr2[i];
	}
	return product;
}