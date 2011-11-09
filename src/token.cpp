
#include "../h/token.h"
using namespace std;

token::token() {
    type = ERROR;
}

token::token(token_type t, string str) {
    type = t;
    lex_val = str;
}

