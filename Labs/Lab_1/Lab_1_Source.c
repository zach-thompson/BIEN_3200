/*
* Created by Zach Thompson
* 09/15/20
* This program is designed to load a data file of any size, and then perform an assortment of
* user-requested descriptive statistics on the data
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include <math.h>

// Initialize all the different functions to be written later
float fmean(double** data, int rows, int column);
float fmedian(double** data, int rows, int column);
float fmode(double** data, int rows, int column);
float fstddev(double** data, int rows, int column);
float fvariance(double** data, int rows, int column);
float fskew(double** data, int rows, int column);
void fMAP(double** data, int rows);
void fPP(double** data, int rows);
void sort(double** data, int rows, int column);

void histogram(double** data, int rows, int column);
double** load_data(FILE* file, int numrows, int numcols);
int num_rows_in_file(FILE* file);
int num_cols_in_file(FILE* file);

int main(void) {
    // Load the data file
    FILE* data_file;
    fopen_s(&data_file, "cardio_dataset.dat", "r");
    // Calculate the number of rows and cols in the file
    int num_rows = num_rows_in_file(data_file);
    int num_cols = num_cols_in_file(data_file);

    char** header = calloc(num_cols, sizeof(double*)); //Allocate space
    char buf[512]; // Make a buffer to grab a whole row

    if (fgets(buf, 512, data_file) != NULL) { // Stores the value in buf and if it exists, continue
        header[0] = strtok(buf, "\n\r\t,"); // Stores the first value of buf into header variable
        printf("Header 0: %s\n", header[0]);
        int i = 1;
        while (header[i - 1] != NULL) {
            header[i] = strtok(NULL, " \n\r\t,"); //gets remaining columns, uses defined delimiters with ","
            if ((header[i] != NULL)) { //if value exists
                printf("Header %d: %s\n", (i), header[i]);
            }
            i++;
        }
    }

    // Load the remaining numerical data into a 2D array that can be in indexed by data[row][col]
    double** data = load_data(data_file, num_rows, num_cols);

    // Initialize variables
    int col = 0;
    int row = 0;
    char func[10];
    char ans[10];
    
    // do-while loop used to execute the bulk of I/O commands
    do {
        // Prompt the user to input whichever column of data they want to analyze, as well as which descriptive statistic)
        printf("\nUsing its header number, select which column you want to analyze.\nHeader: ");
        scanf("%d", &col);
        printf("\nYour analysis functions are mean, median, mode, variance, stddev, and skew.\n");
        printf("Enter which function would you like to perform on column %d:\n", col);
        scanf("%s", func);

        // Massive if/else loop printing out the result of whatever descriptive statistic the user called on the desired column
        // After finishing the loop, prompts user if they want to run through the choices again 
        if (strcmp(func, "mean") == 0) {
            printf("\nThe %s of column %d is: %f\n", func, col, fmean(data, num_rows, col));
        }
        else if (strcmp(func, "median") == 0) {
            printf("\nThe %s of column %d is: %f\n", func, col, fmedian(data, num_rows, col));
        }
        else if (strcmp(func, "mode") == 0) {
            printf("\nThe %s of column %d is: %f\n", func, col, fmode(data, num_rows, col));
        }
        else if (strcmp(func, "stddev") == 0) {
            printf("\nThe %s of column %d is: %f\n", func, col, fstddev(data, num_rows, col));
        }
        else if (strcmp(func, "variance") == 0) {
            printf("\nThe %s of column %d is: %f\n", func, col, fvariance(data, num_rows, col));
        }
        else if (strcmp(func, "skew") == 0) {
            printf("\nThe %s of column %d is: %f\n", func, col, fskew(data, num_rows, col));
        }
        else { printf("\nPlease enter a valid function.\n"); }

        printf("\nWould you like to run more analysis? y or n\n");
        scanf("%s", &ans);
    } while (strcmp(ans, "y") == 0);

    // Give the user the option to run Sietronic's "favorite descriptive statistic" and ask for number of rows to print
    printf("\nWould you like to run some MAP and PP calculations? y or n\n");
    scanf("%s", &ans);
 
    if (strcmp(ans, "y") == 0) {
        printf("How many of the %d rows of would you like to calculate?\n", num_rows - 1);
        scanf("%i", &row);
        fMAP(data, row);
        fPP(data, row);
    }
    
    printf("Select which column you'd like to create a histogram of:\n");
    scanf("%i", &ans);

    histogram(data, num_rows, 4);
    // histogram(data, num_rows, 5);
    // histogram(data, num_rows, ans);
    return 0;
    fclose(data_file);
}

/*
* This function calculates the mean of a desired column
*
* @param data: A 2D array with rows and columns
* @param rows: The number of rows in the file
* @param column: The specific column you want to find the mean of
*
* @returns: The mean of a user-chosen column in the given array
*/
float fmean(double** data, int rows, int column) {
    float mean = 0;

    for (int i = 0; i < rows; i++) {
        mean = mean + data[i][column];
    }
    return mean / rows;
}

