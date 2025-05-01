#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct card{
    char value;
    char suit;
} Card_t;

typedef struct node {
    Card_t card;
    int isHidden;
    struct node* next;
} node;

typedef struct {
    node* columns[7];
    node* foundations[4];
    char last_cmd[256];
    char message[256];
    int in_play_phase;
} GameState;

#endif
