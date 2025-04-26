#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
    char value;
    char suit;
} Card;

typedef struct Node {
    Card card;
    int isHidden;
    struct node* next;
} node;
