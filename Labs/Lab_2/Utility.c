#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utility.h"

/* 
* This contains the following functions:
* load_data
* numrows
* numcols
* ways of calculating the derivatives
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
        char buf[100]; // Make a buffer we'll use to grab a whole row.

        if (fgets(buf, 100, file) != NULL) {
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
        char buf[100]; // Make a buffer we'll use to grab a whole row.

        while (fgets(buf, 100, file) != NULL) {
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
* This function returns the forward derivative of a given array
*
* @param data: A 2D array filed with data.
* @param numrows: The number of rows in the array
* 
* @returns: A 2D array filled with the forward derivative values of the initial array.
*/
double** forward_diff(double** data, int rows) {
    // Set up a 2D array to fill with forward derivative values
    double** forward = calloc(rows, sizeof(double*));
    for (int i = 0; i < rows; i++) {
        forward[i] = calloc(2, sizeof(double)); // Allocate our columns.
        if (forward[i] == NULL) { return NULL; }
    }

    // Calculate the forward derivative for each index in the given array
    for (int i = 0; i < rows - 1; i++) {       
        forward[i][1] = (data[i + 1][1] - data[i][1]) / (data[1][0]); // Standard forward derivative equation
    }
    forward[rows - 1][1] = (data[rows - 1][1] - data[rows - 2][1]) / (data[1][0]); // Use backward derivative for last value
    return forward;
}

/*
* This function returns the backward derivative of a given array
*
* @param data: A 2D array filed with data.
* @param numrows: The number of rows in the array
*
* @returns: A 2D array filled with the backward derivative values of the initial array.
*/
double** backward_diff(double** data, int rows) {
    // Set up a 2D array to fill with forward derivative values
    double** backward = calloc(rows, sizeof(double*));
    for (int i = 0; i < rows; i++) {
        backward[i] = calloc(2, sizeof(double)); // Allocate our columns.
        if (backward[i] == NULL) { return NULL; }
    }

    // Calculate the backward derivative for each index in the given array
    backward[0][1] = (data[1][1] - data[0][1]) / (data[1][0]); // Use forward derivative for first value
    for (int i = 1; i < rows; i++) {
      backward[i][1] = (data[i][1] - data[i - 1][1]) / (data[1][0]); // Standard backward derivative equation
    }
    return backward;
}

/*
* This function returns the central derivative of a given array
*
* @param data: A 2D array filed with data.
* @param numrows: The number of rows in the array
*
* @returns: A 2D array filled with the central derivative values of the initial array.
*/
double** central_diff(double** data, int rows) {
    // Set up a 2D array to fill with forward derivative values
    double** central = calloc(rows, sizeof(double*));
    for (int i = 0; i < rows; i++) {
        central[i] = calloc(2, sizeof(double)); // Allocate our columns.
        if (central[i] == NULL) { return NULL; }
    }

    // Calculate the central derivative for each index in the given array
    central[0][1] = (data[1][1] - data[0][1]) / (data[1][0]); // Use forward derivative for first value
    for (int i = 1; i < rows - 2; i++) {
       central[i][1] = (data[i + 1][1] - data[i - 1][1]) / (2 * data[1][0]); // Standard central derivative equation
    }
    central[rows - 1][1] = (data[rows - 1][1] - data[rows - 2][1]) / (data[1][0]); // Use backward derivative for last value

    return central;
}