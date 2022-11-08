
#include <stdlib.h>
#include "game.c"


int result;

int main() {

    for(int i = 0; i < 50; i++) {

        Game* game = Game__create(4, 9, 4);
        result = startGame(game);
        printf("%d ", result);
        Game__destroy(game);
    
    }


}