#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
    int guess_number, user_guess;
    int attempts = 0;

    srand(time(NULL));
    // guess_number = rand();
    guess_number = rand() % 100 + 1;

    // printf("%d\n", guess_number);

    printf("Welcome to the Guessing Game!\n");

    do
    {
        printf("Enter a number between 1 and 100: ");
        scanf("%d", &user_guess);
        attempts++;

        if (user_guess < guess_number){
            printf("Too low! Try again.\n");
        } else if (user_guess > guess_number) {
            printf("Too high! Try again.\n");
        } else {
            printf("Congratulations! You've guessed the number in %d attempts.\n", attempts);
        }
    } while (guess_number != user_guess);

    printf("Game Over! The number was %d.\n", guess_number);
    printf("You made %d attempts.\n", attempts);
    printf("Thanks for playing! Well Done!\nMade by Python_Programmer.12");

}