#include "game.h"

CyclicCounter::CyclicCounter(int initial_value = 5) : initial_value(initial_value), 
                                                      value(initial_value) {
}

bool CyclicCounter::is_zero() const {
    return value == 0;
}

CyclicCounter CyclicCounter::operator--(int) {
    CyclicCounter original = *this;

    if(is_zero())
        value = initial_value;
    else
        value--;

    return original;
}

//Constructs random number generator that produces random number in range of [first, last].
RandomGenerator::RandomGenerator(int first, int last) : device(),
                                                        generator(device()),
                                                        distribution(first, last) {
}

int RandomGenerator::operator()() {
    return distribution(generator);
}

Game::Game() : force_down_counter(), 
               game_screen(),
               game_board(), 
               current_block(generate_block()),
               random_generator(BLOCK_I, BLOCK_Z) {
}

void Game::run() {
    do {
        run_single_frame();
    } while(!is_game_end);

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

    if(is_block_bottom_touched) {
        game_board.fix(*current_block);
        current_block.reset();
        game_board.erase_full_rows();
        game_screen.update_main_window(game_board);

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

const char Game::get_user_input() const {
    char user_input = wgetch(game_screen.main_window);
    flushinp();
    return user_input;
}
