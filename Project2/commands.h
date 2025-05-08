//
// Created by Jacob Søgaard on 06/04/2025.
//
#ifndef COMMANDS_H
#define COMMANDS_H
#include "structures.h"
extern node* deck;
void LD(char filename[]);
void createCard(node** root, char value[4]);
void createBoard(void);
void SW();
void SR(node** root);
void saveCard(node** root,char name[255]);
int CHECK(char fileName[], char errorCard[3], int* errorIndex);
void SI(node **root, int split);
int LastIsK(node* root);
int checkWin(node* F1, node* F2, node* F3, node* F4);
void P(node** root, char MainMessage[100], char MainLastCMD[100]);
void freeDeck(node **root);
void move(node **from, char card[4], node **to, char MoveMessage[100]);
#endif //COMMANDS_H