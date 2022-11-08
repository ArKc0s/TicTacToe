#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

// Prototypes de fonctions
int oneVersusOneGame(void);
void board(void);
int printWinner(void);
int oneVersusComputerGame(void);
bool isPlayable(int);
int randomNumber(int, int);
void *computerPlay(void);


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

// Fonction de jeu principale
int main()
{
    // Print the menu
    printf("Welcome to the Tic Tac Toe game !\n");
    printf("1. Start a new game\n");
    printf("2. Start a new game against computer\n");
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
    else if(choiceMenu == 2) {

        do
        {
            int game = oneVersusComputerGame();

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

// Fonction de jeu Joueur 1 vs Joueur 2
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

        if(isPlayable(choice)) {
            square[choice-1] = mark;
        }

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

// Fonction de jeu Joueur 1 vs Ordinateur
int oneVersusComputerGame() {

    pthread_t computer;
    void *computerChoice = NULL;

    movesPlayed = 0;
    gameState = -1;
    playerTurn = 1;
    memcpy(square, squarePattern, sizeof(squarePattern));

     do
    {
        board();
        playerTurn = (playerTurn % 2) ? 1 : 2;
        mark = (playerTurn == 1) ? 'X' : 'O';

        if(playerTurn == 1) {

            printf("Joueur %d, entrez un nombre: ", playerTurn);
            scanf("%d", &choice);

            if(isPlayable(choice)) {
                square[choice-1] = mark;
            }

            else
            {
                printf("Case invalide");
                playerTurn--;
                movesPlayed--;
            }
             
        } else {

            assert(pthread_create(&computer, NULL, computerPlay, NULL) == 0);
            pthread_join(computer, &computerChoice);
            square[(int) computerChoice] = mark;

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

// Vérification de la validité du choix
bool isPlayable(int cellNumber) {

    if (cellNumber == 1 && square[0] == '1')
        return true;

    else if (cellNumber == 2 && square[1] == '2')
       return true;

    else if (cellNumber == 3 && square[2] == '3')
        return true;

    else if (cellNumber == 4 && square[3] == '4')
        return true;

    else if (cellNumber == 5 && square[4] == '5')
        return true;

    else if (cellNumber == 6 && square[5] == '6')
        return true;

    else if (cellNumber == 7 && square[6] == '7')
        return true;

    else if (cellNumber == 8 && square[7] == '8')
        return true;

    else if (cellNumber == 9 && square[8] == '9')
        return true;

    return false;
}

// Génération de nombre aléatoire
int randomNumber(int min_num, int max_num) {
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num) {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

// Fonction de jeu Ordinateur vs Ordinateur
void *computerPlay() {
    int play;

    do {
        play = randomNumber(0, 8);
    } while(!isPlayable(play+1));

    pthread_exit((void *) (play));
}

