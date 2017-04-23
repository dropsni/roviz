
#include "trim.h"

Trim::Trim(std::string name, double min, double max, int steps, std::function<void (double)> notifier_func)
    : TrimBase(name, min, max, steps, notifier_func)
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