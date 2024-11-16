#pragma once
#include <stdexcept>
using namespace std;
class EmptyStack: public runtime_error{
public:
    /**
     * @brief defualt constractor
     */
    EmptyStack();
};