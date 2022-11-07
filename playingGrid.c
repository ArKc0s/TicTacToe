#include <stdio.h>
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

void PlayingGrid__reset(PlayingGrid* self) {
}


void PlayingGrid__destroy(PlayingGrid* pg) {
  if (pg) {
     PlayingGrid__reset(pg);
     free(pg);
  }
}

void displayGrid(PlayingGrid* self, int size) {

    //system("clear");
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

int numInRow = 0;
int prevVal = 0;

int countNumInRow(PlayingGrid* self, int size,int winCondition, int index) {

    int curVal = (self->grid[index][0] == 'X') ? 1 : (self->grid[index][0] == 'O') ? 2 : 0;
    if(curVal != prevVal || curVal == 0) {
        prevVal = curVal;
        numInRow = 1;
    } else {
        numInRow++;
        if(numInRow >= winCondition) {
            return curVal;
        }
    }

    return -1;
}

int winDetect(PlayingGrid* self, int size, int winCondition) {

    int result;

    //colonnes
    for(int x = 0; x < size; x++) {
       prevVal=0;
        for(int y = 0; y < size; y++) {
            result = countNumInRow(self, size, winCondition, x+(size*y));
            if(result != -1) {
                return result;
            }
        }
    }

    //lignes
    for(int y = 0; y < size; y++) {
        prevVal = 0;
        for(int x = 0; x < size; x++) {
            result = countNumInRow(self, size, winCondition, x+(size*y));
            if(result != -1) {
                return result;
            }
        }
    }

    //diag sup droite
    for(int x=0; x < size; x++) {
        prevVal = 0;
        for(int i=x; i < (size*size) - (x*size) ; i+=size+1) {
            result = countNumInRow(self, size, winCondition, i);
            if(result != -1) {
                return result;
            }
        }
    }

    //diag inf droite
    for(int y=1; y < size; y++) {
        prevVal = 0;
        for(int i=y*size; i < (size*size) - y ; i+=size+1) {
            result = countNumInRow(self, size, winCondition, i);
            if(result != -1) {
                return result;
            }
        }
    }

    //diag sup gauche
    for(int x=0; x < size; x++) {
        prevVal = 0;

        for(int i=x; i < x*size+1 ; i+=size-1) {
            result = countNumInRow(self, size, winCondition, i);
            if(result != -1) {
                return result;
            }
        }
    }

    //diag inf gauche
    for(int y=1; y < size; y++) {
        prevVal = 0;
        for(int i=(y+1)*(size)-1; i < size*size ; i+=size-1) {
            result = countNumInRow(self, size, winCondition, i);
            if(result != -1) {
                return result;
            }
        }
    }

    return -1;

}

bool isPlayable(int cell, char grid[][2], int size) {
    if(cell >= 0 && cell <= size-1 && grid[cell][0] != 'X' && grid[cell][0] != 'O') {
        return true;
    }
    return false;
}

