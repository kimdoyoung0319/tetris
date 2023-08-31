#include "game.h"

Game::Game() : block_down_counter(INITIAL_COUNTER), game_screen(), game_board() {
    srand(time(NULL));
}

void Game::run() {
    do {
        run_single_frame();
    } while(!is_game_end());

    return;
}

void Game::run_single_frame() {
    usleep(FRAME_DURATION_IN_MILLISECONDS * MICROSECONDS_PER_MILLISECONDS);

    if(!current_block)
        current_block = unique_ptr<Block>(new Block(get_next_block()));

    if(!block_down_counter) {
        current_block->move_down();
        block_down_counter = INITIAL_COUNTER;
    }
    block_down_counter--;

    if(game_board.is_block_valid(*current_block)) {
        game_board.update_board(*current_block);
    } else {
        current_block->undo();
        game_board.fix_block();
        current_block.reset(nullptr);
        game_screen.update_main_window(game_board);
        return;
    }

    char user_input = get_user_input();
    switch(user_input) {
        case 'h':
            current_block->move_left();
            break;
        case 'j':
            current_block->move_down();
            if(!game_board.is_block_valid(*current_block)) {
                current_block->undo();
                game_board.fix_block();
                current_block.reset(nullptr);
                game_screen.update_main_window(game_board);
                return;
            }
            break;
        case 'k':
            current_block->rotate_ccw();
            break;
        case 'l':
            current_block->move_right();
            break;
    }

    if(game_board.is_block_valid(*current_block))
        game_board.update_board(*current_block);
    else
        current_block->undo();

    if(game_board.is_last_line_full())
        game_board.delete_last_line();

    game_screen.update_main_window(game_board);

    return;
}

BlockType Game::get_next_block() const {
    BlockType random_block_type;
    static map<BlockType, bool> block_appeared;
    bool is_all_value_true = true;

    for(auto it = block_appeared.begin(); it != block_appeared.end(); it++) {
        if(!it->second) 
            is_all_value_true = false;
    }

    if(is_all_value_true)
        block_appeared = map<BlockType, bool> {
            {BLOCK_I, false},
            {BLOCK_J, false},
            {BLOCK_L, false},
            {BLOCK_O, false},
            {BLOCK_S, false},
            {BLOCK_T, false},
            {BLOCK_Z, false},
        };

    do {
        random_block_type = static_cast<BlockType>(rand() % 7);
    } while(block_appeared[random_block_type]); 

    block_appeared[random_block_type] = true;

    return random_block_type;
}

const char Game::get_user_input() const {
    char user_input = wgetch(game_screen.main_window);
    flushinp();
    return user_input;
}

//need to be modified
bool Game::is_game_end() const {
    return false;
}

