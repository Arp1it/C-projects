#include <stdio.h>
#include <time.h>

int main(){
    time_t s, val = 1;

    struct tm* current_time;

    s = time(NULL); // Get the current time in seconds since the epoch. epoch is 1970-01-01 00:00:00 +0000 (UTC)

    current_time = localtime(&s); // Convert the time to local time

    printf("Today: %s", asctime(current_time)); // Print the current time in a human-readable format

    printf("Current time: %02d:%02d:%02d\n", current_time->tm_hour, current_time->tm_min, current_time->tm_sec); // Print the current time in HH:MM:SS format

    return 0;
}



// This program demonstrates how to retrieve and display the current date and time in C using the `<time.h>` library. The `<time.h>` header provides functions and structures for working with time and date information.

// 1. **Variable Declarations**:  
//    The program declares two variables: `s` of type `time_t` and `current_time` of type `struct tm*`. The `time_t` type is used to store time as the number of seconds since the Unix epoch (January 1, 1970, 00:00:00 UTC). The `struct tm` is a structure that breaks down time into components like year, month, day, hour, minute, and second.

// 2. **Getting the Current Time**:  
//    The `time(NULL)` function is called to get the current time in seconds since the epoch. This value is stored in the variable `s`. Passing `NULL` to `time()` means the function will return the current time instead of storing it in a provided variable.

// 3. **Converting to Local Time**:  
//    The `localtime(&s)` function converts the time stored in `s` (in seconds since the epoch) into local time, represented as a `struct tm`. The result is a pointer to this structure, which is stored in `current_time`. This step adjusts the time to the local timezone and breaks it into components like hours, minutes, and seconds.

// 4. **Printing the Date in a Readable Format**:  
//    The `asctime(current_time)` function converts the `struct tm` into a human-readable string format, such as `"Wed Mar 15 14:30:00 2023\n"`. This string is printed using `printf` with the label `"Today: "`.

// 5. **Printing the Time in HH:MM:SS Format**:  
//    The program then prints the current time in a more structured format (`HH:MM:SS`) using `printf`. The format specifiers `%02d` ensure that each component (hours, minutes, seconds) is displayed as a two-digit number, with leading zeros if necessary. The values `current_time->tm_hour`, `current_time->tm_min`, and `current_time->tm_sec` are accessed from the `struct tm` to provide the respective time components.

// 6. **Program Termination**:  
//    The `return 0;` statement indicates that the program has executed successfully.

// Overall, this program demonstrates basic time manipulation in C, including retrieving the current time, converting it to local time, and formatting it for display. It is a simple yet effective example of working with the `<time.h>` library.