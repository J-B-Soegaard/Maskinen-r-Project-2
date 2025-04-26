#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

#define node deck;


int main(void) {
    char message[100] = "message:\n";

    char str[255];
    char str2[4];
    char str3[100];

    printf("c1\tc2\tc3\tc4\tc5\tc6\tc7\n\n");
    printf("\t\t\t\t\t\t\t\t[]\tf1\n");
    printf("\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t\t[]\tf2\n");
    printf("\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t\t[]\tf3\n");
    printf("\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t\t[]\tf4\n");
    printf("\t\t\t\t\t\t\t\t\n");
    printf("last command:%s\n",str2);
    printf("%s", &message[0]);
    printf("input >");

    while (1) {
        fgets(str, 255, stdin);
        int numOfCmd = sscanf(str, "%s\n%s\n ", str2, str3);

        //--
        if (str2[0]=='L' && str2[1]=='D') { // command til at load
            if (numOfCmd == 2) {
                LD(str3);
                createBoard();
                printf("last command:%s\n",str2);
                printf("%s", &message[0]);
                printf("input >");
            } else {
                LD("unshuffled.txt");
                createBoard();
                printf("last command:%s\n",str2);
                printf("%s", &message[0]);
                printf("input >");
            }
        }
        //--
        else if (str2[0]=='S'&&str2[1]=='W') {     // command til vise all kort
            SW();
            printf("last command:%s\n",str2);
            printf("%s", &message[0]);
            printf("input >");
        }
        //--
        else if (str2[0]=='S'&&str2[1]=='R') {   // command til at shuffle deck
            SR(&deck);
            createBoard();
            printf("last command:%s\n",str2);
            printf("%s", &message[0]);
            printf("input >");
        }
        //--
        else if (str2[0]=='Q'&&str2[1]=='Q') { // command til at lukke program
            printf("Quit the program");
            exit(0);
        }
        //--
        else {   //hvis ikke nogen af de rigtige commands er brugt
            createBoard();
            sprintf(&message,"command not found\n");
            printf("last command:%s\n",str2);
            printf("message: %s", &message[0]);
            printf("input >");
        }
    }
}
