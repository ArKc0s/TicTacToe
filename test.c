#include "magicSquare.c"
#include "playingGrid.c"

int main() {
    MagicSquare* ms = MagicSquare__create(5);
    PlayingGrid* grid = PlayingGrid__create(5*5);

    printf("%d", ms->sum);
    printf("\n");

    for(int i = 0; i < 25; i++) {
      
        printf("%d ", ms->magicSquare[i]);

    }

    printf("\n");

    for(int i = 0; i < 25; i++) {
      
        printf("%d ", grid->grid[i]);

    }
}