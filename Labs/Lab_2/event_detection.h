#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Determine thresholds
// AF1 function

double max_val(double** data, int rows);

double AF1(double** data, int rows, double max, double d_max);