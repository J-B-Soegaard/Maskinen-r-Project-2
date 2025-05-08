//
// Created by Jacob Søgaard on 07/05/2025.
//

#include "GUI.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>
#include "commands.h"
#include "structures.h"
//

void drawColumn(SDL_Renderer* renderer, TTF_Font* font, node* root, int startX, int startY) {
    const int cardWidth = 40;
    const int cardHeight = 55;
    const int cardSpacing = 36;

    int y = startY;
    node* current = root;

    while (current!=NULL) {
        SDL_Rect cardRect = {startX, y, cardWidth, cardHeight};

        if (current->isHidden==0) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);  // blå bagside
            SDL_RenderFillRect(renderer, &cardRect);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // hvid forside
            SDL_RenderFillRect(renderer, &cardRect);

            char label[4] = {current->card.value, current->card.suit};

            SDL_Color textColor;
            if (current->card.suit == 'S' || current->card.suit == 'C') {
                textColor = (SDL_Color){0, 0, 0, 255};  // sort
            } else {
                textColor = (SDL_Color){255, 0, 0, 255};  // rød
            }


            SDL_Surface* surface = TTF_RenderText_Blended(font, label, textColor);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

           SDL_Rect textRect = {
                startX + (cardWidth - surface->w) / 2,
                y + (cardHeight - surface->h) / 2,
                surface->w, surface->h
            };

            SDL_RenderCopy(renderer, texture, NULL, &textRect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // sort kant
        SDL_RenderDrawRect(renderer, &cardRect);

        y = y+cardSpacing;
        current = current->next;
    }
}
//

void updateFond(SDL_Renderer* renderer, TTF_Font* font, node* head, int X, int Y) {
    const int cardWidth = 40;
    const int cardHeight = 55;
    node* current = head;
    while (current->next!=NULL) {
        current = current->next;
    }
    SDL_Rect cardRect = {X, Y, cardWidth, cardHeight};
    char label[4] = {current->card.value, current->card.suit, '\0'};
    SDL_Color textColor;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // hvid forside
    SDL_RenderFillRect(renderer, &cardRect);
    if (current->card.suit == 'S' || current->card.suit == 'C') {
        textColor = (SDL_Color){0, 0, 0, 255};  // sort
    } else if (current->card.suit == 'H' || current->card.suit == 'D') {
        textColor = (SDL_Color){255, 0, 0, 255};  // rød
    }else {
        textColor = (SDL_Color){255, 255, 255, 255};  // hvid
    }
    SDL_Surface* surface = TTF_RenderText_Blended(font, label, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect = {
        X + (cardWidth - surface->w) / 3,
        Y + (cardHeight - surface->h) / 3,
        surface->w, surface->h
    };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // sort kant
    SDL_RenderDrawRect(renderer, &cardRect);

    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
//

void Pgui(node** root) {
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
    deck=NULL;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;
    bool sdlInitialized = false;

    // Initialize SDL for the first time
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window = SDL_CreateWindow("Yukon",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    font = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 24);
    if (!font) {
        SDL_Log("Kunne ikke indlæse font: %s", TTF_GetError());
    }
    sdlInitialized = true;
    bool running = true;
 while(running) {
     node* Carr[7]={C1,C2,C3,C4,C5,C6,C7}; //gameboard
     node* Farr[4]={F1,F2,F3,F4}; // til gameboard
   char input[100];
   char FromCo[10];  // Column vi rykker fra
   char ToCo[10];    // Column vi rykker hen til
   char card[4] = "";  // Hvis der er angivet kort er det kortet vi ville rykke

     char MoveMessage[100];

     //
     //  GUI del
     SDL_Event event;
     SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);  // grøn baggrund
     SDL_RenderClear(renderer);  // Ryd skærmen først!

     drawColumn(renderer, font, C1, 100, 50);
     drawColumn(renderer, font, C2, 170, 50);
     drawColumn(renderer, font, C3, 240, 50);
     drawColumn(renderer, font, C4, 310, 50);
     drawColumn(renderer, font, C5, 380, 50);
     drawColumn(renderer, font, C6, 450, 50);
     drawColumn(renderer, font, C7, 520, 50);
     updateFond(renderer, font, F1, 700, 100);
     updateFond(renderer, font, F2, 700, 200);
     updateFond(renderer, font, F3, 700, 300);
     updateFond(renderer, font, F4, 700, 400);

     SDL_RenderPresent(renderer); // viser kortene på banen


     while (SDL_PollEvent(&event)) {
         if (event.type == SDL_QUIT) {
             running = false;
             if (sdlInitialized) {
                 TTF_CloseFont(font);
                 TTF_Quit();
                 SDL_DestroyRenderer(renderer);
                 SDL_DestroyWindow(window);
                 SDL_Quit();
             }

             // Free memory
             freeDeck(&C1);
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
             return;
         }
     }

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

   printf("Message: Indtast dit Move (eller Q for at Quit) \n");
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
         // lukker vinduet
        running = false;
            TTF_CloseFont(font);
            TTF_Quit();
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();


      // Når vi kommer tilbage i main kan vi printe:
      // sprintf(&message,"Quit Game. Deck has been saved. Use LD saved_deck\n");
      // Noget i den stil yk
      return;
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
        printf("Message: Ugyldig From \"%s\"\n", FromCo);	// Hvis input ikke er en gyldig C eller F print
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
        printf("Message: Ugyldig TO: \"%s\"\n", ToCo);	// Hvis input ikke er en gyldig C eller F print
          continue;
      }

        if (to != NULL && from != NULL)
        {
            move(from, card, to, MoveMessage);
        }
    } //If-else statement slut

 } //While loop slut

}



//
