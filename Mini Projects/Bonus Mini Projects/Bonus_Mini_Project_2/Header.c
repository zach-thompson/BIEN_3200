#include "Header.h"
/*
* Author: Zach Thompson
* Due: 12/4/20
* Purpose: Implementing binary filtering operations
*/

/*
* This function returns a 2D array pointer after performing a dilation with a 3x3 structure.
*
* @param in: 2D array pointer
* @param numrows: The number of rows in the file.
* @param numcols: The number of columnss in the file.
*
* @returns: 2D array pointer with filtered data.
*/
int** dilate(int** in, int rows, int cols) {
	// Create filter structure
	int filter[3][3] = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };

	// Create 2D output array
	int** out = calloc(rows, sizeof(int)); // Allocate space for rows
	for (int i = 0; i < rows; i++) {
		out[i] = calloc(cols, sizeof(int)); // Allocate space for cols
	}

	// Fill the out array with 0's
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			out[i][j] = 0;
		}
	
	// Perform the dilation process
	for (int i = 1; i < rows - 1; i++) { // Scans through the array, minus the border values
		for (int j = 1; j < cols - 1; j++) {
			if (in[i][j] != 0) { // Loop runs if value isn't 0
				for (int a = -1; a < 2; a++) { // Runs through the neighboring indices 
					for (int b = -1; b < 2; b++) {
						out[i + a][j + b] = in[i][j] * filter[a + 1][b + 1]; // Applies the filter
					}
				}
			}
		}
	}

	return out;
}

/*
* This function returns a 2D array pointer after performing an erosion with a 3x3 structure.
*
* @param in: 2D array pointer
* @param numrows: The number of rows in the file.
* @param numcols: The number of columnss in the file.
*
* @returns: 2D array pointer with filtered data.
*/
int** erode(int** in, int rows, int cols) {
	// Create filter structure
	int filter[3][3] = { {0, 0, 0}, {0, 1, 0}, {0, 0, 0} };

	// Create 2D output array
	int** out = calloc(rows, sizeof(int)); // Allocate space for rows
	for (int i = 0; i < rows; i++) {
		out[i] = calloc(cols, sizeof(int)); // Allocate space for cols
	}

	// Fill the out array with 0's
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			out[i][j] = 0;
		}
	}
	
	// Perform the erosion process
	for (int i = 1; i < rows - 1; i++) { // Scans through the array, minus the border values
		for (int j = 1; j < cols - 1; j++) {
			if (in[i][j] != 0) { // Loop runs if value isn't 0
				int count = 0;
				for (int a = -1; a < 2; a++) { // Runs through the neighboring indices checking for zeros
					for (int b = -1; b < 2; b++) {
						if (in[i + a][j + b] != 0) {
							count++;
						}
					}
				}
				if (count == 9) { // If all of the surrounding indices were non-zero
					out[i][j] = in[i][j];
				}
			}
		}
	}

	return out;
}

/*
* This function returns a 2D array pointer after performing an opening filter with a 3x3 structure.
*
* @param pic: 2D array pointer
* @param numrows: The number of rows in the file.
* @param numcols: The number of columnss in the file.
*
* @returns: 2D array pointer with filtered data.
*/
int** open(int** pic, int rows, int cols) {
	// Create 2D output array
	int** out = calloc(rows, sizeof(int)); // Allocate space for rows
	for (int i = 0; i < rows; i++) {
		out[i] = calloc(cols, sizeof(int)); // Allocate space for cols
	}
	
	// Perform opening
	int** pic_2 = erode(pic, rows, cols); // Erode image
	int** pic_out = dilate(pic_2, rows, cols); // Dilate resulting image
	return pic_2;
}

/*
* This function returns a 2D array pointer after performing a closing filter with a 3x3 structure.
*
* @param pic: 2D array pointer
* @param numrows: The number of rows in the file.
* @param numcols: The number of columnss in the file.
*
* @returns: 2D array pointer with filtered data.
*/
int** close(int** pic_in, int rows, int cols) {
	// Create 2D output array
	int** out = calloc(rows, sizeof(int)); // Allocate space for rows
	for (int i = 0; i < rows; i++) {
		out[i] = calloc(cols, sizeof(int)); // Allocate space for cols
	}
	
	int** pic_2 = dilate(pic_in, rows, cols); // Dilate image
	int** pic_out = erode(pic_2, rows, cols); // Erode resulting image
	return pic_out;
}

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
int** load_data(FILE* file, int numrows, int numcols) {
	if (file != NULL) {
		int** dataset = calloc(numrows, sizeof(int*)); // Allocate each of our row pointers.

		if (dataset == NULL) { return NULL; }
		for (int i = 0; i < numrows; i++) {
			dataset[i] = calloc(numcols, sizeof(int)); // Allocate our columns.
			if (dataset[i] == NULL) { return NULL; }
		}

		for (int i = 0; i < numrows; i++) {
			for (int j = 0; j < numcols; j++) {
				fscanf_s(file, "%i ", &dataset[i][j]);
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
		char buf[110]; // Make a buffer we'll use to grab a whole row.

		while (fgets(buf, 110, file) != NULL) {
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