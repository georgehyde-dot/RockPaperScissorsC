#include "rps.h"
#include <ncurses.h>

void incrementScore(struct Game *g);

void getPlayerName(struct Game *g1);

// Game of rock, paper, scissors
// Play against the computer 
// Pick settings for number of rounds 
// and join the online leaderboard(?)

int main(int argc, char ** argv){
    // int y, x;

    // x = y = 15;

    // initscr();

    // mvprintw(y, x, "Rock, Paper, Scissors!\n");

    struct Game game = {"Player 1", 0, 0, 0, 0, 5, 0};

    getPlayerName(&game);

    fprintf(stdout, "Player 1: %s\nScore:%d\n", game.Player, game.PlayerScore);

    while (1) {
        gameLoop(&game);

        if (game.GameOver == 1){
            fprintf(stdout, "Player: %s\nFinal Score:%d\n", game.Player, game.PlayerScore);
            // endwin();
            break;
        }
        
    }
    return 0;
}