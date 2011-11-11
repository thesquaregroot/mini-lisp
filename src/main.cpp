#include <iostream>
#include "../h/interpreter.h"
using namespace std;

int main() {
    tokenizer tokens(false);
    interpreter interpret(tokens);

    if (!interpret.exec()) {
        cout << interpret.error() << endl;
        return 1;
    }
    return 0;
}
