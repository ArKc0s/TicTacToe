#include <stdbool.h>
#include "magicSquare.c"
#include "playingGrid.c"

int size;

int main() {

    size = 9;

    MagicSquare* ms = MagicSquare__create(size);
    PlayingGrid* grid = PlayingGrid__create(size*size);

    printf("%d", ms->sum);
    printf("\n");

    for(int i = 0; i < 9; i++) {
      
        printf("%d ", ms->magicSquare[i]);

    }

    printf("\n");

    for(int i = 0; i < 9; i++) {
      
        printf("%c ", grid->gridNumbers[i]);

    }

    printf("\n");

    //displayGrid(grid, size);

    for(int i = 0; i < size; i++) {
        grid->grid[size*i][0] = 'O';
        grid->grid[size*i][1] = '\0';
    }

    displayGrid(grid, size);
   
    int test[size];
    hasWon(grid->gridNumbers, test, 0, (size*size)-1, 0, size, 'O', grid->grid, ms);
    hasWon(grid->gridNumbers, test, 0, (size*size)-1, 0, size, 'X', grid->grid, ms);

   

}