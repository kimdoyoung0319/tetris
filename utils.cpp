#include "utils.h"

CyclicCounter::CyclicCounter(int initial_value) : initial_value(initial_value),
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
