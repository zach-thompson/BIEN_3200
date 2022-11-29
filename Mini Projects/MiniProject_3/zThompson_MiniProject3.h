#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <tinyfiledialogs.h>
#define _CRT_SECURE_NO_WARNINGS


void beeper(int num_beeps); // Accepts a number of beeps, no return

void mood_ring(char* color, struct favorite_color*); // Accepts a hex string and a struct pointer, no return
