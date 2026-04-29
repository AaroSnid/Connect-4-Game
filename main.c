#include <stdint.h>
#include <cstdio>
#include <climits>

#include "board.h"

void display_board(uint64_t mask, uint64_t p1) {
    printf("\n  0 1 2 3 4 5 6\n"); // Column headers
    printf(" ---------------\n");

    // Iterate rows from top (5) to bottom (0)
    for (int row = 5; row >= 0; row--) {
        printf("| ");
        for (int col = 0; col < 7; col++) {
            // Calculate the bit index for this coordinate
            int bit_index = col * 7 + row;
            uint64_t bit = 1ULL << bit_index;

            if (!(mask & bit)) {
                // Not in the mask? Unplayed.
                printf("x ");
            } else if (p1 & bit) {
                // In mask and in P1? Player 1.
                printf("1 ");
            } else {
                // In mask but not in P1? Player 2 (0).
                printf("0 ");
            }
        }
        printf("|\n");
    }
    printf(" ---------------\n");
}

int choose_best_ai_move(uint64_t game_board, uint64_t p1_moves) {
    const unsigned char ordered_columns[7] = {3, 2, 4, 1, 5, 0, 6};
    const uint64_t ai_moves = game_board ^ p1_moves;
    int best_column = -1;
    int best_score = INT_MIN;

    for (int i = 0; i < 7; i++) {
        unsigned char col = ordered_columns[i];
        int bit_index = find_open_space(game_board, col);
        if (bit_index < 0) continue;

        uint64_t next_game_board = game_board | (1ULL << bit_index);
        uint64_t next_p1_moves = p1_moves;

        // Immediate wins are always preferred.
        if (is_won(ai_moves | (1ULL << bit_index))) return col;

        int score = -minimax(next_game_board, next_p1_moves, 1, -1000000, 1000000);
        if (score > best_score) {
            best_score = score;
            best_column = col;
        }
    }

    return best_column;
}

int main() {
    uint64_t bit_board = 0; // Represents all occupied slots
    uint64_t p1_moves = 0;  // Represents only Player 1's slots
    int move_num = 0;

    display_board(bit_board, p1_moves);

    while (move_num < 42) {
        if (move_num % 2 == 0) { // Player 1's Turn
            int column;
            printf("Enter column (0-6): ");
            if (scanf("%d", &column) != 1) {
                while (getchar() != '\n'); // Clear buffer
                continue;
            }

            if (column >= 0 && column < 7) {
                int location = play_move(bit_board, column);
                if (location >= 0) {
                    p1_moves |= (1ULL << location);
                    move_num++;
                    display_board(bit_board, p1_moves);
                    if (is_won(p1_moves)) {
                        printf("You won!\n");
                        return 0;
                    }
                } else {
                    printf("Column full!\n");
                }
            }
        } else { // AI's Turn (Player 0)
            int bot_column = choose_best_ai_move(bit_board, p1_moves);
            if (bot_column < 0) {
                break;
            }
            int location = play_move(bit_board, bot_column);
            if (location >= 0) {
                move_num++;
                printf("AI played column %d\n", bot_column);
                display_board(bit_board, p1_moves);
                // Player 0's board is (Total Board XOR Player 1's Board)
                if (is_won(bit_board ^ p1_moves)) {
                    printf("Yeah makes sense, you lost to a pretty smart AI\n");
                    return 0;
                }
            }
        }
    }

    printf("Tie game :(\n");
    return 0;
}