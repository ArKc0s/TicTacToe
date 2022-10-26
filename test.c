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
      
        printf("%d ", grid->grid[i]);

    }

    printf("\n");

    displayGrid(grid, size);

}