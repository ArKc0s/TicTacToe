#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SQUARE_SIZE 81


typedef struct MagicSquare
{
    int magicSquare[MAX_SQUARE_SIZE];
    int sum;
} MagicSquare;

void MagicSquare__init(MagicSquare* self, int n) {

    int magicSquare[n][n];
 
    // set all slots as 0
    memset(magicSquare, 0, sizeof(magicSquare));
 
    // Initialize position for 1
    int i = n / 2;
    int j = n - 1;
 
    // One by one put all values in magic square
    for (int num = 1; num <= n * n;) {
        if (i == -1 && j == n) // 3rd condition
        {
            j = n - 2;
            i = 0;
        }
        else {
            // 1st condition helper if next number
            // goes to out of square's right side
            if (j == n)
                j = 0;
 
            // 1st condition helper if next number
            // is goes to out of square's upper side
            if (i < 0)
                i = n - 1;
        }
        if (magicSquare[i][j]) // 2nd condition
        {
            j -= 2;
            i++;
            continue;
        }
        else
            magicSquare[i][j] = num++; // set number
 
        j++;
        i--; // 1st condition
    }

    //memcpy(self->magicSquare, magicSquare, sizeof(self->magicSquare));
    int k = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            self->magicSquare[k] = magicSquare[j][i];
            k++;
        }
    }
    self->sum = (n * (n * n + 1) / 2);

}

MagicSquare* MagicSquare__create(int size) {
    MagicSquare* square = (MagicSquare*) malloc(sizeof(MagicSquare));
    MagicSquare__init(square, size);
    return square;
}

void MagicSquare__reset(MagicSquare* self) {
}


void MagicSquare__destroy(MagicSquare* ms) {
  if (ms) {
     MagicSquare__reset(ms);
     free(ms);
  }
}

void printms(MagicSquare* self) {
    for (int i = 0; i < 25; i++)
    {
        printf("%d ", self->magicSquare[i]);
        
    }
    
}


 
