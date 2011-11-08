#include <iostream>
#include "../h/interpreter.h"
using namespace std;

int main() {
    tokenizer tokens(cin);
    interpreter interpret(tokens);

    if (!interpret.exec()) {
        cout << interpret.error();
        return 1;
    }
    return 0;
}
