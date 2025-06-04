#include <stdio.h>
#include <string.h>

#define TRUE 1

void create_account();
void deposit_money();
void withdraw_money();
void check_balance();

const char * ACCOUNT_FILE = "accounts.dat";

typedef struct
{
    char name[50];
    int account_number;
    float balance;
} Account;

int main()
{
    while (TRUE)
    {
        int choice;
        printf("Welcome to the Bank Management System\n");
        printf("Please select an option:\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_account();
            break;
        case 2:
            deposit_money();
            break;
        case 3:
            withdraw_money();
            break;
        case 4:
            check_balance();
            break;
        case 5:
            printf("\nExiting the Bank Management System. Goodbye!\n");
            return 0;
            break;

        default:
            printf("\nInvalid choice. Please try again.\n\n");
            break;
        }
    }
}

void create_account()
{
    Account acc;

    FILE *file = fopen(ACCOUNT_FILE, "ab+");
    if (file == NULL)
    {
        printf("\nError opening file.\n\n");
        return;
    }

    char c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
    
    printf("\nEnter your name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    int ind = strcspn(acc.name, "\n");
    acc.name[ind] = '\0'; // Remove newline character
    printf("Enter your account number: ");
    scanf("%d", &acc.account_number);
    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("\nAccount created successfully!\n\n");
}

void deposit_money()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL)
    {
        printf("\nError opening file.\n\n");
        return;
    }

    int acc_no;
    float dmoney;
    Account acc_read;
    printf("Enter your account number to deposit money: ");
    scanf("%d", &acc_no);

    while(fread(&acc_read, sizeof(acc_read), 1 , file)){
        if(acc_read.account_number == acc_no){
            printf("Enter amount to deposit: ");
            scanf("%f", &dmoney);
            acc_read.balance += dmoney;
            fseek(file, -sizeof(acc_read), SEEK_CUR);
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            fclose(file);
            printf("\nMoney deposited successfully: %.2f! New balance: %.2f\n\n", dmoney, acc_read.balance);
            return;
        }
    }

    fclose(file);
    printf("\nAccount No:%d was not found.\n\n", acc_no);
}

void withdraw_money()
{
    FILE *fil = fopen(ACCOUNT_FILE, "rb+");
    if (fil == NULL)
    {
        printf("\nError opening file.\n\n");
        return;
    }

    int acc_no;
    float wmoney;
    Account acc_read;
    printf("Enter your account number to withdraw money: ");
    scanf("%d", &acc_no);

    while (fread(&acc_read, sizeof(acc_read), 1, fil)){
        if (acc_read.account_number == acc_no){
            printf("Enter amount you want to withdrawl: ");
            scanf("%f", &wmoney);

            if (wmoney <= acc_read.balance){
                acc_read.balance -= wmoney;
                fseek(fil, -sizeof(acc_read), SEEK_CUR);
                fwrite(&acc_read, sizeof(acc_read), 1, fil);
                fclose(fil);
                printf("\nMoney withdrawn successfully: %.2f! New balance: %.2f\n\n", wmoney, acc_read.balance);
                return;
            }

            else {
                fclose(fil);
                printf("\nInsufficient balance! Current balance: %.2f\n\n", acc_read.balance);
                return;
            }
        }
    }

    fclose(fil);
    printf("\nAccount No:%d was not found.\n\n", acc_no);
}

void check_balance()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb");
    if (file == NULL)
    {
        printf("\nError opening file.\n\n");
        return;
    }

    int acc_no;
    Account acc_read;
    printf("Enter your account number to check balance: ");
    scanf("%d", &acc_no);

    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if(acc_read.account_number == acc_no){
            printf("\nYour current balance is: %.2f\n\n", acc_read.balance);
            fclose(file);
            return;
        }
    }

    printf("\nAccount No:%d was not found.\n\n", acc_no);
    fclose(file);
}