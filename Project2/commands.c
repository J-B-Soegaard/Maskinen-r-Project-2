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
//
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

    if(Q){				//Skal være if ("spilleren har skrevet Q så køre vi dette if statement")
      freeDeck(&C1);	//Frigør plads
      freeDeck(&C2);
      freeDeck(&C3);
      freeDeck(&C4);
      freeDeck(&C5);
      freeDeck(&C6);
      freeDeck(&C7);
      //freeDeck(&F1);
      //freeDeck(&F2);
      //freeDeck(&F3);
      //freeDeck(&F4);


      // Når vi kommer tilbage i main kan vi printe:
      // sprintf(&message,"Quit Game. Deck has been saved. Use LD saved_deck\n");
      // Noget i den stil yk
    }

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
}
   

