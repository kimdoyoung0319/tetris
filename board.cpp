#include "board.h"

Board::Board() {
    board_static = vector<vector<bool>>(LENGTH_COL, vector<bool>(LENGTH_ROW, false));
    board_dynamic = vector<vector<bool>>(LENGTH_COL, vector<bool>(LENGTH_ROW, false));
}

void Board::print_board() const {
    for(int i = 0; i < LENGTH_ROW + 2; i++)
        cout << "■";
    cout << '\n';
    
    for(int i = 0; i < LENGTH_COL; i++){
        cout << "■";
        for(int j = 0; j < LENGTH_ROW; j++)
            cout << ((board_static[i][j] || board_dynamic[i][j]) ? "■" : "□");
        cout << "■\n";
    }
    
    for(int i = 0; i < LENGTH_ROW + 2; i++)
        cout << "■";
    cout << '\n';
    
    return;
}

void Board::update_board(const Block & block) {
    const Coordinate & position = block.get_position();
    const vector<vector<bool>> & shape = block.get_shape();
    bool x_out_of_bound, y_out_of_bound;
    
    fill(board_dynamic.begin(), board_dynamic.end(), vector<bool>(LENGTH_ROW, false));
    
    for(int i = 0; i < BLOCK_SIDE; i++){
        for(int j = 0; j < BLOCK_SIDE; j++){
            x_out_of_bound = (position.x + j < 0) || (position.x + j >= LENGTH_ROW);
            y_out_of_bound = (position.y + i < 0) || (position.y + i >= LENGTH_COL);
            if(!x_out_of_bound && !y_out_of_bound)
                board_dynamic[position.y + i][position.x + j] = shape[i][j];
        }
    }
    
    return;
}

bool Board::check_block(const Block & block) const {
    const Coordinate & position = block.get_position();
    const vector<vector<bool>> & shape = block.get_shape();
    bool x_out_of_bound, y_out_of_bound, overlap;
    
    for(int i = 0; i < BLOCK_SIDE; i++){
        for(int j = 0; j < BLOCK_SIDE; j++){
            x_out_of_bound = ((position.x + j < 0) || (position.x + j >= LENGTH_ROW));
            y_out_of_bound = ((position.y + i < 0) || (position.y + i >= LENGTH_COL));
            if((x_out_of_bound || y_out_of_bound) && shape[i][j]) return false;
            
            if(!x_out_of_bound && !y_out_of_bound){
                overlap = board_static[position.y + i][position.x + j] && shape[i][j];
                if(overlap) return false;
            }
        }
    }
    
    return true;
}