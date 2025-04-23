#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 20

void print_card(Card card, int visible) {
    if (!visible) {
        printf("[ ]");
    } else {
        printf("%c%c", card.rank, card.suit);
    }
}

int get_column_height(Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

Node* get_nth_node(Node* head, int n) {
    for (int i = 0; i < n && head; i++) {
        head = head->next;
    }
    return head;
}
