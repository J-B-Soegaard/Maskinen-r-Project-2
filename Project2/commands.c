#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"


//-----


//------------------
node* deck = NULL; // decket kortene bliver lagt hægtet på.
void createCard(node** root, char value[3]);
int CHECK(char fileName[]);
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
int CHECK(char fileName[])
{
    int card_count = 0;
    char card[3];                       // til at læse kort (2 chars + '\0')
    char all_cards[52][4];              // Valid kort array + et slot for at tjekke for duplicate kort
    int i, j;

    // Åbner vores file unshuffled.txt med alle valid kort
    FILE *file_check = fopen("unshuffled.txt", "r");
    if (file_check == NULL) {
        return 4; // Error ved åbning af unshuffled file
    }

    while (fscanf(file_check, "%2s", card) == 1 && card_count < 52) {
        strcpy(all_cards[card_count], card);
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
                    fclose(fp);
                    return 1; // Duplicate kort fundet
                } else {
                    all_cards[i][3] = '1'; // Markere kortet som brugt
                    break;
                }
            }
        }

        if (!found) {
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
        return 7; // Ikke nok kort ( mindre ind 52 kort )
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
void move(node **from, char card[4], node **to) {
    node* list1 = *from;    //søjle det kommer fra
    node* list2 = *to;      // søjle den skal hen til.
    node* temp = list1;     //holder værdi den element før det element vi vil har fat i første list
    const char listOfValues[13] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    int i = 0;

    while (card[0] != listOfValues[i] && i != 12) {
        i++; //loop til at finde det korts værdi
    }

    while (list1 != NULL && (list1->card.value != card[0] || list1->card.suit != card[1])) {
        temp = list1;
        list1 = list1->next; //loop til at finde kortet i listen
    }
    if (list1 == NULL) {
        return; //hvis kortet ikke er der.
    }

    if (*to == NULL && list1->card.value == 'K' && list1->next == NULL) { // hvis det er er en konge
        *to = list1;    //konge kan kun rykke hen til en tom søjle
        if (temp == list1) {
            *from = NULL; //hvis rykker fra en tom søjle til en anden
        } else {
            temp->next = NULL; //hvis from søjle ikke er tom
        }
        return;
    }


    if (list2->card.value == '[' && list2->card.suit == ']' && list1->next == NULL) { //hvis det er en funndation
        while (list2->next != NULL) {
            list2 = list2->next;
        }
        if (list2->isHidden == 2 && list1->card.suit == 'C') { //hvis F1 bruger isHidden til at se forskel
            if (list1->card.value == 'A' || list2->card.value == listOfValues[i - 1]) {
                list2->next = list1;
                if (temp == list1) {
                    *from = NULL;
                } else {
                    temp->next = NULL;
                }
            }
        } else if (list2->isHidden == 3 && list1->card.suit == 'D') {// hvis F2
            if (list1->card.value == 'A' || list2->card.value == listOfValues[i - 1]) {
                list2->next = list1;
                if (temp == list1) {
                    *from = NULL;
                } else {
                    temp->next = NULL;
                }
            }
        } else if (list2->isHidden == 4 && list1->card.suit == 'H') { //hvis F3
            if (list1->card.value == 'A' || list2->card.value == listOfValues[i - 1]) {
                list2->next = list1;
                if (temp == list1) {
                    *from = NULL;
                } else {
                    temp->next = NULL;
                }
            }
        } else if (list2->isHidden == 5 && list1->card.suit == 'S') { //hvis F4
            if (list1->card.value == 'A' || list2->card.value == listOfValues[i - 1]) {
                list2->next = list1;
                if (temp == list1) {
                    *from = NULL;
                } else {
                    temp->next = NULL;
                }
            }
        }
    }

    while (list2->next != NULL) {
        list2 = list2->next; //kommer til sidste element i to listen
    }


    if (list1->card.suit != list2->card.suit && list2->card.value == listOfValues[i + 1]) { //checker om det er et lovligt move
        list2->next = list1;
        if (temp == list1) {
            temp = NULL;
        } else {
            temp->next = NULL;
        }
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
// playphase
void P(node** root) {
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
 char list[13]={'A','2','3','4','5','6','7','8','9','T','J','Q','K'}; //liste til at se hvad er størst.

 while(1){
   char input[100];
   char FromCo[10];  // Column vi rykker fra
   char ToCo[10];    // Column vi rykker hen til
   char card[4] = "";  // Hvis der er angivet kort er det kortet vi ville rykke

   if (checkWin(F1,F2,F3,F4)){
       printf("message: Congratulations, you won!\n");
       printf("message: Type \"N\" for a New Game \n >");
       printf("message: Type \"Q\" to Quit the Game \n >");
       printf("input >");
       break;
   // Vi breaker så ud af Void P tilbage i main hvor vi så laver et statement der venter på svar fra brugeren
   // der kan vi lave if statement der hvis vi for N går tilbage til startup phase ellers Q for at quit helt
   // Jeg synes det er bedst sådan for at give spilleren et præcis overblik over hvad der sker når man vinder  da dette
   // ikke er skrevet præcist i opgaven hvad der skal ske.
     }

   printf("Message: Indtast dit Move (eller Q for at Quit)");
   printf("Input >");
   fgets(input, 100, stdin);

   //Fjern newLine
   input[strcspn(input, "\n")] = 0;

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
      // Når vi kommer tilbage i main kan vi printe:
      // sprintf(&message,"Quit Game. Deck has been saved. Use LD saved_deck\n");
      // Noget i den stil yk
      break;
    }

    // Split op i 'fra' og 'til' ved at splitte ved "->"
    char* arrow = strstr(input, "->");
    if (arrow == NULL) {						// Hvis ingen arrow are det forkert format og vi køre ikke koden
      printf("Ugyldigt format! Brug '->'\n");
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
        printf("Ugyldig From: %s\n", FromCo);	// Hvis input ikke er en gyldig C eller F print
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
        printf("Ugyldig TO: %s\n", ToCo);	// Hvis input ikke er en gyldig C eller F print
      }

      move(from, card, to);			// Rykker de ønskede kort
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

