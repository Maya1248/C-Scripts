#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tile {  
    char name[15];
    char side;
} *tile;

// change it up; Make it "Tile" and name being a1, a2... Also a char* tile that represents the tile currently on it
// Idea; Board of Tiles and respective tiles (by name), CONTROLLER responsible for movement logic...

// UI for input interpretation -> CONTROLLER for movement logic -> WARDEN for state checks (King in check, Checkmate etc...)
//                              |-> Store overwritten tiles in the global CAPTURED1[] CAPTURED2[]

void initBoard(tile board[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            board[i][j] = NULL;
        }
    }
}

void freeBoard(tile board[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            free(board[i][j]);
            board[i][j] = NULL;
        }
    }
}

void fillBoard(tile board[8][8], int whiteFirst) {
    if (whiteFirst == 1) {
        // Rooks
        board[0][0] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][0]->name, "B. Rook  ");
        board[0][7] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][7]->name, "B. Rook  ");
        board[7][0] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][0]->name, "W. Rook  ");
        board[7][7] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][7]->name, "W. Rook  ");

        // Knights
        board[0][1] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][1]->name, "B. Knight ");
        board[0][6] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][6]->name, "B. Knight ");
        board[7][1] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][1]->name, "W. Knight ");
        board[7][6] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][6]->name, "W. Knight ");

        // Bishops
        board[0][2] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][2]->name, "B. Bishop ");
        board[0][5] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][5]->name, "B. Bishop ");
        board[7][2] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][2]->name, "W. Bishop ");
        board[7][5] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][5]->name, "W. Bishop ");

        // Kings & Queens
        board[0][3] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][3]->name, "B. Queen  ");
        board[0][4] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][4]->name, "B. King   ");
        board[7][3] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][3]->name, "W. Queen  ");
        board[7][4] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][4]->name, "W. King   ");

        // Pawns
        for (int i=0; i<8; i++) {
            board[1][i] = (tile)malloc(sizeof(struct Tile));
            strcpy(board[1][i]->name, "B. Pawn   ");

            board[6][i] = (tile)malloc(sizeof(struct Tile));
            strcpy(board[6][i]->name, "W. Pawn   ");
        }

        // Assign sides
        for (int i=0; i<2; i++) {
            for (int j=0; j<8; j++) {
                board[i][j]->side = 'B';
            }
        }
        for (int i=6; i<8; i++) {
            for (int j=0; j<8; j++) {
                board[i][j]->side = 'W';
            }
        }

    } else {
        // Rooks
        board[0][0] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][0]->name, "W. Rook   ");
        board[0][7] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][7]->name, "W. Rook   ");
        board[7][0] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][0]->name, "B. Rook   ");
        board[7][7] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][7]->name, "B. Rook   ");

        // Knights
        board[0][1] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][1]->name, "W. Knight ");
        board[0][6] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][6]->name, "W. Knight ");
        board[7][1] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][1]->name, "B. Knight ");
        board[7][6] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][6]->name, "B. Knight ");

        // Bishops
        board[0][2] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][2]->name, "W. Bishop ");
        board[0][5] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][5]->name, "W. Bishop ");
        board[7][2] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][2]->name, "B. Bishop ");
        board[7][5] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][5]->name, "B. Bishop ");

        // Kings & Queens
        board[0][3] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][3]->name, "W. Queen  ");
        board[0][4] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[0][4]->name, "W. King   ");
        board[7][3] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][3]->name, "B. Queen  ");
        board[7][4] = (tile)malloc(sizeof(struct Tile));
        strcpy(board[7][4]->name, "B. King   ");

        // Pawns
        for (int i=0; i<8; i++) {
            board[1][i] = (tile)malloc(sizeof(struct Tile));
            strcpy(board[1][i]->name, "W. Pawn   ");

            board[6][i] = (tile)malloc(sizeof(struct Tile));
            strcpy(board[6][i]->name, "B. Pawn   ");
        }

        // Assign sides
        for (int i=0; i<2; i++) {
            for (int j=0; j<8; j++) {
                board[i][j]->side = 'W';
            }
        }
        for (int i=6; i<8; i++) {
            for (int j=0; j<8; j++) {
                board[i][j]->side = 'B';
            }
        }
    }
} 

void printBoard(tile board[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (board[i][j] != NULL) {
                printf("%s\t", board[i][j]->name);
            } else {
                printf("[         ]\t");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void printLine() {
    for (int i=0; i<15*9; i++) {
        printf("-");
    }
    printf("\n");
}

int main() {
    tile board[8][8];

    initBoard(board); // initialize board; Fill an empty memory space with NULL pointers.

    printLine();

    fillBoard(board, 1); // fill the board in with traditional chess pieces and positions.
    printBoard(board); // print the board...

    printLine();

    freeBoard(board); // for each tile, if the space is occupied by a piece pointer, free it and set a NULL pointer; Else, just set a NULL pointer.
    printBoard(board); // print the empty board...

    return 0;
}
