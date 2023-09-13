#ifndef GAME_H
#define GAME_H

#include <map>
#include <memory>
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>
#include <cstdlib>
#include <ctime>

#include "block.h"
#include "board.h"
#include "screen.h"

typedef std::unique_ptr<Block> block_ptr_t;

class CyclicCounter {
    private:
        const int initial_value;
        int value;

    public:
        CyclicCounter(int);

        bool is_zero() const;
        CyclicCounter operator--(int);
};

class RandomGenerator {
    private:
        std::random_device device;
        std::minstd_rand generator;
        std::uniform_int_distribution<int> distribution;

    public:
        RandomGenerator(int, int);

        int operator()();
};

class Game {
    private:
        bool is_game_end;
        CyclicCounter force_down_counter;
        RandomGenerator random_generator;

        Screen game_screen;
        Board game_board;
        block_ptr_t current_block;

        void run_single_frame();
        block_ptr_t generate_block();
        void sleep_for_frame_duration() const;
        const char get_user_input() const;

    public:
        Game();

        void run();
};

#endif
