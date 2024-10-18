#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

struct Game {
    char Player[10];
    int PlayerScore;
    int ComputerScore;
    int PlayerChoice;
    int ComputerChoice;
    int Rounds;
    int GameOver;
};

enum objectOption {
    ROCK,
    PAPER,
    SCISSORS
};

void getPlayerName(struct Game *g1){
    char buffer[10];
    fprintf(stdout, "Enter %s Name: ", g1->Player);
    if (!(fgets(buffer, sizeof(buffer), stdin) != NULL)) {
       fprintf(stderr, "Error reading Name.\n");
       fprintf(stderr, "Name set to %s\n", g1->Player);
    }
    //remove newline from fgets input
    buffer[strcspn(buffer, "\r\n")] = 0;
    strcpy(g1->Player, buffer);
}

enum objectOption getPlayerSelection(){
    char buffer[100];
    int i, pos;
    pos = 0;

    fprintf(stdout, "Type the number of your choice and press enter:\n");
    fprintf(stdout, "0 - ROCK\n1 - PAPER\n2 - SCISSORS\n");
    if (!(fgets(buffer, sizeof(buffer), stdin) != NULL)) {
       fprintf(stderr, "Error reading input.\n");
    }

    i = (int)buffer[pos];

    if (i < 48 || i > 50) {
        fprintf(stderr, "Input must be a digit (0, 1, or 2)\n");
        return getPlayerSelection(); 
    }
    // increment pos to skip the LF char
    pos += 2;
    switch (i) {
        case 48: return ROCK;
        case 49: return PAPER;
        case 50: return SCISSORS;
    }
    return ROCK;
}

enum objectOption getComputerSelection(){
    int i;
    srand(time(NULL));
    i = rand()%3;
    
    switch (i) {
        case 0: return ROCK;
        case 1: return PAPER;
        case 2: return SCISSORS;
    }
    return ROCK;
}
void scoreRound(struct Game* game){
    void *p = malloc(sizeof(p) * 10);
    void *c = malloc(sizeof(c) * 10);
    char *p_choice = (char *)p;
    char *c_choice = (char *)c;
    

    switch(game->PlayerChoice) {
        case 0: memcpy(p_choice, "ROCK", 10); break;
        case 1: memcpy(p_choice, "PAPER", 10); break; 
        case 2: memcpy(p_choice, "SCISSORS", 10); break;
    }
    switch(game->ComputerChoice) {
        case 0: memcpy(c_choice, "ROCK", 10); break;
        case 1: memcpy(c_choice, "PAPER", 10); break;
        case 2: memcpy(c_choice, "SCISSORS", 10); break;
    }

    

    if (game->ComputerChoice == game->PlayerChoice){
        fprintf(stdout, "You both picked %s\n\n", c_choice);
        free(c_choice);
        free(p_choice);
        return;
    }
    fprintf(stdout, "You chose: %s\nComputer chose: %s\n\n", p_choice, c_choice);
    if (game->PlayerChoice - game->ComputerChoice == -1 || game->PlayerChoice - game->ComputerChoice == 2){
        fprintf(stdout, "You lost\n");
        game->ComputerScore++;
        free(c_choice);
        free(p_choice);
        return;
    } else {
        fprintf(stdout, "You won!\n");
        game->PlayerScore++;
        free(c_choice);
        free(p_choice);
        return;
    }

}

void gameLoop(struct Game* game){
    for (int i = 0;i < game->Rounds;i++){
        game->PlayerChoice = getPlayerSelection();
        game->ComputerChoice = getComputerSelection();
        scoreRound(game);
    }
    game->GameOver = 1;
}