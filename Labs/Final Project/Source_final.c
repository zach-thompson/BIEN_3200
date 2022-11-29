#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Utility_final.h"

/*
* Authors: Thompson, Zach; Wanta, Meghan
* Due: 12/4/2020
* Function: Given an EEG file, determine if the patient is awake or asleep
*/

void main() {
	// Load file
	FILE* file;
	file = fopen("EEG_SleepData_30sec_100Hz.csv", "r");

	if (file == NULL) // Checks to see if the file does not exist or was not loaded correctly
	{
		printf("File Does Not Exist\n");
	}

	int num_rows = num_rows_in_file(file);
	int num_cols = num_cols_in_file(file);

	// Load the data into a 2D array that can be in indexed by data[row][col]
	double** data = load_data(file, num_rows, num_cols);

	// Make determination
	determine_state(data, num_rows, num_cols);
	
}