/*
* This function calculates the median of a desired column
*
* @param data: A 2D array with rows and columns
* @param rows: The number of rows in the file
* @param column: The specific column you want to find the mean of
*
* @returns: The median of a user-chosen column in the given array
*/
float fmedian(double** data, int rows, int column) {
    sort(data, rows, column);
    float median;

    if (rows % 2 == 0) {
        median = (data[rows / 2][column] + data[(rows / 2) - 1][column]) / 2;
    }
    else {
        median = data[rows / 2][column];
    }
    return median;
}

/*
* This function calculates the mode of a desired column
*
* @param data: A 2D array with rows and columns
* @param rows: The number of rows in the file
* @param column: The specific column you want to find the mean of
*
* @returns: The mode of a user-chosen column in the given array
*/
float fmode(double** data, int rows, int column) {
    sort(data, rows, column);
    int i = 0;
    int count;
    int max = 0;
    int row;

    while (i < rows - 1) {
        count = 1;
        while (data[i][column] == data[i + 1][column]) {
            count++;
            i++;
        }
        if (count > max) {
            max = count;
            row = i;
        }
        i++;
    }
    return data[row][column];
}

/*
* This function calculates the standard deviation of a desired column
*
* @param data: A 2D array with rows and columns
* @param rows: The number of rows in the file
* @param column: The specific column you want to find the mean of
*
* @returns: The standard deviation of a user-chosen column in the given array
*/
float fstddev(double** data, int rows, int column) {
    float stddev = sqrt(fvariance(data, rows, column));
    return stddev;
}

/*
* This function calculates the variance of a desired column
*
* @param data: A 2D array with rows and columns
* @param rows: The number of rows in the file
* @param column: The specific column you want to find the mean of
*
* @returns: The variance of a user-chosen column in the given array
*/
float fvariance(double** data, int rows, int column) {
    float variance = 0;
    float mean = fmean(data, rows, column);

    for (int i = 0; i < rows; i++) {
        variance = variance + pow((data[i][column]) - mean, 2);
    }
    return variance / (rows - 1);
}

/*
* This function calculates the skew of a desired column
*
* @param data: A 2D array with rows and columns
* @param rows: The number of rows in the file
* @param column: The specific column you want to find the mean of
*
* @returns: The skew of a user-chosen column in the given array
*/
float fskew(double** data, int rows, int column) {
    float skew = 0;
    float mean = fmean(data, rows, column);
    float variance = fvariance(data, rows, column);

    for (int i = 0; i < rows; i++) {
        skew = skew + pow(data[i][column] - mean, 3);
    }
    skew = skew / (rows - 1);
    skew = skew / pow(variance, 3.0 / 2.0);
    return skew;
}

