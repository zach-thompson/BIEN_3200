#pragma once
#include <stdio.h>
#include <stdlib.h>
/*
* Author: Zach Thompson
* Due: 12/4/20
* Purpose: Implementing binary filtering operations
*/

int** dilate(int** pic, int rows, int cols);

int** erode(int** pic, int rows, int cols);

int** open(int** pic, int rows, int cols);

int** close(int** pic, int rows, int cols);

int** load_data(FILE* file, int numrows, int numcols);

int num_cols_in_file(FILE* file);

int num_rows_in_file(FILE* file);