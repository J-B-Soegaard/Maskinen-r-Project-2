#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-----

typedef struct node {  // struct til at lave linked list med kortene
    char value[3];
    struct node *next; // bevæger kun 1 pointer til at pege frem ikke nogen til at pege tilbage
    int isHidden; // om kortet er oppe eller nede
}node;

node* deck = NULL;  //global fil tror jeg

//------------------
void createCard(node** root, char value[3]);
void LD(char fileName[])
{
    char temp[4];
    FILE *fp;




fp = fopen(fileName, "r");

    if (fp == NULL)
    {
        FILE *fp = fopen("unshuffled.txt", "r"); // hvis ikke den der er givet en rigtigt fil navn så tag den det deck der sorteret.
    }
    while (fgets(temp, 4, fp)!=NULL) {
        createCard(&deck, temp);

    }
    fclose(fp);


}
//------------------

void createCard(node** root, char value[4]) {
    node* new_node = malloc(sizeof(node));
    new_node->next = NULL;
    strncpy(new_node->value, value, 2);
    new_node->value[2] = '\0';
    new_node->isHidden = 0;

    // Check if the list is empty (root is NULL)
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
            printf("%s", curr->value);
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

}
//--
void SW() {
    node* curr = deck;
    while ( curr != NULL) {
        curr->isHidden = 1;
        curr=curr->next;
    }
    createBoard();
}
//---------------
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
