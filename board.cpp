#include "board.h"

Board::Board() : shape(col_size, row_t(row_size, false)) {
}

/*
void Board::erase_last_row() {
    shape.pop_back();
    shape.emplace(shape.begin(), row_t(row_size, false));
    
    return;
}
*/

void Board::erase_full_rows() {
    using std::all_of;
    using std::remove_if;
    using std::function;

    function<bool(row_t)> is_row_full = [](row_t row) {
        return all_of(row.begin(), row.end(), [](bool e) {return e;});
    };

    //check out erase-remove idiom
    //need to be explained by a comment.
    shape.erase(remove_if(shape.begin(), shape.end(), is_row_full), shape.end());

    int rows_to_insert = col_size - shape.size();

    for(int i = 0; i < rows_to_insert; i++)
        shape.emplace(shape.begin(), row_t(row_size, false));

    return;
}

void Board::fix(const Block & block) {
    Coordinate position = block.get_position();

    for(int i = 0; i < block.col_size; i++) {
        for(int j = 0; j < block.row_size; j++) {
            if(block.is_filled({j, i}))
                shape[position.y + i][position.x + j] = true;
        }
    }
    
    return;
}

/*
bool Board::is_last_row_full() const {
    row_t last_row = *shape.rbegin(); 

    for(bool square : last_row) {
        if(!square)
            return false;
    }
    
    return true;
}
*/

bool Board::is_valid(const Block & block) const {
    const Coordinate & position = block.get_position();
    
    for(int i = 0; i < block.col_size; i++){
        for(int j = 0; j < block.row_size; j++){
            if(block.is_filled({j, i})) {
                if(is_coordinate_out_of_bound({position.x + j, position.y + i}))
                    return false;

                if(is_filled({position.x + j, position.y + i}))
                    return false;
            }
        }
    }
    
    return true;
}

bool Board::is_coordinate_out_of_bound(const Coordinate & coordinate) const {
    bool x_out_of_bound = (coordinate.x < 0 || coordinate.x >= row_size);
    bool y_out_of_bound = (coordinate.y < 0 || coordinate.y >= col_size);

    return x_out_of_bound || y_out_of_bound;
}

bool Board::is_filled(const Coordinate & position) const {
    return shape[position.y][position.x];
}
