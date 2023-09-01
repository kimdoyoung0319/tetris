#ifndef GAME_H
#define GAME_H

#include <memory>
#include <map>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "block.h"
#include "board.h"
#include "screen.h"

using std::unique_ptr;
using std::map;

constexpr int FRAME_DURATION_IN_MILLISECONDS = 100;
constexpr int MICROSECONDS_PER_MILLISECONDS = 1000;
constexpr int INITIAL_COUNTER = 5;

class Game {
    private:
        int block_down_counter;
        Screen game_screen;
        Board game_board;
        unique_ptr<Block> current_block;
        BlockType get_next_block() const;
        bool is_game_end();
        bool is_current_block_null() const;
        void run_single_frame();
        const char get_user_input() const;
    public:
        Game();
        void run();
};

#endif
