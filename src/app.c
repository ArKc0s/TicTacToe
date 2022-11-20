#include "app.h"

// Scores
int gameResult;
int scorePlayer1 = 0;
int scorePlayer2 = 0;
int draw = 0;

// Choix dans le menu d'initialisation
int choiceMenu;
int gridSize;
int winCondition;
int firstPlayer;
int isLogged;

//Instance de jeu
game_t* game;

struct stat st = {0};

// Fonction de jeu principale
int main() {

    if (stat("games", &st) == -1) {
        mkdir("games", 0700);
    }

    // Affichage du menu
    printf("Welcome to the Tic Tac Toe game !\n");
    printf("1. Demarrer une partie 1vs\n");
    printf("2. Demarrer une partie contre l'ordinateur\n");
    printf("3. Demarrer une partie ordinateur contre ordinateur\n");
    printf("0. Quitter\n");
    printf("Entrez votre choix: ");

    scanf("%d", &choiceMenu);

    if(choiceMenu == 0) {
        return 0;
    }

    do {
        system("cls");
        printf("Choix de la taille de la grille (3, 5, 7 ou 9) : ");
        scanf("%d", &gridSize);
    } while (gridSize != 3 && gridSize !=5 && gridSize != 7 && gridSize != 9);
    
    do {
        system("cls");
        printf("Choix du nombre de symbole a aligner pour gagner (inferieur a la taille de jeu) : ");
        scanf("%d", &winCondition);
    } while(winCondition > gridSize);

    do {
        system("cls");
        printf("Choix du premier joueur (1 ou 2) : ");
        scanf("%d", &firstPlayer);
    } while(firstPlayer != 1 && firstPlayer != 2);

    do {
        system("cls");
        printf("Voulez vous enregistrer la partie ? (1 = Oui, 0 = Non): ");
        scanf("%d", &isLogged);
    } while(isLogged != 1 && isLogged != 0);

    bool isLoggedB = isLogged != 0;


    // Lancement de partie en fonction du choix
    if (choiceMenu == 1) {

        do {
            game = Game__create(1, gridSize, winCondition, firstPlayer, isLoggedB);
            gameResult = startGame(game);
            Game__destroy(game);

           if(gameResult == 1) {
                scorePlayer1++;
            } else if(gameResult == 2) {
                scorePlayer2++;
            } else {
                draw++;
            }

            printf("\nPlayer 1 score: %d\n", scorePlayer1);
            printf("Player 2 score: %d\n", scorePlayer2);
            printf("Egalites: %d\n", draw);


            printf("Voulez-vous rejouer ? (1 = yes, 0 = no)\n");
            scanf("%d", &choiceMenu);

        } while (choiceMenu == 1);
        
        return 0;

    } else if(choiceMenu == 2) {

        do {
            game = Game__create(2, gridSize, winCondition, firstPlayer, isLoggedB);
            gameResult = startGame(game);
            Game__destroy(game);

            if(gameResult == 1) {
                scorePlayer1++;
            } else if(gameResult == 2) {
                scorePlayer2++;
            } else {
                draw++;
            }

            printf("\nPlayer 1 score: %d\n", scorePlayer1);
            printf("Player 2 score: %d\n", scorePlayer2);
            printf("Egalites: %d\n", draw);


            printf("Voulez-vous rejouer ? (1 = yes, 0 = no)\n");
            scanf("%d", &choiceMenu);

        } while (choiceMenu == 1);
        
        return 0;

    } else if(choiceMenu == 3) {

        do {
            game = Game__create(3, gridSize, winCondition, firstPlayer, isLoggedB);
            gameResult = startGame(game);
            Game__destroy(game);

            if(gameResult == 1) {
                scorePlayer1++;
            } else if(gameResult == 2) {
                scorePlayer2++;
            } else {
                draw++;
            }

            printf("\nPlayer 1 score: %d\n", scorePlayer1);
            printf("Player 2 score: %d\n", scorePlayer2);
            printf("Egalites: %d\n", draw);

            printf("Voulez-vous rejouer ? (1 = yes, 0 = no)\n");
            scanf("%d", &choiceMenu);

        } while (choiceMenu == 1);
        
        return 0;
    } else {
        return 0;
    }
}