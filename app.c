#include <stdio.h>
#include <stdbool.h>


char square[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9' };
int magicSquare[9] = {4, 9, 2, 3, 5, 7, 8, 1, 6};

//Non démarrée = 0 | Joueur 1 = 1 | Joueur 2 = 2 | Finie = -1
int gameState = 0;

int main () {

}

//Affichage de la grille
void board()
{
    system("cls");
    printf("\n\n\tTic Tac Toe\n\n");

    printf("Joueur 1 (X)  -  Joueur 2 (O)\n\n\n");


    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[0], square[1], square[2]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[3], square[4], square[5]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[6], square[7], square[8]);

    printf("     |     |     \n\n");
}

//Détection de victoire
bool hasWon(char player) {
    for(int i = 0; i <9; i++) {
        for(int j = 0; j < 9; j++) {
            for(int k = 0; k < 9; k++) {
                if(i != j && i != k && j != k) {
                    if(square[i] == player && square[j] == player && square[k] == player) {
                        if(magicSquare[i] + magicSquare[j] + magicSquare[k] == 15) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

//Affichage Victoire
void printWinner() {
    if(hasWon('X')) {
        gameState = 1;
        printf("Le joueur 1 (X) gagne la partie !");
    } else if(hasWon('O')) {
        gameState = 1;
        printf("Le joueur 2 (O) gagne la partie !");
    }
    
}