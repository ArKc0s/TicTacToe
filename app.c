#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

char squarePattern[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char square[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char mark;

// Valeurs du carré magique (utilisé dans la détection de victoire)
int magicSquare[9] = {4, 9, 2, 3, 5, 7, 8, 1, 6};
// Egalitée = 0 | Victoire J1 = 1 | Victoire J2 = 2 | En cours = -1
int gameState;
// Joueur 1 = nombre impair | Joueur 2 = nombre pair
int playerTurn;
// Nombre de coups joués
int movesPlayed;
// Case sélectionnée
int choice;
// Scores
int scorePlayer1 = 0;
int scorePlayer2 = 0;

// Choix dans le menu d'initialisation
int choiceMenu;

// Prototypes de fonctions
int oneVersusOneGame(void);
void board(void);
int printWinner(void);



int main()
{
    // Print the menu
    printf("Welcome to the Tic Tac Toe game !\n");
    printf("1. Start a new game\n");
    printf("0. Quit\n");
    printf("Please enter your choice: ");

    // Get the user choice
    scanf("%d", &choiceMenu);

    // Check if the user choice is valid
    if (choiceMenu == 1)
    {

        do
        {
            int game = oneVersusOneGame();

            if (game == 1)
            {
                scorePlayer1++;
            }
            else if (game == 2)
            {
                scorePlayer2++;
            }
            printf("Player 1 score: %d\n", scorePlayer1);
            printf("Player 2 score: %d\n", scorePlayer2);

            printf("Do you want to play again ? (1 = yes, 0 = no)\n");
            scanf("%d", &choiceMenu);

        } while (choiceMenu == 1);
        // Start the game
    }
    else if (choiceMenu == 0)
    {
        // Quit the game
        return 0;
    }
    else
    {
        // Invalid choice
        printf("Invalid choice !\n");
        return 0;
    }

}

int oneVersusOneGame()
{
    gameState = -1;
    playerTurn = 1;
    movesPlayed = 0;
    memcpy(square, squarePattern, sizeof(squarePattern));

    do
    {
        board();
        playerTurn = (playerTurn % 2) ? 1 : 2;

        printf("Joueur %d, entrez un nombre: ", playerTurn);
        scanf("%d", &choice);

        mark = (playerTurn == 1) ? 'X' : 'O';

        if (choice == 1 && square[0] == '1')
            square[0] = mark;

        else if (choice == 2 && square[1] == '2')
            square[1] = mark;

        else if (choice == 3 && square[2] == '3')
            square[2] = mark;

        else if (choice == 4 && square[3] == '4')
            square[3] = mark;

        else if (choice == 5 && square[4] == '5')
            square[4] = mark;

        else if (choice == 6 && square[5] == '6')
            square[5] = mark;

        else if (choice == 7 && square[6] == '7')
            square[6] = mark;

        else if (choice == 8 && square[7] == '8')
            square[7] = mark;

        else if (choice == 9 && square[8] == '9')
            square[8] = mark;

        else
        {
            printf("Case invalide");
            playerTurn--;
            movesPlayed--;
        }

        movesPlayed++;

        gameState = printWinner();

        if (movesPlayed == 9 && gameState == -1){
            printf("Egalitée !\n");
            gameState = 0;
        }

        playerTurn++;

    } while (gameState == -1);

    board();

    return gameState;
}

// Affichage de la grille
void board()
{
    system("clear");
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

// Détection de victoire
bool hasWon(char player)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 9; k++)
            {
                if (i != j && i != k && j != k)
                {
                    if (square[i] == player && square[j] == player && square[k] == player)
                    {
                        if (magicSquare[i] + magicSquare[j] + magicSquare[k] == 15)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Affichage Victoire
int printWinner()
{
    if (hasWon('X'))
    {
        gameState = 1;
        printf("Le joueur 1 (X) gagne la partie !");
        return 1;
    }
    else if (hasWon('O'))
    {
        gameState = 1;
        printf("Le joueur 2 (O) gagne la partie !");
        return 2;
    }
    return -1;
}