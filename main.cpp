#include <iostream>
#include "block.h"
#include "board.h"

int main(void){
    Block block(SHAPE_Z);
    Board board;
    board.update_board(block);
    board.print_board();
    
    block.rotate_cw();
    board.update_board(block);
    board.print_board();
    block.rotate_ccw();
    board.update_board(block);
    board.print_board();
    
    return 0;
}