#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

void time_format_12hours();
void time_format_24hours();

time_t timee;
struct tm *time_info;

char buffer_time[30];
char buffer_day[30];

int main(){

    int choice;

    printf("Choose a clock format:\n");
    printf("1. 12-hour format\n");
    printf("2. 24-hour format\n");
    printf("Enter your choice (1 or 2): ");

    scanf("%d", &choice);

    system("cls"); // Clear the console for a cleaner output
    printf("\n\n");

    if (choice == 1){
        time_format_12hours();
    } else{
        time_format_24hours();
    }
 
}


void time_format_12hours(){
    while(TRUE){
        time(&timee);
        time_info = localtime(&timee);

        strftime(buffer_day, sizeof(buffer_day), "%A %B %Y", time_info);
        strftime(buffer_time, sizeof(buffer_time), "%I:%M:%S %p", time_info);
        printf("\rCurrent day: %s | Current time: %s", buffer_day, buffer_time);

        fflush(stdout);

        sleep(1); // Sleep for 1 second to update the time every second

        // system("cls"); // Clear the console for a cleaner output
    }
}

void time_format_24hours(){
    while(TRUE){
        time(&timee);
        time_info = localtime(&timee);

        strftime(buffer_day, sizeof(buffer_day), "%A %B %Y", time_info);
        strftime(buffer_time, sizeof(buffer_time), "%H:%M:%S", time_info);
        printf("\rCurrent day: %s | Current time: %s", buffer_day, buffer_time);

        fflush(stdout);

        sleep(1); // Sleep for 1 second to update the time every second

        // system("cls"); // Clear the console for a cleaner output
    }
}

// Current day: Friday May 2025 | Current time: 12:00:17 AMPM
// PS C:\Users\Microsoft\Documents\prrrog\ccccc\cprojj> 