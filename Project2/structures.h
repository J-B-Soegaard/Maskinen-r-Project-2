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

#endif