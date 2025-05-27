#include <stdio.h>
#include <math.h>

#define TRUE 1

void print_menu();
double divide(double, double);
double modulus(int, int);


void main()
{
    double num1, num2, result;
    int choice;
    
    while (TRUE)
    {
        print_menu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 7) {
            fprintf(stderr, "\nInvalid choice. Please select a valid operation (1-7).\n");
            continue;
        }

        if (choice != 7){
            printf("\nEnter first number: ");
            scanf("%lf", &num1);
            printf("Enter second number: ");
            scanf("%lf", &num2);

            switch (choice)
            {
                case 1:
                    result = num1 + num2;
                    break;

                case 2:
                    result = num1 - num2;
                    break;

                case 3:
                    result = num1 * num2;
                    break;

                case 4:
                    result = divide(num1, num2);
                    break;

                case 5:
                    result = modulus((int)num1, (int)num2);
                    break;

                case 6:
                    result = pow(num1, num2);
                    break;
            }

            if (!isnan(result)){
                printf("\nResult: %lf\n", result);
            }
        }

        if (choice == 7) {
            printf("Exiting the calculator. Goodbye!\n");
            break;
        }
    }
    

}

double divide(double a, double b) {
    if (b == 0) {
        fprintf(stderr, "\nError: Division by zero is not allowed.");
        return NAN;
    }
    return a / b;
}

double modulus(int a, int b) {
    if (b == 0) {
        fprintf(stderr, "\nError: Modulus by zero is not allowed.");
        return NAN;
    }
    return a % b;
}

void print_menu(){
    printf("\n\n-----------------------------------------------\n");
    printf("Welcome to the Simple Calculator\n");
    printf("\nPlease select an operation:");
    printf("\n1. Add\n2. Subtract\n3. Multiply\n4. Divide\n5. Modulus\n6. Power\n7. Exit\n");
}