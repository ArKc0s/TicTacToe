/*
*
* Header général de l'application
* Auteurs : WADIN Léo, JOSEPH Robin
*
*/

/*
* Appel de toutes les librairies nécessaires au fonctionnement du programme
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>

/*
* Définition des constantes
*/
#define MAX_GRID_SIZE 81

/*
* Définition des structures de données
*/

/*!
* @typedef playingGrid_t
*          Grille de jeu
* @field   grid         Grille de jeu
*/
typedef struct playingGrid_t
{
    char grid[MAX_GRID_SIZE][2];

} playingGrid_t;

/*!
* @typedef game_t
*          Instance de jeu
* @field   gameState    Etat du jeu (-1: En cours | 0: Egalite | 1: Victoire J1 | 2: Victoire J2)
* @field   playerTurn   Joueur qui doit jouer
* @field   movesCount   Nombre de coups joués
* @field   gameType     Type de jeu (1: 1vs1 | 2: 1vsComputer | 3: ComputervsComputer)
* @field   size         Taille de la grille (3,5,7 ou 9)
* @field   winCondition Nombre de symboles à aligner pour gagner
* @field   pg           Grille de jeu
* @field   gameFile     Fichier de stockage de l'historique
* @field   isLogged     Partie sauvegardée ou non
*/
typedef struct game_t {
    int gameState;
    int playerTurn;
    int movesCount;
    int gameType;
    int size;
    int winCondition;
    playingGrid_t* pg;
    FILE* gameFile;
    bool isLogged;

} game_t;

/*!
* @struct data_s
*         Données passées au thread de jeu de l'ordinateur
* @field  size     Taille de la grille
* @field  mark     Symbole du joueur qui doit jouer
* @field  gameFile Fichier de stockage de l'historique
* @field  isLogged Partie sauvegardée ou non
*/
struct data_s {
    playingGrid_t* pg;
    int size;
    char mark;
    FILE* gameFile;
    bool isLogged;
};

/*
* Définition des fonctions du programme
*/

/*!
* @function current_timestamp
*           Permet de trouver un temps unique pour la seed de génération de nombres aléatoires
* @details Addition du temps en secondes et en microsecondes
* @result Nombre différent à chaque appel
*/
long long current_timestamp();


/*!
* @function Game__init
*           Initialisation des propriétés d'une partie
* @param self instance de jeu
* @param type type de partie
* @param size taille de la grille
* @param winCondition condition de victoire
* @param firstPlayer premier joueur à jouer
* @param isLogged la partie est elle enregistrée
*/
void Game__init(game_t*, int, int, int, int, bool);

/*!
* @function Game__create
*           Attribution de l'espace mémoire pour une partie
* @param type type de partie
* @param size taille de la grille
* @param winCondition condition de victoire
* @param firstPlayer premier joueur à jouer
* @param isLogged la partie est elle enregistrée
* @result Instance de partie
*/
game_t* Game__create(int, int, int, int, bool);

/*!
* @function Game__reset
*           Réinitialisation de toutes les propriétés d'une partie
* @param self instance de jeu
*/
void Game__reset(game_t*);

/*!
* @function Game__destroy
*           Destruction d'une partie, libération de l'espace mémoire
* @param self instance de jeu
*/
void Game__destroy(game_t*);

/*!
* @function play
*           Placement d'un symbole sur la grille de jeu
* @param self instance de jeu
* @param mark symbole à placer
* @param position position sur laquelle placer le symbole
* @param gameFile fichier de stockage de l'historique
* @param isLogged la partie est elle enregistrée
*/
void play(game_t*, char, int, FILE*, bool);

/*!
* @function randomPlay
*           Placement d'un symbole sur la grille de jeu avec postition aléatoire
* @param self instance de jeu
* @param mark symbole à placer
* @param position position sur laquelle placer le symbole
* @param gameFile fichier de stockage de l'historique
* @param isLogged la partie est elle enregistrée
*/
void randomPlay(playingGrid_t*, int, char, FILE*, bool);

/*!
* @function critique
*           Fonction du thread de l'ordinateur
* @param data données passées au thread de jeu de l'ordinateur
*/
void* critique(void*);

/*!
* @function processState
*           Actualisation de l'état de jeu d'une partie
* @param self instance de jeu
*/
void processState(game_t*);

/*!
* @function printGameResult
*           Affichage du résultat de la partie
* @param self instance de jeu
*/
void printGameResult(game_t*);

/*!
* @function logGameResult
*           Enregistrement du résultat de la partie dans le fichier de sauvegarde
* @param self instance de jeu
*/
void logGameResult(game_t*);

/*!
* @function oneVersusOneGame
*           Déroulement d'une partie 1vs1
* @param self instance de jeu
* @returns résultat de la partie
*/
int oneVersusOneGame(game_t*);

/*!
* @function oneVersusComputerGame
*           Déroulement d'une partie 1vsC
* @param self instance de jeu
* @returns résultat de la partie
*/
int oneVersusComputerGame(game_t*);

/*!
* @function computerVersusComputerGame
*           Déroulement d'une partie CvsC
* @param self instance de jeu
* @returns résultat de la partie
*/
int computerVersusComputerGame(game_t*, bool);

/*!
* @function startGame
*           Déclenchement du démarrage de la partie
* @param self instance de jeu
* @returns résultat de la partie
*/
int startGame(game_t*);


/*!
* @function PlayingGrid__init
*           Initialisation des propriétés d'une grille de jeu
* @param self instance de la grille
* @param size taille de la grille
*/
void PlayingGrid__init(playingGrid_t*, int);

/*!
* @function PlayingGrid__init
*           Attribution de l'espace mémoire pour une grille de jeu
* @param size taille de la grille
* @returns instance de la grille
*/
playingGrid_t* PlayingGrid__create(int);

/*!
* @function PlayingGrid__reset
*           Réinitialisation de toutes les propriétés d'une grille
* @param self instance de la grille
*/
void PlayingGrid__reset(playingGrid_t*);

/*!
* @function PlayingGrid__destroy
*           Destruction d'une grille, libération de l'espace mémoire
* @param self instance de la grille
*/
void PlayingGrid__destroy(playingGrid_t*);

/*!
* @function displayGrid
*           Affichage dynamique de la grille de jeu
* @param self instance de la grille
* @param size taille de la grille
*/
void displayGrid(playingGrid_t*, int);

/*!
* @function countNumInRow
*           Comptage de la plus grande série de symboles alignés sur une section
* @param self instance de la grille
* @param size taille de la grille
* @param winCondition condition de victoire
* @param index position à vérifier
*/
int countNumInRow(playingGrid_t*, int, int, int);

/*!
* @function detectWin
*           Parcours du tableau dans tous les sens pour détecter une victoire éventelle
* @param self instance de la grille
* @param size taille de la grille
* @param winCondition condition de victoire
*/
int detectWin(playingGrid_t*, int, int);

/*!
* @function isPlayable
*           Détéction de jouabilité d'une case
* @param cell cellule à vérifier
* @param grid grille de jeu
* @param size taille de la grille
*/
bool isPlayable(int, char[][2], int);