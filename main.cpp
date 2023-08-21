#include <iostream>
#include "block.h"
#include "board.h"

int main(void){
    Block block(SHAPE_O);
    Board board;
    board.update_board(block);
    board.print_board();
    
    while(true){
        block.move_down();
        if(board.check_block(block)){
            board.update_board(block);
            board.print_board();
        } else{
            break;
        }
    }
    
    board.fix_block();
    if(board.check_last_line())
        board.delete_last_line();
    board.print_board();
    
    return 0;
}