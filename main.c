//
//  main.c
//  hetman na spokojnie
//
//  Created by Łukasz Michalak on 13/12/2018.
//  Copyright © 2018 Łukasz Michalak. All rights reserved.
//

#include "functions.h"

int main(int argc,char* argv[]){
    system("clear");
    struct field board;
    int size,g=1,decisionn;
    printf("Podaj wielkosc planszy (conajmniej 4)\n");
    scanf("%2d",&size);
    //wielkosc=atoi(argv[1]);
    if(size<4){
        printf("Wielkosc planszy musi byc conajmniej 4 zeby algorytm mogl zadzialac! ");
        return 1;
    }
    filling_the_board(&board, size);
    printf("\nMiejsca hetmanow na planszy beda zaznaczone znakiem X\nCzy chcesz zobaczyc animacje rozwiazywania?(UWAGA! Dla duzych tablic moze byc dluga!)\n[1 - Tak,0 - Nie]\n");
    scanf("%d",&decisionn);
    finding_position(0, &board, size,decisionn);
    system("clear");
    printf("Wynik prezentuje sie nastepujaco\nWspolrzedne hetmanow to:\n");
    for(g=0;g<size;g++){
        printf("Hetman nr %d: %d,%d\n",g+1,board.hetman[g].column,board.hetman[g].row);
    }
    drawing_board(&board, size,size);
    return 0;
}

