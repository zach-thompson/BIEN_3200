#include <stdio.h>
/*
* Author: Zach Thompson
* Date: 9/8/20
* Function: Fill two arrays with increasing values and then print the sum of both arrays
*/

void main() {
	int evens[10];
	int odds[10];

	// fills in both arrays with 0
	int i = 0;
	while (i < 9) {
		evens[i] = 0;
		odds[i] = 0;
		i++;
	}

	// fills in even indices of even[] with even numbers,
	int j = 0;
	for (int i = 0; i < 9; i += 2) {
		evens[i] = j;
		j += 2;
	}

	// fills in odd indices of odd[] with odd numbers
	int k = 1;
	for (int i = 0; i < 9; i += 2) {
		odds[i] = k;
		k += 2;
	}

	// calculates the sum of each array
	int sum_evens = 0;
	int sum_odds = 0;
	int c = 0;
	do {
		sum_evens += evens[c];
		sum_odds += odds[c];
		c++;
	} while (c < 9);

	printf("The sum of the even array is: %d\nThe sum of the odd array is: %d\n", sum_evens, sum_odds);
}