/*
* This function calculates and prints the Mean Arteriol Pressure of a user-given number of rows
*
* @param data: A 2D array with rows and columns
* @param rows: The number of rows in the file
*
* @returns: void
*/
void fMAP(double** data, int rows) {
    float* sp = calloc(rows, sizeof(float));
    float* dp = calloc(rows, sizeof(float));
    float MAP = 0;

    for (int i = 0; i < rows; i++) {
        sp[i] = data[i][4];
        dp[i] = data[i][5];
    }

    for (int i = 0; i < rows; i++) {
        MAP = (sp[i] + 2.0 * dp[i]) / 3;
        printf("The MAP of row %d is %f\n", i + 1, MAP);
    }
    free(sp);
    free(dp);
    return;
}

/*
* This function calculates and prints the Pulse Pressure of a user-given number of rows
*
* @param data: A 2D array with rows and columns
* @param rows: The number of rows in the file
*
* @returns: void
*/
void fPP(double** data, int rows) {
    float* sp = calloc(rows, sizeof(float));
    float* dp = calloc(rows, sizeof(float));
    float PP = 0;

    for (int i = 0; i < rows; i++) {
        sp[i] = data[i][4];
        dp[i] = data[i][5];
    }

    for (int i = 0; i < rows; i++) {
        PP = sp[i] - dp[i];
        printf("The PP of row %d is %f\n", i + 1, PP);
    }
    free(sp);
    free(dp);
    return;
}

/*
* This function organzies the data in each column of a 2D array in ascending order
*
* @param data: A 2D array with rows and columns
* @param rows: The number of rows in the file
* @param column: The number of columns in the file
*
* @returns: void
*/
void sort(double** data, int rows, int column) {
    float temp = 0;

    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            if (data[j][column] > data[j + 1][column]) {
                temp = data[j][column];
                data[j][column] = data[j + 1][column];
                data[j + 1][column] = temp;
            }
        }
    }
}
 
void histogram(double** data, int rows, int column) {
    // Calculate the min and max values of the column
    float min = 0;
    float max = 0;
    for (int i = 0; i < rows; i++) {
        if (min >= data[i][column]) {
            min = data[i][column];
        }
        if (max <= data[i][column]) {
            max = data[i][column];
        }
    }
    
    float width = (max - min) / 50; // Calculates the width of 50 equal bins based on values in the column
    float bin_center[50];
    float bin_value[50];
    for (int i = 0; i < 50; i++) {
        bin_value[i] = i * width;
        bin_center[i] = (i+1) * width - (width / 2);
    }

    int bin_count[50];
    for (int i = 1; i < 51; i++) {
          int count = 0; // Initialize counts each for loop set
          for (int j = 0; j < rows; j++) {
                 if (data[j][column] < bin_value[i] && data[j][column] >= bin_value[i - 1]) { // Tests if row value is between bin values
                     count++;
                 }
                 bin_count[i - 1] = count;
          }
       }
    FILE* histo = fopen("histogram.dat", "w");
    for (int i = 0; i < 50; i++) {
        fprintf(histo, "%f, %i\n", bin_center[i], bin_count[i]);
    }
    return; 
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
        char buf[200]; // Make a buffer we'll use to grab a whole row.

        if (fgets(buf, 200, file) != NULL) {
            // Tokenize our buffer, looking for how many columns we have (aka how many tokens we can create)
            char* token;
            char* next_token = NULL;

            token = strtok_s(buf, " \n\r\t,", &next_token);

            while (token != NULL) {
                token = strtok_s(NULL, " \n\r\t,", &next_token);
                numcols++;
            }
            rewind(file); // Reset our position to the beginning of the file.

            return numcols;
        }
        else {
            fprintf_s(stderr, "Failed to read first row.");
            return 0;
        }
        rewind(file); // Reset our position to the beginning of the file.
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
        char buf[200]; // Make a buffer we'll use to grab a whole row.

        while (fgets(buf, 200, file) != NULL) {
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
