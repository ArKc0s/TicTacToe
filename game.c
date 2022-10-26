typedef struct Game
{
    int gameState;
    int playerTurn;
    int movesCount;
    int gameType;

} Game;

void Game__init(Game* self, int type) {

    self->gameState = -1;
    self->playerTurn = 0;
    self->movesCount = 0;
    self->gameType = type;

}

Game* Game__create(int type) {
    Game* game = (Game*) malloc(sizeof(Game));
    Game__init(game, type);
    return game;
}