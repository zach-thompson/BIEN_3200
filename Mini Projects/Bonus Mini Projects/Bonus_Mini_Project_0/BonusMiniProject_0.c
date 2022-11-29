#include "BonusMiniProject_0.h"
#include <math.h>
/*
* Author: Zach Thompson
* Due: 12/4/20
* Function: Practice basic coding practices
*/

int* chillin_out() {
	int* chill = calloc(10, sizeof(int));

	for (int i = 0; i < 10; i++) {
		chill[i] = 2;
	}

	for (int i = 0; i < 10; i++) {
		chill[i] = maxin(chill[i], i);
	}

	return chill;
}

int maxin(int base, int power) {
	int result = 1;
	for (int i = 0; i < power; i++) {
		result = result * base;
	}
	return result;
}

void relaxin_all_cool(int* chill) {
	for (int i = 0; i < 10; i++) {
		printf("%i\n", chill[i]);
	}
}
void main() {
	printf("In west Philadelphia I was born and raised. On the playground was where I spent most of my days.\n");
	int* fresh_prince = chillin_out();
	relaxin_all_cool(fresh_prince);

	return;
}