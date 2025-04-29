#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "structures.h"  

typedef struct GameState {
    CardNode *deck;           
    Column *columns[7];       
    Foundation *foundations[4];
    char lastCommand[128];
    char message[128];
    int phase;                // 0 to start 1 to play
} GameState;

#endif
