#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

#define node deck;


int main(void) {
    char message[] = "message:\n";
    char lastCmd[3];

    printf("c1\tc2\tc3\tc4\tc5\tc6\tc7\n\n");
    printf("\t\t\t\t\t\t\t\t[]\tf1\n");
    printf("\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t\t[]\tf2\n");
    printf("\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t\t[]\tf3\n");
    printf("\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t\t[]\tf4\n");
    printf("\t\t\t\t\t\t\t\t\n");
    printf("last command:%s\n",lastCmd);
    printf("%s", &message[0]);
    printf("input >");

    while (1) { //while loop til startphase
//---
        char command[3];

        scanf("%4s", command);
        if ((command[0]=='l'&&command[1]=='d')||(command[0]=='L'&&command[1]=='D')) {
    strcpy(lastCmd, "ld"); //
            //char filename[50];
            //scanf("%s", filename);
LD("/Users/jacobsoegaard/CLionProjects/Test/test.txt");
            createBoard();
            // ld(filename)

        }
//--
        if (command[0]=='S'&&command[1]=='W') {     // command til vise all kort
        SW();
        }

//--
        if (command[0]=='Q'&&command[1]=='Q') { // command til at lukke program
            printf("Quit the program");
            exit(0);
        }
//--
        }
    }



