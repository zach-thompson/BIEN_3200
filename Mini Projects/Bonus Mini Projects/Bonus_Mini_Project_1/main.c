#include "Header.h"
/*
* Author: Zach Thompson
* Due: 12/4/20
* Function: Implement bandpass and high pass filters
*/

void main() {
	return;
}

double* convolve(double* signal, int s_rows, double* filter, int f_rows) {
	int length = s_rows + f_rows - 1;
	double* output = calloc(length, sizeof(double));

	for (int i = 0; i < f_rows; i++) {
		output[i] = filter[i] * signal[s_rows - i];
	}
	return output;
}

double* create_high_pass_filt(double* signal) {
	
	
}

double* create_band_pass_filt(double* x) {

}

double* load_data(FILE* file, int numrows) {
	if (file != NULL) {
		double* dataset = calloc(numrows, sizeof(double)); // Allocate each of our row pointers.

		if (dataset == NULL) { return NULL; }

		for (int i = 0; i < numrows; i++) {
			fscanf_s(file, "%lf,", &dataset[i]);
		}
		return dataset;
	}
	else {
		printf_s(stderr, "Unable to find file! Ensure it is in the Debug directory.");
		return NULL;
	}
}

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