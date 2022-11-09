
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "game.c"

int result;

struct stat st = {0};

int main() {

    int j1=0;
    int j2=0;
    int draw=0;

    if (stat("games", &st) == -1) {
        mkdir("games", 0700);
    }

    for(int i = 0; i < 10000; i++) {

        Game* game = Game__create(4, 3, 3, 2, false);
        result = startGame(game);
        if(result == 1) {
            j1++;
        } else if(result == 2) {
            j2++;
        } else {
            draw++;
        }
        Game__destroy(game);
    }
    

    printf("Résultat des 10000 parties jouées en 3x3 (Joueur 1 démarrant)\n -> Joueur 1 : %d victoires \n -> Joueur 2 : %d victoires \n -> Egalités : %d", j1, j2, draw);

}