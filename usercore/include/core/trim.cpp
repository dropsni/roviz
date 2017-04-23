
#include "trim.h"

Trim::Trim(std::string name, double min, double max, int steps, bool num_of_steps)
    : TrimDevBase(name, min, max, steps, num_of_steps)
{
}

Trim::Trim(Trim &&trim)
    : TrimBase(std::move(trim))
{
}

Trim &Trim::operator=(Trim &&trim)
{
    TrimBase::operator=(std::move(trim));
    return *this;
}

double Trim::value() const
{
    return TrimBase::value();
}
