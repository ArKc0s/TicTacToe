#include "magicSquare.c"
#include "playingGrid.c"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <assert.h>
#include <pthread.h>

typedef struct Game {
    int gameState;
    int playerTurn;
    int movesCount;
    int gameType;
    int size;
    MagicSquare* ms;
    PlayingGrid* pg;

} Game;

struct Data {
    PlayingGrid* pg ;
    int size;
    char mark;
};

pthread_mutex_t mutex;
char mark;
int choice;

void Game__init(Game* self, int type, int size) {

    self->gameState = -1;
    self->playerTurn = 1;
    self->movesCount = 0;
    self->gameType = type;
    self->ms = MagicSquare__create(size);
    self->pg = PlayingGrid__create(size*size);
    self->size = size;

}

Game* Game__create(int type, int gridSize) {
    Game* game = (Game*) malloc(sizeof(Game));
    Game__init(game, type, gridSize);
    return game;
}

void Game__reset(Game* self) {
    PlayingGrid__reset(self->pg);
    MagicSquare__reset(self->ms);
}


void Game__destroy(Game* game) {
  if (game) {
    PlayingGrid__destroy(game->pg);
    MagicSquare__destroy(game->ms);
    Game__reset(game);
    free(game);
  }
}

long long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/100;
    return milliseconds;
}


void randomPlay(PlayingGrid* pg, int size, char mark) {
      
    do {
        choice = rand() % (size*size + 1);
    } while(!isPlayable(choice - 1, pg->grid, size*size));

    pg->grid[choice-1][0] = mark;
    pg->grid[choice-1][1] = ' ';
}

void *critique(void *data) {

    struct Data *d  = data;

    pthread_mutex_lock(&mutex);
    srand(current_timestamp());
    randomPlay(d->pg, d->size, d->mark);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void detectWin(Game* self, int buffer[]) {
    
        hasWon(self->pg->gridNumbers, buffer, 0, (self->size*self->size)-1, 0, self->size, 'O', self->ms, self->pg);
        hasWon(self->pg->gridNumbers, buffer, 0, (self->size*self->size)-1, 0, self->size, 'X', self->ms, self->pg);

        self->gameState = self->pg->isWon;

        if (self->movesCount == self->size*self->size && self->gameState == -1){
            printf("Egalitée !\n");
            self->gameState = 0;
        }

        self->playerTurn++;

        printf("\n");
}

int oneVersusOneGame(Game* self)
{

    int choice;
    
    do
    {
        displayGrid(self->pg, self->size);
        self->playerTurn = (self->playerTurn % 2) ? 1 : 2;    


        printf("Joueur %d, entrez un nombre: ", self->playerTurn);
        scanf("%d", &choice);

        mark = (self->playerTurn == 1) ? 'X' : 'O';

        if(isPlayable(choice-1, self->pg->grid, self->size*self->size)) {
            self->pg->grid[choice-1][0] = mark;
            self->pg->grid[choice-1][1] = ' ';
        }

        else
        {
            printf("Case invalide");
            self->playerTurn--;
            self->movesCount--;
        }

        self->movesCount++;

        int buffer[2];
        detectWin(self, buffer);

    } while (self->gameState == -1);

    displayGrid(self->pg, self->size);

    return self->gameState;
}

int oneVersusComputerGame(Game* self) {

    int choice;

    do {
        displayGrid(self->pg, self->size);
        self->playerTurn = (self->playerTurn % 2) ? 1 : 2;
        mark = (self->playerTurn == 1) ? 'X' : 'O';

        if(self->playerTurn == 1) {

            printf("Joueur %d, entrez un nombre: ", self->playerTurn);
            scanf("%d", &choice);

            if(isPlayable(choice-1, self->pg->grid, self->size*self->size)) {
                self->pg->grid[choice-1][0] = mark;
                self->pg->grid[choice-1][1] = ' ';
            } else {
                printf("Case invalide");
                self->playerTurn--;
                self->movesCount--;
            }             
        } else {
            randomPlay(self->pg, self->size, mark);
        }

        self->movesCount++;

        int buffer[2];
        detectWin(self, buffer);

    } while (self->gameState == -1);

    displayGrid(self->pg, self->size);

    return self->gameState;

}

int computerVersusComputerGame(Game* self) {

    pthread_t j1, j2;
    struct Data d1, d2;

    pthread_mutex_init(&mutex, NULL);
    do {
        self->playerTurn = (self->playerTurn % 2) ? 1 : 2;


        if(self->playerTurn == 1) {

            d1.pg = self->pg;
            d1.size = self->size;
            d1.mark = 'X';
            pthread_create(&j1, NULL, critique, (void *) &d1);
            pthread_join(j1, NULL);
             
        } else {

            d2.pg = self->pg;
            d2.size = self->size;
            d2.mark = 'O';

            pthread_create(&j2, NULL, critique, (void *) &d2);
            pthread_join(j2, NULL);

        }

        self->movesCount++;

        int buffer[2];
        detectWin(self, buffer);

    } while (self->gameState == -1);

    displayGrid(self->pg, self->size);
    pthread_mutex_destroy(&mutex);

    return self->gameState;

}


int startGame(Game* self) {

    if(self->gameType == 1) {
        return oneVersusOneGame(self);
    } else if(self->gameType == 2) {
        return oneVersusComputerGame(self);
    } else if(self->gameType == 3) {
        return computerVersusComputerGame(self);
    }

}
