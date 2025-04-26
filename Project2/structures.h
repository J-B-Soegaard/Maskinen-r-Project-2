#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct Card{
    char value;
    char suit;
} Card_t;

typedef struct Node {
    Card_t card;
    int isHidden;
    struct node* next;
} node;

#endif