#include <iostream>
#include <vector>
#include <memory>

class Foo;

typedef std::vector<std::vector<bool>> matrix_t;
typedef std::unique_ptr<Foo> foo_ptr_t;

const matrix_t initial_matrix = {{0, 1}, {1, 0}};

class Foo {
    protected:
        matrix_t matrix;
        Foo(matrix_t matrix) : matrix(matrix) {}

    public:
        Foo() {}

        const matrix_t & get_matrix() const {
            return matrix;
        }
};

class Bar : public Foo {
    public:
        Bar() : Foo(initial_matrix) {}
};

int main(void) {
    foo_ptr_t foop = std::make_unique<Bar>();

    if(foop->get_matrix().empty())
        std::cout << "Empty!\n";
    else
        std::cout << "Filled!\n";

    /*
    for(row_t row : foop->matrix) {
        for(bool e : row)
            std::cout << int(e);
        std::cout << '\n';
    }
    */


    return 0;
}
