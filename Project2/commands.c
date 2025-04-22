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
    int counter = 0; // hver 7 skal den lave ny linje
    int fCounter = 1; // sætter f på de rigtige steder
    int numberF=0;  // +1 hver gang f bliver sat så vi får f1,f2,f3,f4
    for (node* curr = deck; curr != NULL; curr = curr->next) {
        if (curr->isHidden == 1) {
            printf("%s", curr->value); // hvis kortet vender op ad
        }else {
            printf("[]"); // hvis kortet vender ned af
        }
        printf("\t");
        counter++;

        if (counter == 7) {  // ny linje hver 7 søjle.
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
void saveCard(node** root,char name[255]) { 
    if (name == NULL) {
        name = "cards.txt"; // hvis filen ikke får et navn
    }
    FILE *fp = fopen(name, "w");
    node* curr = *root;
    while (curr != NULL) { // decket burde allerede være checket igennem, så derfor ingen behøve for sikkerhed.
        fprintf(fp, "%s\n", curr->value); //printer værdi i filen.
        curr = curr->next; //næste værdi
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
        all_cards[card_count][2] = '0'; // '0' betyder ikke brugt, '1' betyder allerede brugt (For check af dup kort)
        card_count++;
    }
    fclose(file_check);

    //Arbejdsplads (Still in the making)

  return 0; //No error
}
