#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"


//-----


//------------------
node* deck = NULL; // decket kortene bliver lagt hægtet på.
void createCard(node** root, char value[3]);
int CHECK(char fileName[], char errorCard[3], int* errorIndex);
int checkWin(node* F1, node* F2, node* F3, node* F4);
void LD(char fileName[])
{

    char temp[4];
    FILE *fp;

fp = fopen(fileName, "r"); // åbner filen

    if (fp == NULL)
    {
        FILE *fp = fopen("unshuffled.txt", "r"); // hvis ikke den der er givet en rigtigt fil navn så tag den det deck der sorteret.
    }
    while (fgets(temp, 4, fp)!=NULL) {
        createCard(&deck, temp); // laver alle kortene og linker dem til deck

    }
    fclose(fp);


}
//------------------

void createCard(node** root, char value[4]) {
    node* new_node = malloc(sizeof(node));
    new_node->next = NULL;
    new_node->card.value = value[0];
    new_node->card.suit = value[1];
    new_node->isHidden = 0;

    // check om listen er tom.
    if (*root == NULL) {
        *root = new_node;
    } else {
        node* curr = *root;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
}

//----------------
//--
void createBoard(void) { // fungere kun til startup phase
    printf("\nc1\tc2\tc3\tc4\tc5\tc6\tc7\n\n");
    int counter = 0;
    int fCounter = 1;
    int numberF=0;
    if (deck == NULL) {
        printf("\t\t\t\t\t\t\t\t\t[]\tf1\n");
        printf("\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t\t\t[]\tf2\n");
        printf("\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t\t\t[]\tf3\n");
        printf("\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t\t\t[]\tf4\n");
        printf("\t\t\t\t\t\t\t\t\n");
    }
    for (node* curr = deck; curr != NULL; curr = curr->next) {
        if (curr->isHidden == 1) {
            printf("%c%c", curr->card.value,curr->card.suit);
        }else {
            printf("[]");
        }
        printf("\t");
        counter++;


        if (counter == 7) {
            if (fCounter == 1|| fCounter == 3|| fCounter == 5|| fCounter == 7)
            {
                numberF++;
                printf("\t\t[]\tf%d", numberF);

            }

            printf("\n");
            counter = 0;
            fCounter++;
        }

    }
printf("\n");
}
//--
void SW() { // viser alle kortene
    node* curr = deck;
    while ( curr != NULL) {
        curr->isHidden = 1;
        curr=curr->next;
    }
    createBoard();
}
//---------------
//--
void SI(node **root, int split) {
    node *deck = *root;       // brug *root som deck
    node *curr = deck;
    node *deck2 = NULL;
    int i = 0;
    if (split>52) {
        return;
    }
    while (i < split - 1) {

        curr = curr->next;
        i++;
    }

    deck2 = curr->next; // her splitter vi
    curr->next = NULL;

    node *newDeck = NULL;
    node **ptrDeck = &newDeck; //holder adressen til hvor næste kort skal ind

    while (deck != NULL || deck2 != NULL) {
        if (deck != NULL) { // tag et kort fra deck på putter det i nye deck
            *ptrDeck = deck;    //sætter nyt kort ind på newDeck
            deck = deck->next;
            ptrDeck = &(*ptrDeck)->next;
        }
        if (deck2 != NULL) {    // tag et kort fra deck2 på putter det i nye deck
            *ptrDeck = deck2;
            deck2 = deck2->next;
            ptrDeck = &((*ptrDeck)->next);
        }
    }
    *ptrDeck = NULL;

    *root = newDeck; //  new deck bliver til deck
}
//--
//---------------
void saveCard(node** root,char name[255]) {
    if (name == NULL) {
        name = "cards.txt";
    }
    FILE *fp = fopen(name, "w");
    node* curr = *root;
    while (curr != NULL ) {
        fprintf(fp, "%c%c\n", curr->card.value,curr->card.suit);
        curr = curr->next;
    }
    fclose(fp);
}
//---------------
int CHECK(char fileName[], char errorCard[3], int* errorIndex) {
    int card_count = 0;
    char card[3];                       // til at læse kort (2 chars + '\0')
    char all_cards[52][4];              // Valid kort array + et slot for at tjekke for duplicate kort
    int i;

    // Åbner vores file unshuffled.txt med alle valid kort
    FILE *file_check = fopen("unshuffled.txt", "r");
    if (file_check == NULL) {
        return 4; // Error ved åbning af unshuffled file
    }

    while (fscanf(file_check, "%2s", card) == 1 && card_count < 52) {
        strcpy(all_cards[card_count], card); // Tilføjer alle vores kort til all_cards array
        all_cards[card_count][3] = '0'; // Sætte alle kort til '0' som betyder ikke brugt
        card_count++;
    }
    fclose(file_check);

    if (card_count != 52) {
        return 5; // Unshuffled.txt har ikke 52 kort (Burde ikke ske i vores setup)
    }

    // Åben filen vi ville check
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        return 6; // Error ved åbning af file
    }

    int input_count = 0;

    while (fscanf(fp, "%2s", card) == 1) {
        int found = 0;
        for (i = 0; i < 52; i++) {
            if (strcmp(card, all_cards[i]) == 0) {
                found = 1;
                if (all_cards[i][3] == '1') {
                    strcpy(errorCard, card);
                    *errorIndex = input_count + 1;
                    fclose(fp);
                    return 1; // Duplicate kort fundet
                } else {
                    all_cards[i][3] = '1'; // Markere kortet som brugt
                    break;
                }
            }
        }

        if (!found) {
            strcpy(errorCard, card);
            *errorIndex = input_count + 1;
            fclose(fp);
            return 3; // Ikke rigtigt kort (Ikke Valid kort fundet)
        }

        input_count++;
        if (input_count > 52) {
            fclose(fp);
            return 2; // For mange kort (over 52 kort)
        }
    }

    fclose(fp);

    if (input_count < 52) {
        return 7; // Ikke nok kort (mindre ind 52 kort)
    }

    return 0; // Alt Ok (Valid deck)

    // Error code liste:
    // 0 = Ingen problemer
    // 1 = Duplicate kort
    // 2 = For mange kort
    // 3 = invalid kort (Kort eksistere ikke eller ikke rigtig format)
    // 4 = Kan ikke åbne unshuffled file
    // 5 = Unshuffeled har ikke nok kort (burde ikke ske)
    // 6 = filen vi checker for kan ikke åbnes
    // 7 = for lidt kort



}

