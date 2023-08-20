#include <iostream>
#include "block.h"
#include "board.h"

int main(void){
    Block block(SHAPE_O);
    Board board;
    board.update_board(block);
    board.print_board();
    
    while(true){
        block.move_right();
        if(board.check_block(block)){
            board.update_board(block);
            board.print_board();
        } else{
            break;
        }
    }
    
    return 0;
}