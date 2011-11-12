#ifndef DEFINITION_H
#define DEFINITION_H 1

#include <string>

struct definition {
    std::string name;
    int arg_count;

    definition(std::string n, int count);
    bool operator<(const definition d) const;
};

#endif
