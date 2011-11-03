#include "../h/symbol_table.h"
using namespace std;
// std::vector<std::map<std::string, s_expression*> > vars;

void symbol_table::push() {
    map<string, s_expression> m;
    vars.push_back(m);
}

void symbol_table::pop() {
    vars.pop_back();
}

s_expression* symbol_table::get(string name) {
    for (int i=vars.size-1; i>=0; i--) {
        if (vars[i].count(name)) {
            return (vars[i])[name];
        }
    }
    return NULL;
}

void symbol_table::set(string name, s_expression* value) {
    (vars.back())[name] = value;
}

