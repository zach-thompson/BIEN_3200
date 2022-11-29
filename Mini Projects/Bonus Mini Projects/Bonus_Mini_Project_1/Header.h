#pragma once
#include <stdio.h>
#include <stdlib.h>
/*
* Author: Zach Thompson
* Due: 12/4/20
* Function: Header file for implementing bandpass and high pass filters
*/

#ifndef HEADER
#define HEADER

double* convolve(double* signal, int s_rows, double* filter, int f_rows);

double* create_high_pass_filt(double* x);

double* create_band_pass_filt(double* x);

double* load_data(FILE* file, int numrows); // Loads a file into a 1D array

int num_rows_in_file(FILE* file); // Counts the number of rows in a file

#endif#pragma once
