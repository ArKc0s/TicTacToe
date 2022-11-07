
#include <stdlib.h>
#include "game.c"

int result;

int main() {

    /*MagicSquare* ms = MagicSquare__create(5);
    printms(ms);*/

    for(int i = 0; i < 1; i++) {

        Game* game = Game__create(3, 5);
        result = startGame(game);
        printf("%d ", result);
        Game__destroy(game);
    
    }

    /*Game* game = Game__create(3,3);
    startGame(game);*/

    
   


}