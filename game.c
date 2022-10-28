#include "magicSquare.c"
#include "playingGrid.c"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

typedef struct Game
{
    int gameState;
    int playerTurn;
    int movesCount;
    int gameType;
    int size;
    MagicSquare* ms;
    PlayingGrid* pg;

} Game;


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

int oneVersusOneGame(Game* self)
{

    int choice;
    char mark;
    
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

        int test[2];
        hasWon(self->pg->gridNumbers, test, 0, (self->size*self->size)-1, 0, self->size, 'O', self->ms, self->pg);
        hasWon(self->pg->gridNumbers, test, 0, (self->size*self->size)-1, 0, self->size, 'X', self->ms, self->pg);

        self->gameState = self->pg->isWon;
        
        if (self->movesCount == self->size*self->size && self->gameState == -1){
            printf("Egalitée !\n");
            self->gameState = 0;
        }
      
        self->playerTurn++;

    } while (self->gameState == -1);

    displayGrid(self->pg, self->size);

    return self->gameState;
}

int oneVersusComputerGame(Game* self) {

    int choice;
    char mark;

    pthread_t computer;
    void *computerChoice = NULL;

    srand(time(0));

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
            }

            else
            {
                printf("Case invalide");
                self->playerTurn--;
                self->movesCount--;
            }
             
        } else {

            
            do {
                choice = rand() % (self->size*self->size + 1);
                printf("%d ", choice);
            } while(!isPlayable(choice - 1, self->pg->grid, self->size*self->size));

            self->pg->grid[choice-1][0] = mark;
            self->pg->grid[choice-1][1] = ' ';

            //assert(pthread_create(&computer, NULL, computerPlay, NULL) == 0);
            //pthread_join(computer, &computerChoice);
            //square[(int) computerChoice] = mark;

        }

        self->movesCount++;

        int test[2];
        hasWon(self->pg->gridNumbers, test, 0, (self->size*self->size)-1, 0, self->size, 'O', self->ms, self->pg);
        hasWon(self->pg->gridNumbers, test, 0, (self->size*self->size)-1, 0, self->size, 'X', self->ms, self->pg);

        self->gameState = self->pg->isWon;

        if (self->movesCount == self->size*self->size && self->gameState == -1){
            printf("Egalitée !\n");
            self->gameState = 0;
        }

        self->playerTurn++;

    } while (self->gameState == -1);

    displayGrid(self->pg, self->size);

    return self->gameState;

}


int startGame(Game* self) {

    if(self->gameType == 1) {
        return oneVersusOneGame(self);
    } else if(self->gameType == 2) {
        return oneVersusComputerGame(self);
    }

}





/*void *computerPlay() {
    int play;

    do {
        play = randomNumber(0, 8);
    } while(!isPlayable(play+1));

    pthread_exit((void *) (play));
}*/