#include "board.h"

Board::Board() : board_static(LENGTH_COL, vector<bool>(LENGTH_ROW, false)),
                 board_dynamic(LENGTH_COL, vector<bool>(LENGTH_ROW, false)) {
}

void Board::update_board(const Block & block) {
    const Coordinate & position = block.get_position();
    bool x_out_of_bound, y_out_of_bound;
    
    fill(board_dynamic.begin(), board_dynamic.end(), vector<bool>(LENGTH_ROW, false));
    
    for(int i = 0; i < BLOCK_SIDE; i++) {
        for(int j = 0; j < BLOCK_SIDE; j++) {
            x_out_of_bound = (position.x + j < 0) || (position.x + j >= LENGTH_ROW);
            y_out_of_bound = (position.y + i < 0) || (position.y + i >= LENGTH_COL);
            if(!x_out_of_bound && !y_out_of_bound)
                board_dynamic[position.y + i][position.x + j] = block.is_filled({j, i});
        }
    }
    
    return;
}

void Board::delete_last_line() {
    board_static.pop_back();
    board_static.emplace(board_static.begin(), vector<bool>(LENGTH_ROW, false));
    
    return;
}

void Board::fix_block() {
    for(int i = 0; i < LENGTH_COL; i++) {
        for(int j = 0; j < LENGTH_ROW; j++)
            board_static[i][j] = board_static[i][j] || board_dynamic[i][j];
    }
        
    fill(board_dynamic.begin(), board_dynamic.end(), vector<bool>(LENGTH_ROW, false));
    
    return;
}

bool Board::is_block_valid(const Block & block) const {
    const Coordinate & position = block.get_position();
    bool x_out_of_bound, y_out_of_bound, overlap;
    
    for(int i = 0; i < BLOCK_SIDE; i++){
        for(int j = 0; j < BLOCK_SIDE; j++){
            x_out_of_bound = ((position.x + j < 0) || (position.x + j >= LENGTH_ROW));
            y_out_of_bound = ((position.y + i < 0) || (position.y + i >= LENGTH_COL));
            if((x_out_of_bound || y_out_of_bound) && block.is_filled({j, i})) return false;
            
            if(!x_out_of_bound && !y_out_of_bound){
                overlap = board_static[position.y + i][position.x + j] && block.is_filled({j, i});
                if(overlap) return false;
            }
        }
    }
    
    return true;
}

bool Board::is_last_line_full() const {
    vector<bool> last_line = *board_static.rbegin();
    for(auto square : last_line){
        if(!square) return false;
    }
    
    return true;
}

bool Board::is_filled(const Coordinate & position) const {
    return board_static[position.y][position.x] || board_dynamic[position.y][position.x];
}

bool Board::is_filled_dynamic(const Coordinate & position) const {
    return board_dynamic[position.y][position.x];
}

bool Board::is_filled_static(const Coordinate & position) const {
    return board_static[position.y][position.x];
}
