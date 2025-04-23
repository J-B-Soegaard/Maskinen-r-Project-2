#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
    char rank; 
    char suit;  
} Card;

typedef struct Node {
    Card card;
    int visible;
    struct Node* next;   
} Node;
