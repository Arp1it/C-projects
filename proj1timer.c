/* c program to design a timer! */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int hour, minute, second;
    hour=minute=second=0;

    while (1) 
    {
        // clear output screen!
        // system("clear"); // for linux
        system("cls"); // for windows
        
        // print time in HH:MM:SS format
        printf("Timer: %02d:%02d:%02d\n", hour, minute, second);

        // clear output buffer in gcc
        fflush(stdout); // this is used to flush the output buffer in gcc. The output buffer is a temporary storage area for data that is being sent to the output device. When you use printf, the data is stored in the output buffer until it is full or until you flush it. Flushing the output buffer means that you are sending the data to the output device immediately.

        // increase second
        second++;

        if (second == 60) // if second is 60, increase minute and reset second
        {
            second = 0;
            minute++;
        }

        if (minute == 60){
            minute = 0; // if minute is 60, increase hour and reset minute
            hour++;
        }

        if (hour == 24){ // if hour is 24, reset hour
            hour = 0;
            minute = 0;
            second = 0;
        }

        sleep(1); // sleep for 1 second
    }

    return 0;
    
}