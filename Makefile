VERSION = 2_0_1

build: src/app.c src/game.c src/playingGrid.c src/utils.h
	gcc src/app.c src/game.c src/playingGrid.c src/utils.h -Wall -lpthread -o TicTacToe_v_$(VERSION).exe