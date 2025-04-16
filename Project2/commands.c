#include <stdio.h>
#include <string.h>
#include "stdlib.h"
//-----
typedef struct node {  // struct til at lave linked list med kortene
    char value[3];
    struct node *next; // bevæger kun 1 pointer til at pege frem ikke nogen til at pege tilbage
}node;
node deck;
//------------------
void createCard(node** root, char value[3]);
void LD(char fileName[])
{
    char temp[3];
    FILE *fp;

    fp = fopen(fileName, "r");

    if (fp == NULL)
    {
        printf("File not found\n");
        FILE *fp = fopen("unshuffled.txt", "r"); // hvis ikke den der er givet en rigtigt fil navn så tag den det deck der sorteret.
    }
    while (fgets(temp, 3, fp)!=NULL) {
        createCard(&deck, temp);

    }
    fclose(fp);

}
//------------------

void createCard(node** root, char value[3]) { // tænker vi kan har 7 "roots" for hver søjle så vi kan genbruge koden til playphase til startup phase behøver vi kun "deck"
    node* new_node = malloc(sizeof(node)); // laver plads i memory til det nye kort
    new_node->next = NULL;
    strncpy(new_node->value, value, 2);  // sætter værdi til den give string
    new_node->value[2] = '\0';

    // Check if the list is empty (root is NULL)
    if (*root == NULL) {  // sikker at curr ikke starter med at være null
        *root = new_node;
    } else {
        node* curr = *root;
        while (curr->next != NULL) {  // loop igennem til den finder det sidste element
            curr = curr->next;
        }
        curr->next = new_node; // tilføjer det nye element
    }
}
//----------------
int CHECK()
{
    int card_count = 0;
    char card[3];                // 3, 2 for char + 1 for Null (ny linje)
    char all_cards[52][3];       // Array med 52 kort og 3, 2 for char og 1 for ny linje some bruges til check

    FILE *file_check = fopen("unshuffled.txt", "r");

    while (fscanf(file_check, "%2s", card) == 1){
      strcpy(all_cards[card_count], card); // Kopier alle kort ind til vores Tjek array
      card_count++;
    }

    fclose(file_check);

    //Arbejdsplads (Still in the making)

  return 0; //No error
}
