#include "../h/symbol_table.h"
using namespace std;

// std::vector<std::map<std::string, s_expression*> > vars;
// std::map<std::string, s_expression*> params;
// std::map<std::string, s_expression*> bodies;

// public
s_expression* symbol_table::get(string& name) {
    for (int i=vars.size()-1; i>=0; i--) {
        if (vars[i].count(name) > 0) {
            return (vars[i])[name];
        }
    }
    return NULL;
}

void symbol_table::set(string& name, s_expression* value) {
    (vars.back())[name] = value;
}

void symbol_table::push() {
    map<string, s_expression*> m;
    vars.push_back(m);
}

void symbol_table::pop() {
    vars.pop_back();
}

s_expression* symbol_table::eval(s_expression*) {
    return NULL;    
}

