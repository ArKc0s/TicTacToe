#include<stdio.h>
#include <stdbool.h>

#define MAX_GRID_SIZE 81


typedef struct PlayingGrid
{
    char grid[MAX_GRID_SIZE][2];
    int gridNumbers[MAX_GRID_SIZE];
    int isWon;

} PlayingGrid;

void PlayingGrid__init(PlayingGrid* self, int size) {

    int length = snprintf( NULL, 0, "%d", size);
    char* str = malloc( length + 1 );

    for(int k = 0; k < size; k++) {

        snprintf(str, length + 1, "%d", k+1 );
        
        self->grid[k][0] = str[0];
        self->grid[k][1] = str[1];

        self->gridNumbers[k] = k;
        
    }

    free(str);

    self->isWon = -1;
}

PlayingGrid* PlayingGrid__create(int size) {
    PlayingGrid* pGrid = (PlayingGrid*) malloc(sizeof(PlayingGrid));
    PlayingGrid__init(pGrid, size);
    return pGrid;
}

void displayGrid(PlayingGrid* self, int size) {

    system("clear");
    printf("\n\n\tTic Tac Toe\n\n");

    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");

    int j;

    for(int row = 0; row < size; row++) {

        for(int i = 0; i < size-1; i++) {
            printf("     |");
        }
        printf("     \n");
        
        for(j = 0; j < size-1; j++) {
            if(self->grid[j + (row*size)][1] == '\0') {
                printf("  %c  |", self->grid[j + (row*size)][0]);
            } else {
                printf("  %c%c |", self->grid[j + (row*size)][0], self->grid[j + (row*size)][1]);
            }
            
        }
        printf("  %c%c \n", self->grid[j + (row*size)][0], self->grid[j + (row*size)][1]);
    

        if(row != size-1) {
            for(int i = 0; i < size-1; i++) {
                printf("_____|");
            }
             printf("_____\n");
        } else {
            for(int i = 0; i < size-1; i++) {
                printf("     |");
            }
            printf("     \n\n");
        }
       
    }
}

void printWin(char player, PlayingGrid* self)
{
    if (player == 'X')
    {
        //gameState = 1;
        printf("Le joueur 1 (X) gagne la partie !");
        self->isWon = 1;
    }
    else if (player == 'O')
    {
        //gameState = 1;
        printf("Le joueur 2 (O) gagne la partie !");
        self->isWon = 2;
    }
}

void hasWon(int arr[], int data[], int start, int end,
                     int index, int r, char player, MagicSquare* ms, PlayingGrid* self) {
    
    // Current combination is ready to be printed, print it
    if (index == r)
    {
        int sum = 0;
        bool playerFound;
        for (int j=0; j<r; j++) {

            playerFound = true;

            if(self->grid[data[j]][0] != player) {
                playerFound = false;
            } 

        }

        if(playerFound) {
            for(int j = 0; j<r; j++) {
                sum+=ms->magicSquare[data[j]];
            }

            if(sum == ms->sum) {
                printWin(player, self);
            }
        }
        return;
    }
 
    // replace index with all possible elements. The condition
    // "end-i+1 >= r-index" makes sure that including one element
    // at index will make a combination with remaining elements
    // at remaining positions
    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        //On ne vérifie pas une combinaison si la première case vérifiée ne contient pas le joueur
        if(self->grid[arr[i]][0] != player) {
            continue;
        }
        hasWon(arr, data, i+1, end, index+1, r, player, ms, self);
    }
}

bool isPlayable(int cell, char grid[][2], int size) {
    if(cell >= 0 && cell <= size-1 && grid[cell][0] != 'X' && grid[cell][0] != 'O') {
        return true;
    }
    return false;
}

