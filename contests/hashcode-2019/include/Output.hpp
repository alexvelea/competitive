#ifndef HASHCODE_OUTPUT_HPP
#define HASHCODE_OUTPUT_HPP

#include <ostream>

struct BaseOutput {
    virtual double Cost() = 0;
    virtual void Dump(std::ostream&) = 0;
};

void Dump(BaseOutput& output);

#ifndef hashcodeuselib
#include "Output.cpp"
#endif

#endif // HASHCODE__OUTPUT_HPP
