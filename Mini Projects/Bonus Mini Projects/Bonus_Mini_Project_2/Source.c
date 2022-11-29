#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
/*
* Author: Zach Thompson
* Due: 12/4/20
* Purpose: Implementing binary filtering operations
*/

void main() {
	FILE* file;
	file = fopen("glassesman.dat", "r");

	if (file == NULL) // Checks to see if the file does not exist or was not loaded correctly
	{
		printf("File Does Not Exist\n");
	}

	int num_rows = num_rows_in_file(file);
	int num_cols = num_cols_in_file(file);
	
	// Load the data into a 2D array that can be in indexed by data[row][col]
	int** image = load_data(file, num_rows, num_cols);

	// Perform the binary filtering operations on the image
	int** eroded_image = erode(image, num_rows, num_cols);
	int** dilated_image = dilate(image, num_rows, num_cols);
	int** opened_image = open(image, num_rows, num_cols);
	int** closed_image = close(image, num_rows, num_cols);

	// Create files to output the results into
	FILE* eroded_file;
	eroded_file = fopen("eroded_file.dat", "w");
	FILE* dilated_file;
	dilated_file = fopen("dilated_file.dat", "w");
	FILE* opened_file;
	opened_file = fopen("opened_file.dat", "w");
	FILE* closed_file;
	closed_file = fopen("closed_file.dat", "w");

	// Loop through the image arrays and print them out to their respective files
	for (int x = 0; x < num_rows; x++) {
		for (int y = 0; y < num_cols; y++) {
			fprintf(eroded_file, "%i ", eroded_image[x][y]);
			fprintf(dilated_file, "%i ", dilated_image[x][y]);
			fprintf(opened_file, "%i ", opened_image[x][y]);
			fprintf(closed_file, "%i ", closed_image[x][y]);
		}
		fprintf(eroded_file, "%\n");
		fprintf(dilated_file, "%\n");
		fprintf(opened_file, "%\n");
		fprintf(closed_file, "%\n");
	}

	fclose(eroded_file, dilated_file, opened_file, closed_file); // Close all files
	return;
}