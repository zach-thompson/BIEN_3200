#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// ways of calculating the derivatives
// load_data
// numrows/cols

double** load_data(FILE* file, int numrows, int numcols);

int num_cols_in_file(FILE* file);

int num_rows_in_file(FILE* file);

double** forward_diff(double** data, int rows);

double** backward_diff(double** data, int rows);

double** central_diff(double** data, int rows);