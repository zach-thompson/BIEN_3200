/*
* Lab 2
* Created by: Zach Thompson
* Date created: 10/6/20
* Function: This program ...
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include "utility.h"
#include "event_detection.h"

void main() {
    // Determine which data file the user wants to load
    FILE* file;
    char file_name[50];
    char yes_no[10];

    do { // do/while loop to run while yes_no is "y"
        printf("Enter the name of the file you would like to load:\n"); // Prompt the user to enter a file name
        scanf("%s", &file_name);
        fopen_s(&file, file_name, "r"); // Open the file

        if (file != NULL) { // If the file exists, run this loop
            int cols = num_cols_in_file(file);
            if (cols != 2) { // Make sure the file has the required 2 columns
                printf("Please load a file with 2 columns.\n\n");
                strcpy(yes_no, "y"); // Set yes_no to "y" if the number of column is not 2 so the loop reruns
            }
            else (strcpy(yes_no, "good")); // Sets yes_no to something other than y or n
        }
        else { // If the file does not exist, run this loop
            printf("The file you entered does not exist. Would you like to try again? y or n\n");
            scanf("%s", &yes_no);
            while ((strcmp(yes_no, "y") != 0) && (strcmp(yes_no, "n") != 0)) { // While yes_no isn't "y" or "n" run this loop
                    printf("Please enter y or n.\n");
                    scanf("%s", &yes_no); // Sets yes_no according to user input
            }
        }
    } while (strcmp(yes_no, "y") == 0); // Condition of the do/while loop

    if (strcmp(yes_no, "n") == 0) { exit(EXIT_FAILURE); } // If the user doesn't want to load a file, end the program

    int cols = num_cols_in_file(file);
    int rows = num_rows_in_file(file);
    double** data = load_data(file, rows, cols); // Load the data into a 2D array that can be referenced as data[rows][cols]

    double** central = central_diff(data, rows); // Calculate the central derivative of the data
    double max = max_val(data, rows); // Calculate the maximum value in the orignal array
    double d_max = max_val(central, rows); // Calculate the maximum value in the array of central derivatives

    AF1(central, rows, max, d_max); // Call the AF1 function to print out all the times an event is detected
}