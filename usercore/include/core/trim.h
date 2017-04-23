#ifndef TRIM_H
#define TRIM_H

#include <string>
#include "bases/export_handling.h"
#include "bases/trim_dev_base.h"

class ROVIZ_EXPORT_CLASS Trim : public TrimBase
{
public:
    Trim() = default;
    Trim(std::string name, double min, double max, int steps = 0, bool num_of_steps = true);
    ~Trim() = default;

    // Don't allow copies
    Trim(const Trim &trim) = delete;
    Trim &operator=(const Trim &config) = delete;

    // Allow moving
    Trim(Trim &&trim);
    Trim &operator=(Trim &&trim);

    double value(void) const override;
};

#endif // TRIM_H
