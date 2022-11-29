#include <stdio.h>
#include <stdlib.h>
#include "Utility_final.h"

/* 
* This contains the following functions:
* load_data
* numrows
* numcols
* determine_state
*/

/*
* This function loads data, given a already opened input file and known dimensions,
* and returns a double pointer (2D array) dynamically allocated for this purpose.
*
* @param file: An ALREADY OPEN file pointer
* @param numrows: The number of rows in the file.
* @param numcols: The number of columnss in the file.
*
* @returns: a pointer to a dynamically allocated array filled with data from the input file
*/

double** load_data(FILE* file, int numrows, int numcols) {
    if (file != NULL) {
        double** dataset = calloc(numrows, sizeof(double*)); // Allocate each of our row pointers.

        if (dataset == NULL) { return NULL; }
        for (int i = 0; i < numrows; i++) {
            dataset[i] = calloc(numcols, sizeof(double)); // Allocate our columns.
            if (dataset[i] == NULL) { return NULL; }
        }

        for (int i = 0; i < numrows; i++) {
            for (int j = 0; j < numcols; j++) {
                fscanf_s(file, "%lf,", &dataset[i][j]);
            }
        }
        return dataset;
    }
    else {
        fprintf_s(stderr, "Unable to find file! Ensure it is in the Debug directory.");
        return NULL;
    }
}

/*
* This function returns the number of columns in a file.
*
* @param file: The text file to examine for number of columns.
*
* @returns: The number of detected columns in the file.
*/
int num_cols_in_file(FILE* file) {
    int numcols = 0;
    if (file) {
        char buf[30000]; // Make a buffer we'll use to grab a whole row.

        if (fgets(buf, 30000, file) != NULL) {
            // Tokenize our buffer, looking for how many columns we have (aka how many tokens we can create)
            char* token;
            char* next_token = NULL;

            token = strtok_s(buf, " \n\r\t,", &next_token);

            while (token != NULL) {
                token = strtok_s(NULL, " \n\r\t,", &next_token);
                numcols++;
            }
            rewind(file); // Reset position to the beginning of the file
            return numcols;
        }
        else {
            fprintf_s(stderr, "Failed to read first row.");
            return 0;
        }
        rewind(file); // Reset position to the beginning of the file
    }
    else {
        fprintf_s(stderr, "File is unopened. Numcols only works on opened files.");
        return 0;
    }
}

/*
* This function returns the number of rows in a file.
*
* @param file: The text file to examine for number of rows.
*
* @returns: The number of detected rows in the file.
*/
int num_rows_in_file(FILE* file) {
    int numrows = 0;
    if (file) {
        char buf[100000]; // Make a buffer we'll use to grab a whole row.

        while (fgets(buf, 100000, file) != NULL) {
            numrows++;
        }
        rewind(file); // Reset our position to the beginning of the file.
        return numrows;
    }
    else {
        fprintf_s(stderr, "File is unopened. Numrows only works on opened files.");
        return 0;
    }
}

/*
* This function determines if an EEG data array is from a sleeping patient or an awake one.
*
* @param double: The data array to examine for determination.
*
* @returns: Determination char* holding either asleep or awake.
*/
void determine_state(double** data, int rows, int cols) {
	for (int i = 0; i < rows; i++) { // Double for loop to run through entire 2D array
		int count = 0;
		for (int j = 0; j < cols; j++) {
			if ((data[i][j] > 0 && data[i][j + 1] < 0) || (data[i][j] < 0 && data[i][j + 1] > 0)) { // Checks to see if consecutive data points cross 0, basically determining number of oscilations
				count++;
			}
		}
		if (count >= 300) { // If the number of 0-crossings is higher than 300, EEG is from a patient in waking state
			printf(" %i. (%i) awake\n", i+1, count); // Prints EEG# along with state determination
		}
		else { printf(" %i. (%i) \tasleep\n", i+1, count); }
	}
	return;
}