#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "event_detection.h"
#include "utility.h"

/*
* This contains the following functions:
* Threshold determinations
* AF1 Function
*/

// Calculates and returns the highest value in an array
double max_val(double** data, int rows) {
	double max = 0;
	for (int i = 0; i < rows; i++) {
		if (data[i][1] > max) { max = data[i][1]; }
	}
	return max;
}

// AF1 lgorithm for detecting an event
double AF1(double** data, int rows, double max, double d_max) {
	double** central = central_diff(data, rows); // Calculate the central derivatives of the data array

	// Determine relative thresholds
	double gen_thresh = max * 0.3;
	double pos_thresh = d_max * 0.5;
	double neg_thresh = d_max * -0.3;

	bool a; // Boolean representing case a (3 consecutive values over the positive threshold)
	bool b; /* Boolean representing case b (2 consecutive values within the blank below the negative threshold, 
			*     also representing case c (All values within the blank above the general threshold) */
	for (int i = 0; i < rows; i++) {
		a = false;
		b = false;
		if (data[i][1] && data[i + 1][1] && data[i + 2][1] > pos_thresh) { // Checks for 3 values over the positive threshold
			a = true;
		}
		for (int j = i * 0.004; j < i * .004 + 0.01; j = j + .004) {
			if ((data[j][1] && data[j + 1][i] < neg_thresh) && (data[j][1] > gen_thresh)) {
				b = true;
				i = i + 100; // skipping over the blanking period
			}
		}
		if (a && b == true) {
			printf("Event detected at %f seconds.\n", data[i][0]); // Print out when an event is detected
		}
	}
}