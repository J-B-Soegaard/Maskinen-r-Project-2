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
void saveCard(node** root,char name[255]);
#endif //COMMANDS_H