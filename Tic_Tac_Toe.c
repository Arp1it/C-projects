#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 3
#define X 'X'
#define O 'O'

int difficulty;

typedef struct
{
    int player_x_score;
    int computer_score;
    int draws;
} Score;

Score game_score = {.player_x_score = 0, .computer_score = 0, .draws = 0};

void input_difficulty();
void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

int main()
{
    srand(time(NULL));
    input_difficulty();
    while (1)
    {
        play_game();
        printf("Do you want to play again? (1: Yes, 0: No): ");
        int choice;
        scanf("%d", &choice);
        if (choice == 0)
        {
            break;
        }
    }

    return 0;
}

void play_game()
{
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};

    print_board(board);

    char current_player = rand() % 2 ? X : O;

    while (1)
    {
        if (current_player == X)
        {
            player_move(board);
            print_board(board);
            if (check_win(board, current_player))
            {
                game_score.player_x_score++;
                print_board(board);
                printf("Congratulations! You win!\n");
                break;
            }
            current_player = O;
        }
        else
        {
            computer_move(board);
            print_board(board);
            if (check_win(board, current_player))
            {
                game_score.computer_score++;
                print_board(board);
                printf("Computer wins!\n");
                break;
            }
            current_player = X;
        }

        if (check_draw(board))
        {
            game_score.draws++;
            print_board(board);
            printf("It's a draw!\n");
            break;
        }
    }
}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
    return (row < 1 || row > BOARD_SIZE || col < 1 || col > BOARD_SIZE || board[row - 1][col - 1] != ' ');
}

void player_move(char board[BOARD_SIZE][BOARD_SIZE])
{
    int count = 0, x, y;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if(board[i][j] == ' '){
                count++;
                x = i;
                y = j;
            }
        }
    }
    
    if(count == 1){
        board[x][y] = X;
        return;
    }

    int row, col;

    do
    {
        printf("Player X's Move!\n");
        printf("Enter your move (row and column): ");
        scanf("%d %d", &row, &col);
    } while (is_valid_move(board, row, col));

    board[row - 1][col - 1] = X;
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE])
{
    // 1. Immediate win
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O';
                if (check_win(board, O))
                {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // 1. Immediate block
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'X';
                if (check_win(board, X))
                {
                    board[i][j] = 'O';
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    if(difficulty == 2){
        // 3. Play corner move!
        if(board[1][1] == ' '){
            board[1][1] = O;
            return;
        }

        int corner[4][2] = {
            {0, 0},
            {0, 2},
            {2, 0},
            {2, 2}
        };

        for(int i = 0; i < 4; i++){
            if(board[corner[i][0]][corner[i][1]] == ' '){
                board[corner[i][0]][corner[i][1]] = O;
                return;
            }
        }
    }

    // 5. First Move
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O';
                return;
            }
        }
    }
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return 1;
        }

        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
        {
            return 1;
        }
    }

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    {
        return 1;
    }

    return 0;
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0; // Not a draw, empty space found
            }
        }
    }

    return 1;
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    clear_screen();
    printf("Difficulty Level: %d\n", difficulty);
    printf("Current Score - Player X: %d, Computer: %d, Draws: %d\n", game_score.player_x_score, game_score.computer_score, game_score.draws);
    printf("Tic Tac Toe:\n");

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("\n");
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf(" %c", board[i][j]);

            if (j < BOARD_SIZE - 1)
            {
                printf(" |");
            }
        }

        if (i < BOARD_SIZE - 1)
        {
            printf("\n---+---+---");
        }
    }
    printf("\n\n");
}

void input_difficulty()
{
    while (1)
    {
        printf("Select difficulty level:\n");
        printf("1. Human (Standard)\n");
        printf("2. God Mode (Impossible to Win!)\n");
        printf("3. Two Player Mode!\n");
        printf("Enter your choice: ");
        scanf("%d", &difficulty);

        if (difficulty != 1 && difficulty != 2)
        {
            printf("Invalid choice. Please select 1 or 2.\n");
        }
        else
        {
            break;
        }
    }
}

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}