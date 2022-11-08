
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "game.c"

int result;
struct stat st = {0};

int main() {

    if (stat("games", &st) == -1) {
        mkdir("games");
    }

    for(int i = 0; i < 1; i++) {

        Game* game = Game__create(3, 3, 3, 2, true);
        result = startGame(game);
        printf("%d ", result);
        Game__destroy(game);
    
    }


}