void SR(node** root) {
  srand(time(NULL));		// Laver et random seed. Dette gør vi for ny random tal hver gang
  int x;					// Variable der skal holde vores random tal
  int Locations = 1;		// Variable	der skal angive hvor mange positioner kortet kan blive lagt ind på

  node* deck_temp=NULL;		// Vores midlertidig pointer der skal holde starten af vores deck

  while (*root != NULL) {	// Bliver ved ind til root deck er tomt
    x = (rand() % Locations) + 1;	//Tilfældig tal fra 1 til Locations

    // Find top kortet fra vores root deck
    node* currentCard = *root;
    node* prev = NULL;

    while (currentCard->next != NULL) {
      prev = currentCard;
      currentCard = currentCard->next;
    }

    if (prev != NULL) {
      prev->next = NULL;  // Fjern top kort
    } else {
      *root = NULL; // Vis der kun er et kort tilbage skal decket være tomt
    }

    currentCard->next = NULL;

	// Indsætter currentCard i deck_temp på vores random Location x
    if (deck_temp == NULL || x == 1) {
      currentCard->next = deck_temp;		// Hvis det nye deck er tomt, eller x == 1, indsættes currentCard forrest
      deck_temp = currentCard;
    } else {
      node* insertPrev = deck_temp;			// Gå frem til den positionen før x (det ønskede lokation)
      for (int i = 1; i < x - 1; i++) {
        insertPrev = insertPrev->next;
      }

      // Indsæt kortet på den ønskede position
      currentCard->next = insertPrev->next;
      insertPrev->next = currentCard;
    }

    Locations++;		// Muligheden af lokationer bliver nu større

  }

  //Husker at udskifte vores temporary pointer med root deckes orginale pointer
  *root = deck_temp;

}
//
void freeDeck(node **root) {
    node* current = *root; // til at holde værdien
    node* tmp; // til at frigøre

    while (current != NULL) {
        tmp = current;
        current = current->next;
        free(tmp);
    }

    *root = NULL;
}
//move funktion
void move(node **from, char card[4], node **to, char MoveMessage[100]) {
    node* list1 = *from;    //søjle det kommer fra
    node* list2 = *to;      // søjle den skal hen til.
    node* temp = list1;     //holder værdi den element før det element vi vil har fat i første list
    const char listOfValues[13] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    int i = 0;
    if (card[0]=='\0') { // hvis der bliver skrevet feks. C1->F1
        while (list1->next!= NULL) {
            list1 = list1->next; // finder sidste kort
        }
        card[0]=list1->card.value; //putter værdierne ind
        card[1]=list1->card.suit;
        list1 = *from; // sætter list tilbage til pointe på from.
    }

    while (card[0] != listOfValues[i] && i != 12) {
        i++; //loop til at finde det korts værdi
    }

    while (list1 != NULL && (list1->card.value != card[0] || list1->card.suit != card[1])) {
        temp = list1;
        list1 = list1->next; //loop til at finde kortet i listen
    }
    if (list1 == NULL) {
        sprintf(&MoveMessage[0], "Kortet var ikke i den colone");
        return; //hvis kortet ikke er der.
    }
    /*
    if (list1->isHidden==0) {
        // så kort ikke kan rykke hvis de er bagsiden op ad
    }
    */
    if (*to == NULL && list1->card.value == 'K' && list2 == NULL) { // hvis det er er en konge
        *to = list1;    //konge kan kun rykke hen til en tom søjle
        if (temp == list1) {
            *from = NULL; //hvis rykker fra en tom søjle til en anden
        } else {
            temp->next = NULL; //hvis from søjle ikke er tom
        }
        sprintf(&MoveMessage[0], "OK"); //rykker kongen til en tom kolon
        if (*from != NULL) {
            list1 = *from;
            while (list1->next != NULL) {
                list1 = list1->next;
            }
            if (list1->isHidden == 0) { // checker om det kommer et ikke vendt kort på toppen som skal vendes.
                list1->isHidden = 1;
            }
        }
        return;
    }


    if (list2->card.value == '[' && list2->card.suit == ']' && list1->next == NULL) { //hvis det er en funndation

        if (list2->isHidden == 2 && list1->card.suit == 'C') { //hvis F1 bruger isHidden til at se forskel
            while (list2->next != NULL) {
                list2 = list2->next;
            }
            if (list1->card.value == 'A' || list2->card.value == listOfValues[i - 1]) {
                list2->next = list1;
                if (temp == list1) {
                    *from = NULL;
                    sprintf(&MoveMessage[0], "OK"); // rykker til F1
                    if (*from != NULL) {
                        list1 = *from;
                        while (list1->next != NULL) {
                            list1 = list1->next;
                        }
                        if (list1->isHidden == 0) { // checker om det kommer et ikke vendt kort på toppen som skal vendes.
                            list1->isHidden = 1;
                        }
                    }
                    return;
                } else {
                    temp->next = NULL;
                    sprintf(&MoveMessage[0], "OK"); // rykker til F1
                    if (*from != NULL) {
                        list1 = *from;
                        while (list1->next != NULL) {
                            list1 = list1->next;
                        }
                        if (list1->isHidden == 0) { // checker om det kommer et ikke vendt kort på toppen som skal vendes.
                            list1->isHidden = 1;
                        }
                    }
                    return;
                }

            }
        } else if (list2->isHidden == 3 && list1->card.suit == 'D') {// hvis F2
            while (list2->next != NULL) {
                list2 = list2->next;
            }
            if (list1->card.value == 'A' || list2->card.value == listOfValues[i - 1]) {
                list2->next = list1;
                if (temp == list1) {
                    *from = NULL;
                    sprintf(&MoveMessage[0], "OK"); // rykker til F2
                    if (*from != NULL) {
                        list1 = *from;
                        while (list1->next != NULL) {
                            list1 = list1->next;
                        }
                        if (list1->isHidden == 0) { // checker om det kommer et ikke vendt kort på toppen som skal vendes.
                            list1->isHidden = 1;
                        }
                    }
                    return;
                } else {
                    temp->next = NULL;
                    sprintf(&MoveMessage[0], "OK"); // rykker til F2
                    if (*from != NULL) {
                        list1 = *from;
                        while (list1->next != NULL) {
                            list1 = list1->next;
                        }
                        if (list1->isHidden == 0) { // checker om det kommer et ikke vendt kort på toppen som skal vendes.
                            list1->isHidden = 1;
                        }
                    }
                    return;
                }
            }
        } else if (list2->isHidden == 4 && list1->card.suit == 'H') { //hvis F3
            while (list2->next != NULL) {
                list2 = list2->next;
            }
            if (list1->card.value == 'A' || list2->card.value == listOfValues[i - 1]) {
                list2->next = list1;
                if (temp == list1) {
                    *from = NULL;
                } else {
                    temp->next = NULL;
                }
                sprintf(&MoveMessage[0], "OK"); // rykker til F3
                if (*from != NULL) {
                    list1 = *from;
                    while (list1->next != NULL) {
                        list1 = list1->next;
                    }
                    if (list1->isHidden == 0) { // checker om det kommer et ikke vendt kort på toppen som skal vendes.
                        list1->isHidden = 1;
                    }
                }
                return;
            }
        } else if (list2->isHidden == 5 && list1->card.suit == 'S') { //hvis F4
            while (list2->next != NULL) {
                list2 = list2->next;
            }
            if (list1->card.value == 'A' || list2->card.value == listOfValues[i - 1]) {
                list2->next = list1;
                if (temp == list1) {
                    *from = NULL;
                } else {
                    temp->next = NULL;
                }
                sprintf(&MoveMessage[0], "OK"); // rykker til
                if (*from != NULL) {
                    list1 = *from;
                    while (list1->next != NULL) {
                        list1 = list1->next;
                    }
                    if (list1->isHidden == 0) { // checker om det kommer et ikke vendt kort på toppen som skal vendes.
                        list1->isHidden = 1;
                    }
                }
                return;
            }
        }else {
            sprintf(&MoveMessage[0], "fejl kort passer ikke i fonditon"); //  hvis list2 er en fond men kortet ikke passer.
            return;
        }
    }

    while (list2->next != NULL) {
        list2 = list2->next; //kommer til sidste element i to listen
    }


    if (list1->card.suit != list2->card.suit && list2->card.value == listOfValues[i + 1]) { //checker om det er et lovligt move
        if (list1->isHidden==0) { //hvis spiller prøver at rykke et kort der ikke er vendt om.
            sprintf(&MoveMessage[0], "fejl kortet passer ikke.(kort er ikke vendt om)");
            return;
        }
        list2->next = list1;
        if (temp == list1) {
            *from = NULL;
        } else {
            temp->next = NULL;
        }
        sprintf(&MoveMessage[0], "OK"); // rykker til til kolon
    } else {
        sprintf(&MoveMessage[0], "fejl kortet passer ikke."); // rykker til
        return;
    }

    if (*from != NULL) { 
        list1 = *from;
        while (list1->next != NULL) {
            list1 = list1->next;
        }
        if (list1->isHidden == 0) { // checker om det kommer et ikke vendt kort på toppen som skal vendes.
            list1->isHidden = 1;
        }
    }
}
// gameBoard
void gameboard(node* collum[7],node* fonditons[4]) {
    node* c1=collum[0];
    node* c2=collum[1];
    node* c3=collum[2];
    node* c4=collum[3];
    node* c5=collum[4];
    node* c6=collum[5];
    node* c7=collum[6];
    node* række[]={c1,c2,c3,c4,c5,c6,c7}; //søjler
    node* fond1=fonditons[0];
    node* fond2=fonditons[1];
    node* fond3=fonditons[2];
    node* fond4=fonditons[3];
    node* fondArr[4]={fond1,fond2,fond3,fond4}; // fondations
    int j=0;
    printf("\nc1\tc2\tc3\tc4\tc5\tc6\tc7\n\n");
    int counter = 1;
    while (række[0]!=NULL||række[1]!=NULL||række[2]!=NULL||række[3]!=NULL||række[4]!=NULL||række[5]!=NULL||række[6]!=NULL||counter<=7) {
        for (int i=0;i<7;i++) {
            if (række[i]!=NULL) {
                if (række[i]->isHidden==1) {
                    printf("%c%c\t",række[i]->card.value,række[i]->card.suit);
                }else {
                    printf("[]\t");
                }
                række[i]=række[i]->next;
            } else {
                printf("\t");
            }
        }
        if (counter==1||counter==3||counter==5||counter==7) {
            while (fondArr[j]->next!=NULL) {
                fondArr[j]=fondArr[j]->next;
            }
            printf("\t\t%c%c\tF%d",fondArr[j]->card.value,fondArr[j]->card.suit,j+1);
            j++;
        }
        counter++;
        printf("\n");
    }
}
// slut gameboard
// playphase
void P(node** root, char MainMessage[100], char MainLastCMD[100])
{
    node* C1= NULL; node* C2 = NULL; node* C3 = NULL; node* C4 = NULL; node* C5 = NULL; node* C6 = NULL; node* C7 = NULL; // all søjler
    node** c1ptr= &C1;
    node** c2ptr= &C2;
    node** c3ptr= &C3;
    node** c4ptr= &C4;
    node** c5ptr= &C5;
    node** c6ptr= &C6;
    node** c7ptr= &C7;
    int card_count = 0;
    node *curr = *root;
    node* prev = curr;

    //
    node* F1=NULL;
    node* F2=NULL;
    node* F3=NULL;
    node* F4=NULL;
    createCard(&F1,"[]");
    createCard(&F2,"[]");
    createCard(&F3,"[]");
    createCard(&F4,"[]");
    F1->isHidden = 2; // C
    F2->isHidden = 3; // D
    F3->isHidden = 4; // H
    F4->isHidden = 5; // S
    //
    while (curr != NULL) {
        if (card_count<1) {
            *c1ptr = curr; // giver kortet til c1
            curr->isHidden=1;
            curr=curr->next; // vider i listen
            prev->next=NULL; // klipper listen
            prev=curr;
            c1ptr = &((*c1ptr)->next);
        }
        if (card_count<6) {
            *c2ptr = curr;
            if (card_count<1) { // logik til at hvilket kort skal skjules
                curr->isHidden=0; // skjuler
            }else {
                curr->isHidden=1; // viser
            } //
            curr=curr->next;
            prev->next=NULL;
            prev=curr;
            c2ptr = &((*c2ptr)->next);

        }
        if (card_count<7) {
            *c3ptr = curr;
            if (card_count<2) { // logik til at hvilket kort skal skjules
                curr->isHidden=0; // skjuler
            }else {
                curr->isHidden=1; // viser
            } //
            curr=curr->next;
            prev->next=NULL;
            prev=curr;
            c3ptr = &((*c3ptr)->next);
        }
        if (card_count<8) {
            *c4ptr = curr;
            if (card_count<3) { // logik til at hvilket kort skal skjules
                curr->isHidden=0; // skjuler
            }else {
                curr->isHidden=1; // viser
            } //
            curr=curr->next;
            prev->next=NULL;
            prev=curr;
            c4ptr = &((*c4ptr)->next);
        }
        if (card_count<9) {
            *c5ptr = curr;
            if (card_count<4) { // logik til at hvilket kort skal skjules
                curr->isHidden=0; // skjuler
            }else {
                curr->isHidden=1; // viser
            } //
            curr=curr->next;
            prev->next=NULL;
            prev=curr;
            c5ptr = &((*c5ptr)->next);
        }
        if (card_count<10) {
            *c6ptr = curr;
            if (card_count<5) { // logik til at hvilket kort skal skjules
                curr->isHidden=0; // skjuler
            }else {
                curr->isHidden=1; // viser
            } //
            curr=curr->next;
            prev->next=NULL;
            prev=curr;
            c6ptr = &((*c6ptr)->next);
        }
        if (card_count<11) {
            *c7ptr = curr;
            if (card_count<6) { // logik til at hvilket kort skal skjules
                curr->isHidden=0; // skjuler
            }else {
                curr->isHidden=1; // viser
            } //
            curr=curr->next;
            prev->next=NULL;
            prev=curr;
            c7ptr = &((*c7ptr)->next);
        }
        card_count++;

    } // slut while loop
    //liste til at se hvad er størst.
    deck=NULL;
    char message[100];
    char last_cmd[100];
    char MoveMessage[100];

    sprintf(&message[0], "Game is ready, Good luck!\n");
    sprintf(&last_cmd[0], "P\n");



 while(1){
     node* Carr[7]={C1,C2,C3,C4,C5,C6,C7}; //gameboard
     node* Farr[4]={F1,F2,F3,F4}; // til gameboard
   char input[100];
   char FromCo[100];  // Column vi rykker fra
   char ToCo[100];    // Column vi rykker hen til
   char card[100] = "";  // Hvis der er angivet kort er det kortet vi ville rykke

     if (checkWin(F1,F2,F3,F4)){                // Check for win condition er opfyldt
         sprintf(&MainMessage[0], "You won, well played!");
         sprintf(&MainLastCMD[0], last_cmd);
         break;
     }

     gameboard(Carr,Farr);
     printf("last command:%s\n",&last_cmd[0]);      // Display gameboard og display last kommando og besked
     printf("message: %s\n", &message[0]);
     printf("input >");



   fgets(input, 100, stdin);            // Få brugens input

   //Fjern newLine
   input[strcspn(input, "\n")] = 0;
     sprintf(&last_cmd[0], input);


     // Dette er en command der bliver brugt til at tjekke om man faktisk kan vinde spillet
     if(strcmp(input, "EZWIN") == 0)
     {
         createCard(&Farr[0],"KC");         // Ved at force alle F til at holde en kong
         createCard(&Farr[1],"KH");
         createCard(&Farr[2],"KS");
         createCard(&Farr[3],"KD");

         if (checkWin(Farr[0],Farr[1],Farr[2],Farr[3])){
             sprintf(&MainMessage[0], "You won, well played!");
             sprintf(&MainLastCMD[0], last_cmd);
             break;
         }
     }

   //Tjek for Q (quit)
    if(strcmp(input, "Q") == 0 || strcmp(input, "q") == 0){		//hvis Quit så køre vi quit
      freeDeck(&C1);	//Frigør plads
      freeDeck(&C2);
      freeDeck(&C3);
      freeDeck(&C4);
      freeDeck(&C5);
      freeDeck(&C6);
      freeDeck(&C7);
      freeDeck(&F1);
      freeDeck(&F2);
      freeDeck(&F3);
      freeDeck(&F4);
        sprintf(&MainMessage[0], "Quit and saved current deck");
        sprintf(&MainLastCMD[0], last_cmd);
      return;
    }

    // Split op i 'fra' og 'til' ved at splitte ved "->"
    char* arrow = strstr(input, "->");
    if (arrow == NULL) {						// Hvis ingen arrow are det forkert format og vi køre ikke koden
      sprintf(&message[0],"Ugyldigt format! Brug '->'\n");
    } else {

      int FromLeng = arrow - input; 		// Længten bag ved -> aka From delen (Skal meget gerne være 5 eller 2)
      strncpy(FromCo, input, FromLeng);		// Kopierer de første FromLeng tegn fra input til FromCo.
      FromCo[FromLeng] = '\0';				// Afslutter med \0
      strcpy(ToCo, arrow + 2);				// Kopier det der er efter -> (skipper 2 tegn)

      char* colon = strchr(FromCo, ':'); // Tjek hvis der er ":" i input

      if (colon != NULL) {
        *colon = '\0';             // Split column og kort ad
        strcpy(card, colon + 1);   // Læser kort
      }

      // Find FROM pointer
      node** from = NULL;
      if (strcmp(FromCo, "C1") == 0) from = &C1;
      else if (strcmp(FromCo, "C2") == 0) from = &C2;
      else if (strcmp(FromCo, "C3") == 0) from = &C3;
      else if (strcmp(FromCo, "C4") == 0) from = &C4;
      else if (strcmp(FromCo, "C5") == 0) from = &C5;
      else if (strcmp(FromCo, "C6") == 0) from = &C6;
      else if (strcmp(FromCo, "C7") == 0) from = &C7;
      else if (strcmp(FromCo, "F1") == 0) from = &F1;
      else if (strcmp(FromCo, "F2") == 0) from = &F2;
      else if (strcmp(FromCo, "F3") == 0) from = &F3;
      else if (strcmp(FromCo, "F4") == 0) from = &F4;
      else {
        sprintf(&message[0], "Ugyldig From \"%s\"\n", FromCo);	// Hvis input ikke er en gyldig C eller F print
          continue;
      }


      // Find TO pointer
      node** to = NULL;
      if (strcmp(ToCo, "C1") == 0) to = &C1;
      else if (strcmp(ToCo, "C2") == 0) to = &C2;
      else if (strcmp(ToCo, "C3") == 0) to = &C3;
      else if (strcmp(ToCo, "C4") == 0) to = &C4;
      else if (strcmp(ToCo, "C5") == 0) to = &C5;
      else if (strcmp(ToCo, "C6") == 0) to = &C6;
      else if (strcmp(ToCo, "C7") == 0) to = &C7;
      else if (strcmp(ToCo, "F1") == 0) to = &F1;
      else if (strcmp(ToCo, "F2") == 0) to = &F2;
      else if (strcmp(ToCo, "F3") == 0) to = &F3;
      else if (strcmp(ToCo, "F4") == 0) to = &F4;
      else {
        sprintf(&message[0],"Ugyldig TO: \"%s\"\n", ToCo);	// Hvis input ikke er en gyldig C eller F print
          continue;
      }

        if (to != NULL && from != NULL)
        {
            move(from, card, to, MoveMessage);			// Rykker de ønskede kort
            sprintf(&message[0], MoveMessage);
            continue;
        }
    } //If-else statement slut
 } //While loop slut

}

int LastIsK(node* root) {
    if (root == NULL) return 0; // Hvis bunken er tom behøver vi ikke tjekke og retunere 0 (false)

    while (root->next != NULL) {	// Find det sidste kort
        root = root->next;
    }

    return (root->card.value == 'K');	// Hvis det sidste kort er en konge retunere vi 1 (true)
}

int checkWin(node* F1, node* F2, node* F3, node* F4) {
    return LastIsK(F1) && LastIsK(F2) && LastIsK(F3) && LastIsK(F4); // Retunere 1 hvis alle F's sidste kort er K ellers 0
}

