#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include <time.h>


#define node deck;


int main(void) {
    char message[100] = "\n";

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
    printf("message: %s", &message[0]);
    printf("input >");

    while (1) {
        fgets(str, 255, stdin);
        int numOfCmd = sscanf(str, "%s\n%s\n ", str2, str3);

        //--
        if (str2[0]=='L' && str2[1]=='D') { // command til at load
            if (numOfCmd == 2 && CHECK(str3) == 0) {
                sprintf(&message,"File found!\n");
                LD(str3);
                createBoard();
                printf("last command:%s\n",str2);
                printf("message: %s", &message[0]);
                printf("input >");
            } else {
                if (CHECK(str3) == 1) {
                sprintf(&message,"ERROR: File contains duplicate cards\n"); //File har duplicated cards
                } else if (CHECK(str3) == 2) {
                    sprintf(&message,"ERROR: File contains more then 52 cards\n"); //Mere end 52 kort
                } else if (CHECK(str3) == 3) {
                    sprintf(&message,"ERROR: File contains invalid cards\n"); //fil har kort der ikke har rigtig format
                } else if (CHECK(str3) == 4) {
                    sprintf(&message,"ERROR: Unable to open check deck\n");//Kan ikke åbne unshuffeld (burde ikke ske)
                    printf("last command:%s\n",str2);
                    printf("message: %s", &message[0]);
                    printf("input >");
                    exit(0);
                } else if (CHECK(str3) == 5) {
                    sprintf(&message,"ERROR: Check deck doesn't have enough cards\n"); //Burde ikke ske
                    printf("last command:%s\n",str2);
                    printf("message: %s", &message[0]);
                    printf("input >");
                    exit(0);
                } else if (CHECK(str3) == 6) {
                    sprintf(&message,"ERROR: Unable to open the file\n");   //Kan ikke åbne givet fil
                } else if (CHECK(str3) == 7) {
                    sprintf(&message,"ERROR: File contains less then 52 cards\n"); // mindre end 52 kort
                }
                LD("unshuffled.txt");
                createBoard();
                printf("last command:%s\n",str2);
                printf("message: %s", &message[0]);
                printf("input >");
            }
        }
        //--
        else if (str2[0]=='S'&&str2[1]=='W') {     // command til vise all kort
            SW();
            sprintf(&message,"cards are flipped\n");
            printf("last command:%s\n",str2);
                printf("message: %s", &message[0]);
            printf("input >");
        }
        //--
        else if (str2[0]=='S'&&str2[1]=='R') {   // command til at shuffle deck
            sprintf(&message,"deck shuffled\n");
            SR(&deck);
            createBoard();
            printf("last command:%s\n",str2);
                printf("message: %s", &message[0]);
            printf("input >");
        }
        //--
        else if (str2[0]=='Q'&&str2[1]=='Q') { // command til at lukke program
            printf("Quit the program");
            exit(0);
        }
        else if (str2[0]=='S'&&str2[1]=='D') {// command til at gemme deck}
            if (numOfCmd == 2) {
                sprintf(&message,"file created!\n");
                saveCard(&deck,str3);
            }else {
                sprintf(&message,"No file name given, cards.txt file created\n");
                saveCard(&deck,"cards.txt");
            }
            createBoard();
            printf("last command:%s\n",str2);
            printf("message: %s", &message[0]);
            printf("input >");
        } else if (str2[0]=='S'&&str2[1]=='I') {// splitte og samle igen
            if (numOfCmd == 2) {
                SI(&deck,atoi(str3));
                sprintf(&message,"deck split\n");
                createBoard();
                printf("last command:%s\n",str2);
                printf("message: %s", &message[0]);
                printf("input >");
            }else {
                srand(time(NULL));
                SI(&deck,rand()%51+1);
                sprintf(&message,"no number given random number chosen\n");
                createBoard();
                printf("last command:%s\n",str2);
                printf("message: %s", &message[0]);
                printf("input >");
            }
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
