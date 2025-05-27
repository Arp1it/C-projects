#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep function
#include <time.h> // For time function

#define TRUE 1
#define FALSE 0

const int BAR_LENGTH = 50; // Length of the progress bar
const int MAX_TASK = 3; // Maximum number of tasks

typedef struct{
    int id;
    int progress;
    int step;
} Task;


void print_baar(Task task);
void clr_scr();

int main(){
    Task task[MAX_TASK];

    srand(time(NULL)); // Seed for random number generation

    for (int i = 0; i < MAX_TASK; i++){
        task[i].id = i + 1;
        task[i].progress = 0;
        task[i].step = rand() % 10 + 1;
    }

    int task_continue = TRUE;
    while(task_continue){
        task_continue = FALSE;

        clr_scr(); // Clear the screen
        printf("Progress Bar Simulation\n");

        for (int i = 0; i < MAX_TASK; i++){
            task[i].progress += task[i].step;

            if(task[i].progress < 100){
                task_continue = TRUE; // Set to TRUE if any task is not complete

            }else if(task[i].progress >= 100){
                task[i].progress = 100;
            }

            print_baar(task[i]);
        }
        
        sleep(1); // Sleep for 1 second to simulate progress
    }

    printf("All tasks completed!");

    return 0;
}

void clr_scr(){
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For Linux/Unix
    #endif
}

void print_baar(Task task){
    int bar_to_show = (task.progress * BAR_LENGTH) / 100;

    printf("Task %d: [", task.id);

    for (int i = 0; i < BAR_LENGTH; i++){
        if (i < bar_to_show){
            printf("=");
        } else {
            printf(" ");
        }
    }

    printf("] %d%%\n", task.progress);
}