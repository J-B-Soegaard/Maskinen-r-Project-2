#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include <string.h>


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

        scanf("%2s", command);
        if ((command[0]=='l'&&command[1]=='d')||(command[0]=='L'&&command[1]=='D')) {
    strcpy(lastCmd, "ld"); //
            char filename[50];
            scanf("%s", filename);
            // ld(filename)

        }
//--
        if (command[0]=='Q'&&command[1]=='Q') { // command til at lukke program
            exit(0);
        }
//--
        }
    }



