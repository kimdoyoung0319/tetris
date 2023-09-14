#ifndef GAME_H
#define GAME_H

#include <map>
#include <memory>
#include <algorithm>
#include <chrono>
#include <thread>

#include "block.h"
#include "board.h"
#include "screen.h"
#include "utils.h"

typedef std::unique_ptr<Block> block_ptr_t;

class Game {
    private:
        bool is_game_end;
        CyclicCounter force_down_counter;
        RandomGenerator random_generator;

        Screen game_screen;
        Board game_board;
        block_ptr_t current_block;
        unsigned int score = 0;

        void run_single_frame();
        block_ptr_t generate_block();
        void sleep_for_frame_duration() const;
        void sleep_for_user_input() const;
        const char get_user_input() const;

        const unsigned int score_per_erased_row = 100;
        const unsigned int score_per_tetris = 1000;

    public:
        Game();

        void run();
};

#endif
