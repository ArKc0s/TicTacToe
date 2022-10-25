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