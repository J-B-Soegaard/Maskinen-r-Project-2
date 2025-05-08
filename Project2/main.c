#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include <time.h>
#include "structures.h"
#include "GUI.h"




int main(void) {
    char message[100] = "\n";

    char str[255];
    char str2[4];
    char str3[100];

   createBoard();
    printf("last command:%s\n",str2);
    printf("message: %s", &message[0]);
    printf("input >");

    while (1) {
        fgets(str, 255, stdin);
        int numOfCmd = sscanf(str, "%s\n%s\n ", str2, str3);
        char errorCard[3];
        int errorPos;

        //--
        if (strcmp(str2, "LD") == 0) { // command til at load
            if (deck!=NULL) { //hvis der allerede er et deck loaded ind.
                free(deck);
                deck=NULL;
            }
            if (numOfCmd == 2 && CHECK(str3, errorCard, &errorPos) == 0) {
                sprintf(&message,"File found!\n");
                LD(str3);
                createBoard();
                printf("last command:%s %s\n",str2,str3);
                printf("message: %s", &message[0]);
                printf("input >");
            } else {
                if (numOfCmd==1)
                {
                    sprintf(&message,"Loaded Standard deck\n");
                } else if (CHECK(str3, errorCard, &errorPos) == 1) {
                sprintf(&message,"ERROR: File contains duplicate cards at %d: %s, loading unshuffled\n", errorPos, errorCard); //File har duplicated cards
                } else if (CHECK(str3, errorCard, &errorPos) == 2) {
                    sprintf(&message,"ERROR: File contains more then 52 cards, loading unshuffled\n"); //Mere end 52 kort
                } else if (CHECK(str3, errorCard, &errorPos) == 3) {
                    sprintf(&message,"ERROR: File contains invalid cards at %d: %s, loading unshuffled\n", errorPos, errorCard); //fil har kort der ikke har rigtig format
                } else if (CHECK(str3, errorCard, &errorPos) == 4) {
                    sprintf(&message,"ERROR: Unable to open check deck\n");//Kan ikke åbne unshuffeld (burde ikke ske)
                    printf("last command:%s\n",str2);
                    printf("message: %s", &message[0]);
                    printf("input >");
                    exit(0);
                } else if (CHECK(str3, errorCard, &errorPos) == 5) {
                    sprintf(&message,"ERROR: Check deck doesn't have enough cards\n"); //Burde ikke ske
                    printf("last command:%s\n",str2);
                    printf("message: %s", &message[0]);
                    printf("input >");
                    exit(0);
                } else if (CHECK(str3, errorCard, &errorPos) == 6) {
                    sprintf(&message,"ERROR: Unable to open the file, loading unshuffled\n");   //Kan ikke åbne givet fil
                } else if (CHECK(str3, errorCard, &errorPos) == 7) {
                    sprintf(&message,"ERROR: File contains less then 52 cards, loading unshuffled\n"); // mindre end 52 kort
                }
                LD("unshuffled.txt");
                createBoard();
                printf("last command:%s\n",str2);
                printf("message: %s", &message[0]);
                printf("input >");
            }
        }
        //--
        else if (strcmp(str2, "SW") == 0) {     // command til vise all kort
            SW();

            if (deck==NULL) {
                sprintf(&message,"Fail, no deck loaded\n");
            }else {
                sprintf(&message,"cards are flipped\n");
            }
            printf("last command:%s\n",str2);
                printf("message: %s", &message[0]);
            printf("input >");
        }
        //--
        else if (strcmp(str2, "SR") == 0) {   // command til at shuffle deck
            if (deck==NULL) {
                sprintf(&message,"no deck loaded\n");
                createBoard();
                printf("last command:%s\n",str2);
                printf("message: %s", &message[0]);
                printf("input >");
            }else {
                sprintf(&message,"deck shuffled\n");
                SR(&deck);
                createBoard();
                printf("last command:%s\n",str2);
                printf("message: %s", &message[0]);
                printf("input >");
            }
        }
        //--
        else if (strcmp(str2, "QQ") == 0) { // command til at lukke program
            printf("Quit the program");
            exit(0);
        }
        else if (strcmp(str2, "SD") == 0) {// command til at gemme deck}
            if (numOfCmd == 2) {
                if (deck==NULL) {
                    printf("last command:%s %s\n",str2,str3);
                    sprintf(&message,"Fail no deck loaded\n");
                }else {
                    printf("last command:%s %s\n",str2,str3);
                    sprintf(&message,"file created!\n");
                    saveCard(&deck,str3);
                }

            }else {
                if (deck==NULL) {
                    printf("last command:%s %s\n",str2,str3);
                    sprintf(&message,"Fail no deck loaded\n");
                }else {
                    sprintf(&message,"No file name given, cards.txt file created\n");
                    saveCard(&deck,"cards.txt");
                }

            }
            createBoard();
            printf("last command:%s\n",str2);
            printf("message: %s", &message[0]);
            printf("input >");
        } else if (strcmp(str2, "SI") == 0) {// splitte og samle igen
            if (numOfCmd == 2) {
                if (deck==NULL) {
                    sprintf(&message,"Fail no deck loaded\n");
                    createBoard();
                    printf("last command:%s %s\n",str2,str3);
                    printf("message: %s", &message[0]);
                    printf("input >");
                }else if (atoi(str3)>52) {
                    sprintf(&message,"number too high\n");
                    createBoard();
                    printf("last command:%s %s\n",str2,str3);
                    printf("message: %s", &message[0]);
                    printf("input >");
                }else {
                    SI(&deck,atoi(str3));
                    sprintf(&message,"deck split\n");
                    createBoard();
                    printf("last command:%s %s\n",str2,str3);
                    printf("message: %s", &message[0]);
                    printf("input >");
                }

            }else {
                if (deck==NULL) {
                    sprintf(&message,"Fail no deck loaded\n");
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
        } else if (strcmp(str2, "P") == 0) {
            if (deck==NULL) {           // Hvis intet deck er loaded kan man ikke spille
                sprintf(&message,"Fail no deck loaded\n");
                createBoard();
                printf("last command:%s\n",str2);
                printf("message: %s", &message[0]);
                printf("input >");
            }else {                                     // Spil med det givet deck
                saveCard(&deck,"currentdeck.txt");
                char WinMessage[100];           // Strings der bliver brugt til at kunne give den rigtige besked fra P
                char MainLastCMD[100];          // Som er afhænigt om man vandt eller quittede
                P(&deck, WinMessage, MainLastCMD);  // Enter game phase
                LD("currentdeck.txt");
                createBoard();
                printf("last command: %s\n", &MainLastCMD[0]);
                printf("message: %s\n", &WinMessage[0]);
                printf("input >");
            }
        } else if (strcmp(str2, "G") == 0) {            // Ved brug af "G" kommando kan vi gå ind i den del der bruger GUI
            saveCard(&deck,"currentdeck.txt");
            char WinMessage[100];
            char MainLastCMD[100];
            Pgui(&deck);
            LD("currentdeck.txt");
            createBoard();
            printf("last command: %s\n", &MainLastCMD[0]);
            printf("message: %s\n", &WinMessage[0]);
            printf("input >");
        }
        else {   //hvis ikke nogen af de rigtige commands er brugt
            createBoard();
            sprintf(&message,"command not found\n");
            printf("last command:%s\n",str2);
            printf("message: %s", &message[0]);
            printf("input >");
        }
    }
}
