//
// Created by Jacob Søgaard on 06/04/2025.
//
#ifndef COMMANDS_H
#define COMMANDS_H
void LD(char filename[]);
void createCard(char value[3]);
void createBoard(void);
void SW();
void SR();
typedef struct node {  // struct til at lave linked list med kortene
    char value[3];
    struct node *next; // bevæger kun 1 pointer til at pege frem ikke nogen til at pege tilbage
    int isHidden;
}node;

extern node deck;
#endif //COMMANDS_H
