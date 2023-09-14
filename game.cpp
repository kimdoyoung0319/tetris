#include "game.h"

Game::Game() : force_down_counter(), 
               game_screen(),
               game_board(), 
               current_block(generate_block()),
               random_generator(BLOCK_I, BLOCK_Z) {
    game_screen.update_score_window(score);
    game_screen.update_message_window(Screen::MESSAGE_EMPTY);
}

void Game::run() {
    do {
        run_single_frame();
    } while(!is_game_end);

    game_screen.update_message_window(Screen::MESSAGE_GAME_OVER);
    sleep_for_user_input();

    return;
}

void Game::run_single_frame() {
    sleep_for_frame_duration();

    if(!current_block) {
        current_block = generate_block();

        if(!game_board.is_valid(*current_block)) {
            is_game_end = true;
            return;
        }
    }

    bool is_block_bottom_touched = false;

    if(force_down_counter.is_zero()) {
        current_block->move_down();

        if(game_board.is_valid(*current_block)) {
            game_screen.update_main_window(game_board, *current_block);
        } else {
            current_block->undo();
            is_block_bottom_touched = true;
        }
    }

    force_down_counter--;

    char user_input = get_user_input();
    switch(user_input) {
        case 'h':
            current_block->move_left();
            break;
        case 'j':
            current_block->move_down();

            if(!game_board.is_valid(*current_block)) {
                current_block->undo();
                is_block_bottom_touched = true;
            }

            break;
        case 'k':
            current_block->rotate();
            break;
        case 'l':
            current_block->move_right();
            break;
    }

    if(game_board.is_valid(*current_block))
        game_screen.update_main_window(game_board, *current_block);
    else
        current_block->undo();

    unsigned int erased_rows;

    if(is_block_bottom_touched) {
        game_board.fix(*current_block);
        current_block.reset();

        erased_rows = game_board.erase_full_rows();

        if(erased_rows == 4) {
            score += score_per_tetris;
            game_screen.update_message_window(Screen::MESSAGE_TETRIS);
        } else if(erased_rows > 0) {
            //The value MESSAGE_SINGLE, MESSAGE_DOUBLE, and MESSAGE_TRIPLE has initial value of 1, 2, 3...
            //So, the static_cast of integer to MessageType converts the number of erased rows to the message.
            score += erased_rows * score_per_erased_row;
            game_screen.update_message_window(static_cast<Screen::MessageType>(erased_rows));
        } else {
            game_screen.update_message_window(Screen::MESSAGE_EMPTY);
        }

        game_screen.update_main_window(game_board);
        game_screen.update_score_window(score);

        return;
    }

    return;
}

void Game::sleep_for_frame_duration() const {
    static const std::chrono::milliseconds frame_duration_in_ms(100);
    std::this_thread::sleep_for(frame_duration_in_ms);

    return;
}

block_ptr_t Game::generate_block() {
    using std::map;
    using std::pair;
    using std::all_of;

    static map<BlockType, bool> is_generated;

    bool is_every_type_generated 
        = all_of(is_generated.begin(),
                 is_generated.end(),
                 [](pair<BlockType, bool> e) {return e.second;});

    if(is_every_type_generated) {
        is_generated.clear();

        for(int i = BLOCK_I; i != BLOCK_Z; i++)
            is_generated[static_cast<BlockType>(i)] = false;
    }

    BlockType random_block_type;

    do {
        random_block_type
            = static_cast<BlockType>(random_generator());
    } while(is_generated[random_block_type]);

    is_generated[random_block_type] = true;

    switch(random_block_type) {
        case BLOCK_I: return block_ptr_t(new IBlock()); 
        case BLOCK_J: return block_ptr_t(new JBlock()); 
        case BLOCK_L: return block_ptr_t(new LBlock()); 
        case BLOCK_O: return block_ptr_t(new OBlock()); 
        case BLOCK_S: return block_ptr_t(new SBlock()); 
        case BLOCK_T: return block_ptr_t(new TBlock()); 
        case BLOCK_Z: return block_ptr_t(new ZBlock()); 
        default: return nullptr;
    }
}

void Game::sleep_for_user_input() const {
    wtimeout(game_screen.main_window, -1);
    wgetch(game_screen.main_window);
    wtimeout(game_screen.main_window, 0);

    return;
}

const char Game::get_user_input() const {
    char user_input = wgetch(game_screen.main_window);
    flushinp();
    return user_input;
}
