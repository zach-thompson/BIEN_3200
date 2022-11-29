#include <stdio.h>
#include "zThompson_MiniProject3.h"
#define _CRT_SECURE_NO_WARNINGS

/*
* Mini Project 3
* Author: Zach Thompson
* Date: 10/27/20
* Purpose: TBD
*/

void main(int argsc, char* argv[]) {
	beeper(atoi(argv[1]));

}

void beeper(int num_beeps) {
	int n = num_beeps;
	printf("You asked for %d beeps.", num_beeps);
	for (int i = 0; i < n; i++) {
		tinyfd_beep();
	}
}

void mood_ring(char* color, struct favorite_color* mood) {
	/* unsigned char default[3];
	*result[3];
	*
	*colorchooser(null, null, default, result)
	*
	* struct->var1 = result[0]
	* (*Struct) var =
	*/
}