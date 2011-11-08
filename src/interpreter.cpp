#include "../h/itos.h"
#include "../h/interpreter.h"
using namespace std;

// symbol_table symbols;
// tokenizer ins;
// std::string err_msg;

/// private
s_expression* interpreter::get_exp() {
    return symbols.
}

/// public
interpreter::interpreter(tokenizer& tokens) {
    ins = tokens;
}

bool interpreter::exec() {

}

string interpreter::error() {
    return ("ERROR: line " + itos(ins.lineno) + ": " + err_msg);
}

