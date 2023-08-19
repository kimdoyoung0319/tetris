#include <iostream>
#include "board.h"
#include "block.h"

Board::Board() {
    board = vector<vector<bool>>(LENGTH_COL, vector<bool>(LENGTH_ROW, false));
}

void Board::print_board() const {
    for(int i = 0; i < LENGTH_ROW + 2; i++)
        std::cout << "■";
    std::cout << std::endl;
    
    for(vector<bool> row : board){
        std::cout << "■";
        for(bool square : row)
            std::cout << (square ? "■" : "□");
        std::cout << "■" << std::endl;
    }
    
    for(int i = 0; i < LENGTH_ROW + 2; i++)
        std::cout << "■";
    std::cout << std::endl;
    
    return;
}

//must be executed after check_position
void Board::update_board(const Block & block) {
    Coordinate position = block.get_position();
    vector<vector<bool>> shape = block.get_shape();
    
    for(int i = 0; i < BLOCK_SIDE; i++)
        for(int j = 0; j < BLOCK_SIDE; j++)
            board[position.y + i][position.x + j] = shape[i][j];
    
    return;
}

void Board::delete_line() {
    board.pop_back();
    board.insert(board.begin(), vector<bool>(LENGTH_ROW, false));
    
    return;
}

bool Board::check_position(const Block & block) const {
    Coordinate position = block.get_position();
    vector<vector<bool>> shape = block.get_shape();
    bool x_out_of_bound, y_out_of_bound, overlap;
    
    for(int i = 0; i < BLOCK_SIDE; i++){
        for(int j = 0; i < BLOCK_SIDE; i++){
            x_out_of_bound = ((position.x + i < 0) || (position.x + i >= LENGTH_ROW)) && shape[i][j];
            y_out_of_bound = ((position.y + j < 0) || (position.y + j >= LENGTH_COL)) && shape[i][j];
            overlap = board[position.x + i][position.y + j] && shape[i][j];
            
            if(x_out_of_bound || y_out_of_bound || overlap) return false;
        }
    }
    
    return true;
}

bool Board::check_end(const Block & next_block) const {
    Coordinate position = INITIAL_POS;
    vector<vector<bool>> shape = next_block.get_shape();
    bool overlap;
    
    for(int i = 0; i < BLOCK_SIDE; i++){
        for(int j = 0; j < BLOCK_SIDE; j++){
            overlap = board[position.x + i][position.y + j] && shape[i][j];
            if(overlap) return true;
        }
    }
    
    return false;
}

bool Board::check_line() const {
    vector<bool> last_line = board[LENGTH_COL - 1];
    
    for(bool square : last_line)
        if(!square) return false;
    
    return true;
}