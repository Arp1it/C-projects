#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
    #include <conio.h> // For Windows
#else
    #include <termios.h> // For Linux/macOS
#endif

#define MAX_USER 10
#define Credential_Length 50

typedef struct
{
    char username[Credential_Length];
    char password[Credential_Length];
} User;

User user[MAX_USER];
int user_count = 0;

void register_user();
int login_user();
void fix_fgets_newline(char *);
void input_cred(char *username, char *password, char *typee);
void delete_user();
void change_password();

int main()
{
    int options;
    printf("Welcome to the User Management System\n");

    while (1)
    {
        printf("1. Register User\n");
        printf("2. Login User\n");
        printf("3. Delete User\n");
        printf("4. Change User Password\n");
        printf("5. Exit\n");
        printf("Please select an option: ");
        scanf("%d", &options);
        getchar(); // Clear the newline character left by scanf

        switch (options)
        {
        case 1:
            register_user();
            break;

        case 2:
        {
            int user_log = login_user();
            if (user_log >= 0)
            {
                printf("\n\nSuccessfully Logged in! Welcome %s\n\n", user[user_log].username);
            }
            else
            {
                printf("\n\nLogin Failed!\n\n");
            }

            break;
        }

        case 3:
            delete_user();
            break;

        case 4:
            change_password();
            break;

        case 5:
            printf("\nExiting!\n");
            return 0;
            break;

        default:
            printf("Invalid Argument!\n\n");
            break;
        }
    }

    return 0;
}

void register_user()
{
    if (user_count >= MAX_USER)
    {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }

    int new_user_index = user_count;
    char tusername[Credential_Length], tpassword[Credential_Length];

    printf("\nRegister User!");

    input_cred(tusername, tpassword, "register");

    if (strcmp(tusername, "") == 0)
    {
        printf("Username cannot be empty.\n");
        return;
    }

    else
    {
        for (int i = 0; i <= user_count; i++)
        {
            if (strcmp(user[i].username, tusername) == 0)
            {
                printf("\n\nUsername already exists. Please choose a different username.\n");
                printf("Registration failed!\n\n");
                return;
            }
        }
    }

    strcpy(user[new_user_index].username, tusername);
    strcpy(user[new_user_index].password, tpassword);

    user_count++;

    printf("\n\nUser %s registered successfully!\n", user[new_user_index].username);
    printf("You can now login with your credentials.\n\n");
}

int login_user()
{
    printf("\nLogin User!");
    char tusername[Credential_Length], tpassword[Credential_Length];

    input_cred(tusername, tpassword, "login");

    for (int i = 0; i <= user_count; i++)
    {
        if (strcmp(user[i].username, tusername) == 0 && strcmp(user[i].password, tpassword) == 0)
        {
            return i; // Return the index of the logged-in user
        }
    }
    return -1;
}

void input_cred(char *username, char *password, char *typee)
{
    if (strcmp(typee, "chpassword") != 0)
    {
        printf("\nEnter Username: ");
        fgets(username, Credential_Length, stdin);
        fix_fgets_newline(username);

        printf("Enter Password (masking enabled): ");
    }

    else if(strcmp(typee, "chpassword") == 0)
    {
        printf("\nEnter New Password (masking enabled): ");
    }

    #ifdef _WIN32
        // Change terminal settings to disable echo for Windows
        char ch;
        int i = 0;

        while ((ch = getch()) != '\r' && ch != EOF)
        { // Use getch() to read without echo
            if (ch == '\b' && i > 0)
            {
                i--;
                printf("\b \b"); // Handle backspace
            }

            else
            {
                password[i++] = ch;
                printf("*"); // Print asterisk for each character
            }
        }

        password[i] = '\0'; // Null-terminate the password string

    #else
        // Change terminal settings to disable echo for linux/macOS
        struct termios old_prop, new_prop;
        tcgetattr(STDIN_FILENO, &old_prop);
        new_prop = old_prop;
        new_prop.c_lflag = ~(ECHO | ICANON); // Disable echo and canonical mode
        tcsetattr(STDIN_FILENO, TCSANOW, &new_prop);

        char ch;
        int i = 0;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ; // Clear any leftover input
        {
            if (ch == '\b' && i > 0)
            {
                i--;
                printf("\b \b"); // Handle backspace
            }
            else if (ch != '\b')
            {
                password[i++] = ch;
                printf("*");
            }
        }
        password[i] = '\0'; // Null-terminate the password string

        tcsetattr(STDIN_FILENO, TCSANOW, &old_prop); // Restore old terminal settings

    #endif
}

void fix_fgets_newline(char *str)
{
    int index = strcspn(str, "\n");
    str[index] = '\0'; // Replace newline character with null terminator
    if (index == 0)
    {
        printf("Input cannot be empty.\n\n");
    }
}

void delete_user()
{
    char tusername[Credential_Length], tpassword[Credential_Length];
    printf("\nDelete User!");
    input_cred(tusername, tpassword, "delete");

    for (int i = 0; i <= user_count; i++)
    {
        if (strcmp(user[i].username, tusername) == 0 && strcmp(user[i].password, tpassword) == 0)
        {
            // Shift users left to overwrite the one being deleted
            for (int j = i; j <= user_count - 1; j++)
            {
                user[j] = user[j + 1];
            }
            user_count--;
            printf("\nUser '%s' deleted successfully.\n\n", tusername);
            return;
        }
    }
    printf("\n\nUser not found or password incorrect.\n\n");
}

void change_password()
{
    char tusername[Credential_Length], old_password[Credential_Length], new_password[Credential_Length];
    input_cred(tusername, old_password, "login");

    for (int i = 0; i <= user_count; i++)
    {
        if (strcmp(user[i].username, tusername) == 0 && strcmp(user[i].password, old_password) == 0)
        {
            input_cred(tusername, new_password, "chpassword");
            strcpy(user[i].password, new_password);
            printf("\nPassword changed successfully for user '%s'.\n\n", tusername);
            return;
        }
    }

    printf("\n\nUser not found or password incorrect.\n\n");
}