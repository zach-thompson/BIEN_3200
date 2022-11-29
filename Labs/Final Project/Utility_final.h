#pragma once
#include <stdio.h>
#include <stdlib.h>

double** load_data(FILE* file, int numrows, int numcols); // Loads a file into a 2D array

int num_cols_in_file(FILE* file); // Counts the number of columns in a file

int num_rows_in_file(FILE* file); // Counts the number of rows in a file

void determine_state(double** data, int rows, int cols); // Determines if the EEG array argument is awake or asleep