#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_card(Card card, int visible) {
    if (!visible) {
        printf("[ ]");
    } else {
        printf("%c%c", card.rank, card.suit);
    }
}
