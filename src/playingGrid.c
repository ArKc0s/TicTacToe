#include "app.h"

//Décalration de variables globales pour la détection de victoire
int numInRow = 0;
int prevVal = 0;

void PlayingGrid__init(playingGrid_t* self, int size) {

    int length = snprintf( NULL, 0, "%d", size);
    char* str = malloc( length + 1 );

    //Initialisaiton des nombres dans la grille, sous forme de char pour l'affichage
    for(int k = 0; k < size; k++) {

        snprintf(str, length + 1, "%d", k+1 );
        
        self->grid[k][0] = str[0];
        self->grid[k][1] = str[1];
        
    }

    free(str);
}

playingGrid_t* PlayingGrid__create(int size) {
    playingGrid_t* pGrid = (playingGrid_t*) malloc(sizeof(playingGrid_t));
    PlayingGrid__init(pGrid, size);
    return pGrid;
}

void PlayingGrid__reset(playingGrid_t* self) {
}

void PlayingGrid__destroy(playingGrid_t* pg) {
  if (pg) {
     PlayingGrid__reset(pg);
     free(pg);
  }
}

void displayGrid(playingGrid_t* self, int size) {

    system("cls");
    printf("\n\n\tTic Tac Toe\n\n");

    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");

    int j;

    //Boucle d'itération des lignes
    for(int row = 0; row < size; row++) {

        //Affichage de la première partie de chaque line (ex:      |     |     )
        for(int i = 0; i < size-1; i++) {
            printf("     |");
        }
        printf("     \n");

        //Affichage de la première partie de chaque line (ex:  1  |  2  |  3  )
        for(j = 0; j < size-1; j++) {
            //distinction de cas selon chiffre ou nombre >= 10 
            if(self->grid[j + (row*size)][1] == '\0') {
                printf("  %c  |", self->grid[j + (row*size)][0]);
            } else {
                printf("  %c%c |", self->grid[j + (row*size)][0], self->grid[j + (row*size)][1]);
            }
            
        }
        //Affichage du dernier chiffre
        printf("  %c%c \n", self->grid[j + (row*size)][0], self->grid[j + (row*size)][1]);
    

        //Si l'on est pas à la dernière ligne on affiche un séparateur de ligne
        if(row != size-1) {
            for(int i = 0; i < size-1; i++) {
                printf("_____|");
            }
            //retour à la ligne pour le dernier
            printf("_____\n");
        //Sinon, denrière ligne, pas de séparateur
        } else {
            for(int i = 0; i < size-1; i++) {
                printf("     |");
            }
            printf("     \n\n");
        }
       
    }
}

int countNumInRow(playingGrid_t* self, int size, int winCondition, int index) {

    //Parse de l'identifiant du joueur (int) grace au symbole présent dans la case, si pas jouée alors 0
    int curVal = (self->grid[index][0] == 'X') ? 1 : (self->grid[index][0] == 'O') ? 2 : 0;
    //Si la valeur courante n'est pas égale à la précédente alors on es tplus dans une suite de même carractère, on réinitialise le nombre de symboles à la suite à 1
    if(curVal != prevVal || curVal == 0) {
        prevVal = curVal;
        numInRow = 1;
    //Sinon, on est toujours dans la meme suite alors on incrémente le nombre de symboles à la suite
    } else {
        numInRow++;
        // Détection d'une victoire
        if(numInRow >= winCondition) {
            return curVal;
        }
    }

    //Aucune victoire détectée
    return -1;
}

int detectWin(playingGrid_t* self, int size, int winCondition) {

    //resultat de la partie
    int result;

    //parcours en colonnes
    for(int x = 0; x < size; x++) {
       prevVal=0;
        for(int y = 0; y < size; y++) {
            result = countNumInRow(self, size, winCondition, x+(size*y));
            if(result != -1) {
                return result;
            }
        }
    }

    //parcours en lignes
    for(int y = 0; y < size; y++) {
        prevVal = 0;
        for(int x = 0; x < size; x++) {
            result = countNumInRow(self, size, winCondition, x+(size*y));
            if(result != -1) {
                return result;
            }
        }
    }

    //parcours diagonale supérieure droite
    for(int x=0; x < size; x++) {
        prevVal = 0;
        for(int i=x; i < (size*size) - (x*size) ; i+=size+1) {
            result = countNumInRow(self, size, winCondition, i);
            if(result != -1) {
                return result;
            }
        }
    }

    //parcours diagonale inférieure droite
    for(int y=1; y < size; y++) {
        prevVal = 0;
        for(int i=y*size; i < (size*size) - y ; i+=size+1) {
            result = countNumInRow(self, size, winCondition, i);
            if(result != -1) {
                return result;
            }
        }
    }

    //parcours diagonale supérieure gauche
    for(int x=0; x < size; x++) {
        prevVal = 0;

        for(int i=x; i < x*size+1 ; i+=size-1) {
            result = countNumInRow(self, size, winCondition, i);
            if(result != -1) {
                return result;
            }
        }
    }

    //parcours diagonale inférieure gauche
    for(int y=1; y < size; y++) {
        prevVal = 0;
        for(int i=(y+1)*(size)-1; i < size*size ; i+=size-1) {
            result = countNumInRow(self, size, winCondition, i);
            if(result != -1) {
                return result;
            }
        }
    }

    //pas de victoire, la partie doit continuer
    return -1;

}

bool isPlayable(int cell, char grid[][2], int size) {
    //Si symbole X ou O absent alors la case est jouable
    if(cell >= 0 && cell <= size-1 && grid[cell][0] != 'X' && grid[cell][0] != 'O') {
        return true;
    }
    return false;
}

