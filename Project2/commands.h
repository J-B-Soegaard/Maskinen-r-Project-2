//
// Created by Jacob Søgaard on 06/04/2025.
//
#ifndef COMMANDS_H
#define COMMANDS_H
#include "structures.h"
node* deck;
void LD(char filename[]);
void createCard(char value[3]);
void createBoard(void);
void SW();
void SR(node** root);

#endif //COMMANDS_H