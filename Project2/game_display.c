#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

// if u want to change max number of cards for each column change this value
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
void display_game(GameState* state) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");

    int max_rows = 0;
    for (int i = 0; i < 7; i++) {
        int h = get_column_height(state->columns[i]);
        if (h > max_rows) max_rows = h;
    }
    
    for (int row = 0; row < max_rows; row++) {
        for (int col = 0; col < 7; col++) {
            Node* node = get_nth_node(state->columns[col], row);
            if (node) {
                print_card(node->card, node->visible);
            } else {
                printf("   ");
            }
            printf("\t");
        }
        printf("\n");
    }

    for (int i = 0; i < 4; i++) {
        printf("[] F%d\t", i + 1);
    }
    printf("\n\n");

    printf("LAST Command: %s\n", state->last_cmd);
    printf("Message: %s\n", state->message);
    printf("INPUT > ");
}
