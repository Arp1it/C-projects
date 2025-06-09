#include <stdio.h>

int puzzel[9][9] = {
    {3, 0, 0, 0, 2, 0, 0, 7, 0},
    {9, 0, 0, 5, 0, 0, 0, 1, 4},
    {0, 1, 6, 3, 7, 0, 0, 0, 8},
    {2, 0, 0, 8, 0, 0, 0, 0, 1},
    {5, 0, 0, 0, 4, 1, 8, 0, 0},
    {0, 8, 9, 0, 0, 0, 0, 5, 0},
    {0, 0, 5, 0, 1, 0, 2, 8, 0},
    {0, 4, 0, 0, 0, 6, 0, 9, 3},
    {7, 3, 1, 0, 8, 2, 0, 0, 0},
};

void print_puzzel(int puzzel[9][9]);
int is_valid_puzzel(int puzzel[9][9]);
int valid_move(int puzzel[9][9], int row, int column, int val);
int solve_puzzel(int puzzel[9][9], int row, int col);

int main()
{
    print_puzzel(puzzel);

    if (!is_valid_puzzel(puzzel)){
        printf("\nPuzzel is not valid!");
        return 0;
    }

    if (solve_puzzel(puzzel, 0, 0)){
        printf("\nSoved Puzzel:\n");
        print_puzzel(puzzel);
    }

    else{
        printf("\nThe Puzzel is not Solvable\n");
    }
    return 0;
}


int is_valid_puzzel(int puzzel[9][9]){
    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){

            int val = puzzel[row][col];

            if (val != 0){
                puzzel[row][col] = 0;

                if (!valid_move(puzzel, row, col, val)){
                    puzzel[row][col] = val;
                    return 0;
                }

                puzzel[row][col] = val;
            }
        }
    }

    return 1;
}


int solve_puzzel(int puzzel[9][9], int row, int col){
    if (col == 9){
        if (row == 8){
            return 1;
        }

        row++;
        col = 0;
    }

    if (puzzel[row][col] > 0){
        return solve_puzzel(puzzel, row, col+1);
    }

    for (int i = 1; i <= 9; i++)
    {
        if(valid_move(puzzel, row, col, i)){
            puzzel[row][col] = i;

            if (solve_puzzel(puzzel, row, col+1)){
                return 1;
            }
            puzzel[row][col] = 0;
        }
    }
    
    return 0;
}


int valid_move(int puzzel[9][9], int row, int column, int val){

    for (int i = 0; i < 9; i++){
        if(puzzel[row][i] == val){
            return 0;
        }
    }

    for (int i = 0; i<9; i++){
        if(puzzel[i][column] == val){
            return 0;
        }
    }

    int r = row - row % 3;
    int c = column - column % 3;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (puzzel[r+i][c+j] == val){
                return 0;
            }
        }
    }

    return 1;
}

void print_puzzel(int puzzel[9][9])
{
    printf("+-------+-------+-------+\n");
    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            printf("|-------+-------+-------|\n");
        }
        printf("| ");
        for (int colmn = 0; colmn < 9; colmn++)
        {
            if (colmn % 3 == 0 && colmn != 0)
            {
                printf("| ");
            }

            if (puzzel[row][colmn] == 0)
            {
                printf("  ");
            }

            else
            {
                printf("%d ", puzzel[row][colmn]);
            }
        }
        printf("|");
        printf("\n");
    }
    printf("+-------+-------+-------+");
}