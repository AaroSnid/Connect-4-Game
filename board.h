#ifndef BOARD_H_
#define BOARD_H_

#include <stdint.h>

/*
Bit board:

.  .  .  .  .  .  .
5 12 19 26 33 40 47
4 11 18 25 32 39 46
3 10 17 24 31 38 45
2  9 16 23 30 37 44
1  8 15 22 29 36 43
0  7 14 21 28 35 42

uint64_t = 0 0 ...  0 47 46 45 44 43 42  0 40 39 38 37 36 35  0 33 32 31 30 29 28  0 26 25 24 23 22 21  0 19 18 17 16 15 14  0 12 11 10  9  8  7  0  5  4  3  2  1  0
pos % 7 gives row number

*/


/* This function will find any 4 adjacent pieces on the given board */
bool is_won(uint64_t player_moves){

    // Directions listed as step size in finding adjacent pieces in bitboard
    // 1 = up/down, 6 = down to the right, 7 = right/left, 8 = up to the right
    unsigned char directions[4] = {1, 6, 7, 8};
    
    for (int i = 0; i < 4; i++){
        // Mask the board with itself shifted to find if the direction has adjacent pieces
        uint64_t two_adjacent = player_moves & (player_moves >> directions[i]);
        uint64_t four_adjacent = two_adjacent & (two_adjacent >> (2*directions[i]));
        if (four_adjacent) return true;
    }
    return false;
}

/* Returns 1 if the column is at capacity, 0 otherwise*/
bool is_playable(uint64_t game_board, unsigned char column){
    // Maps 0:5, 1:12, 2:19, etc
    return !(game_board & (1ULL << (7*column + 5)));
}

/* Plays the move in the given column. Returns the bit board position inserted at, or -1 for error */
int play_move(uint64_t &game_board, unsigned char column){
    if (is_playable(game_board, column)){

        // Find first non-played height and play there, starting from the bottom
        for (int row = 0; row < 6; row++){
            unsigned char bit_index = 7*column + row;

            if (!(game_board & (1ULL << bit_index))){
                game_board |= (1ULL << bit_index);
                return bit_index;
            }
        }
    }
    return -1;
}

#endif 