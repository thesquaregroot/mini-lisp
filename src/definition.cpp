#include "../h/definition.h"
using namespace std;

definition::definition(std::string n, int count) {
    name = n;
    arg_count = count;
}

bool definition::operator<(const definition d) const {
    if (this->name != d.name) {
        return (this->name < d.name);
    } else {
        return (this->arg_count < d.arg_count);
    }
}

