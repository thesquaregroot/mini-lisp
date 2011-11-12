#include "../h/symbol_table.h"
using namespace std;

// std::vector<std::map<std::string, s_expression*> > vars;
// std::map<definition, s_expression*> funcs;

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

void symbol_table::define(string& name, s_expression* args, s_expression* body) {
    definition def = definition(name, args->size());
    s_expression* s = new s_expression();
    s->car() = args;
    s->cdr() = body;
    funcs[def] = s;  // overwrites previous definitions if they exists
}

/* Returns the arguments and boyd of a function with the given name and number of arguments
//  in the following structure of s-expression:
//     .
//    / \
// args body
*/
s_expression* symbol_table::retrieve(string& name, int arg_count) {
    definition def = definition(name, arg_count);
    if (funcs.count(def) > 0) {
        return funcs[def];
    } else {
        return NULL; // not defined
    }
}

