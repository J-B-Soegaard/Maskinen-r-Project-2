#include <stdio.h>
#include <string.h>

int LD(char fileName[])
{
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL){
        FILE *fp = fopen("unshuffled.txt", "r"); // hvis ikke den der er givet en rigtigt fil navn så tag den det deck der sorteret.
    }
}

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
