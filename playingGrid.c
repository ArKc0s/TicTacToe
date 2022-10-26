#include<stdio.h>

#define MAX_GRID_SIZE 81


typedef struct PlayingGrid
{
    int grid[MAX_GRID_SIZE];

} PlayingGrid;

void PlayingGrid__init(PlayingGrid* self, int size) {

    for(int k = 0; k < size; k++) {
        self->grid[k] = k+1;
    }
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
            if(self->grid[j + (row*size)] > 9) {
                printf("  %d |", self->grid[j + (row*size)]);
            } else {
                printf("  %d  |", self->grid[j + (row*size)]);
            }
            
        }
        printf("  %d \n", self->grid[j + (row*size)]);
    

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