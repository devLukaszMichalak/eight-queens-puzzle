//
//  functions.c
//  hetman na spokojnie
//
//  Created by Łukasz Michalak on 12/05/2022.
//  Copyright © 2022 Łukasz Michalak. All rights reserved.
//

#include "functions.h"

void filling_the_board(struct field *board,int size){
    int i,j;
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            board->position[i][j]=1;//wszystkie pola zdolne do gry
        }
    }
}

void capture(struct field *board,int lenght,int what_queen){
    int i,j,k=0;
    for(i=board->hetman[what_queen].row;i<lenght;i++){
        board->position[board->hetman[what_queen].row+k][board->hetman[what_queen].column]=0;
        k++;//above queen
    }
    k=0;
    for(i=board->hetman[what_queen].row;i>-1;i--){
        board->position[board->hetman[what_queen].row-k][board->hetman[what_queen].column]=0;
        k++;//below queen
    }
    k=0;
    for(i=board->hetman[what_queen].column;i<lenght;i++){
        board->position[board->hetman[what_queen].row][board->hetman[what_queen].column+k]=0;
        k++;//on the right of the queen
    }
    k=0;
    for(i=board->hetman[what_queen].column;i>-1;i--){
        board->position[board->hetman[what_queen].row][board->hetman[what_queen].column-k]=0;
        k++;//left
    }
    k=0;
    for(i=board->hetman[what_queen].row,j=board->hetman[what_queen].column;i<lenght&&j<lenght;i++,j++){
        board->position[board->hetman[what_queen].row+k][board->hetman[what_queen].column+k]=0;
        k++;//right up
    }
    k=0;
    for(i=board->hetman[what_queen].row,j=board->hetman[what_queen].column;i>-1&&j>-1;i--,j--){
        board->position[board->hetman[what_queen].row-k][board->hetman[what_queen].column-k]=0;
        k++;//left down
    }
    k=0;
    for(i=board->hetman[what_queen].row,j=board->hetman[what_queen].column;i>-1&&j<lenght;i--,j++){
        board->position[board->hetman[what_queen].row-k][board->hetman[what_queen].column+k]=0;
        k++;//right down
    }
    k=0;
    for(i=board->hetman[what_queen].row,j=board->hetman[what_queen].column;i<lenght&&j>-1;i++,j--){
        board->position[board->hetman[what_queen].row+k][board->hetman[what_queen].column-k]=0;
        k++;//left up
    }
}

void restoration(struct field *board,int size,int what_queen){
    filling_the_board(board, size);
    for(what_queen-=1;what_queen>-1;what_queen--){
    capture(board,size,what_queen);//old captures queen
    }
}
int is_won(struct field *board,int size){
    int f,g,checking=0;
    for(f=0;f<size;f++){
        for(g=0;g<size;g++){
            checking++;
        }
    }
    if(checking==size*size){
        return 1;
    }
    else{
        return 0;
    }
}

int finding_position(int what_queen,struct field *board,int size,int decision){
    int i,numerator=0,END=0,k;
    for(i=0;i<size;i++){
        if(END==1){
            return END;
        }
        else if(what_queen==size){
            return END;
        }
        if(board->position[i][what_queen]==1){
            board->hetman[what_queen].row=i;
            board->hetman[what_queen].column=what_queen;//dane nowego hetmana zapisane
            capture(board,size,what_queen);//zamienia niedozwolone pola na 0
            if(decision==1){
                //getchar();
                usleep(700000);
                system("clear");
                printf("\nUstawiamy hetmana na polu %d,%d\n",board->hetman[what_queen].column,board->hetman[what_queen].row);
                drawing_board(board, size,what_queen+1);
            }
            END=finding_position(what_queen+1, board, size,decision);
            numerator++;
            if(what_queen==size-1){ //jezeli to ostatni chteman to sprawdz czy to koniec
                END=is_won(board, size);
                if(END==1){
                    return END;
                }
            }
            if(END==0){
                restoration(board, size, what_queen);//odnowa planszy to tego sprzed sprawdzenia hetmana+1
                if(decision==1){
                    system("clear");
                    printf("\nNie da sie postawic. Cofamy sie\n");
                    drawing_board(board, size,what_queen+1);
                }
                for(k=0;k<numerator;k++){
                    board->position[board->hetman[what_queen].row-k][board->hetman[what_queen].column]=0;//zamiania pola juz sprawdzone na 0 zeby nie krecic sie w nieskonczonosc
                }
            }
    }
    }
    return END;
}

void drawing_board(struct field *board,int size,int what_queen){
    int g,f;
    printf("  ");
    for(f=0;f<size;f++){
        if(f<10){
        printf("  %d ",f);
        }
        else if(f>9){
            printf("  %d",f);
        }
    }
    printf("\n");
    for(g=0;g<what_queen;g++){
        board->position[board->hetman[g].row][board->hetman[g].column]=42;
    }
    printf("  ");
    for(g=0;g<4*size+1;g++){
        printf("-");
    }
    printf("\n");
    for(f=0;f<size;f++){
        if(f<10){
            printf("%d ",f);
        }
        else if(f>9){
            printf("%d",f);
        }
        for(g=0;g<size;g++){
            printf("|");
            if(board->position[f][g]==42){
                printf(" X ");
            }
            else{
                printf("   ");
            }
        }
        printf("|");
        printf("\n  ");
        for(g=0;g<4*size+1;g++){
            printf("-");
        }
        printf("\n");
    }
}
