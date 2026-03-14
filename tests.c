#include "board.h"

// Each entry is a bitboard for ONE player. 
// None of these contain bits in the buffer rows (6, 13, 20, 27, 34, 41, 48).
const uint64_t win_test_boards[] = {
0xFULL,                 // 0: Vertical (0,1,2,3)
    0xF0000000ULL,          // 1: Vertical (28,29,30,31)
    0x3CULL,                // 2: Vertical (1,2,3,4)
    0x10204080ULL,          // 3: Horizontal (7,14,21,28) - Row 0
    0x204081000000ULL,      // 4: Horizontal (21,28,35,42) - Row 0
    0x40810204000ULL,       // 5: Horizontal (15,22,29,36) - Row 1
    0x1010101ULL,           // 6: Diag / (0,8,16,24)
    0x101010100ULL,         // 7: Diag / (8,16,24,32)
    0x10101010000ULL,       // 8: Diag / (16,24,32,40)
    0x41041040ULL,          // 9: Diag \ (6,12,18,24)
    0x104104104000000ULL,   // 10: Diag \ (26,32,38,44)
    0x7ULL,                 // 11: Near Miss Vert (3-in-a-row)
    0x4080ULL,              // 12: Near Miss Horiz (2-in-a-row)
    0x10101ULL,             // 13: Near Miss Diag (3-in-a-row)
    0x1000101ULL,           // 14: Near Miss Gap
    0x10041ULL              // 15: Near Miss Gap
};

const bool win_test_expected[] = {
true, true, true, true, true, true, true, true, true, true, true,
    false, false, false, false, false
};

void run_bitboard_tests() {
    int total_tests = sizeof(win_test_boards) / sizeof(win_test_boards[0]);
    
    for (int i = 0; i < total_tests; i++) {
        bool result = is_won(win_test_boards[i]);
        
        if (result == win_test_expected[i]) {
            printf("Pass\n");
        } else {
            printf("Fail\n");
        }
    }
}