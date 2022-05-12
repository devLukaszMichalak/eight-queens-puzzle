//
//  functions.h
//  hetman na spokojnie
//
//  Created by Łukasz Michalak on 12/05/2022.
//  Copyright © 2022 Łukasz Michalak. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc/malloc.h>
#include <unistd.h>

#define N 100

struct solutions{
    int row;
    int column;
};
struct field{
    int position[N][N];
    struct solutions hetman[N];
};
int finding_position(int what_queen,struct field *board,int size,int decision);
void capture(struct field *board,int lenght, int what_queen);
void filling_the_board(struct field *board,int size);
void restoration(struct field *board,int size,int what_queen);
int is_won(struct field *board,int size);
void drawing_board(struct field *board,int size,int what_queen);

#endif /* functions_h */
