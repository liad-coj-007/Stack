#include "EmptyStack.h"
#include <string>
using namespace std;
const string msg = "the stack is empty!";

EmptyStack::EmptyStack():runtime_error(msg){}