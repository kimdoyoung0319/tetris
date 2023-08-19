#include <iostream>
#include "block.h"
#include "board.h"

int main(void){
    vector<vector<bool>> shape = {
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
    };
    
    Block block(shape);
    Board board;
    
    board.print_board();
    board.update_board(block);
    std::cout << "-----------------------------" << std::endl;
    board.print_board();
    block.move_right();
    board.update_board(block);
    std::cout << "-----------------------------" << std::endl;
    board.print_board();
    
    return 0;
}