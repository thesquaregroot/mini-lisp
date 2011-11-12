#ifndef DEFINITION_H
#define DEFINITION_H 1

#include <string>

struct definition {
    std::string name;
    int arg_count;

    definition(std::string n, int count) {
        name = n;
        arg_count = count;
    }

    bool operator<(const definition d) const {
        if (this->name != d.name) {
            return (this->name < d.name);
        } else {
            return (this->arg_count < d.arg_count);
        }
    }
};

#endif
