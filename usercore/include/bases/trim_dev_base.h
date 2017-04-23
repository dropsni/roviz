#ifndef TRIM_DEV_BASE_H
#define TRIM_DEV_BASE_H

#include <string>
#include <memory>
#include "bases/export_handling.h"
#include "bases/trim_dev_base_p.h"

class QLayout;
class QSlider;

class ROVIZ_EXPORT_CLASS TrimDevBase
{
public:
    TrimDevBase() = default;
    TrimDevBase(std::string name, double min, double max, int steps, bool num_of_steps = true);
    virtual ~TrimDevBase() = default;

    // Don't allow copies
    TrimDevBase(const TrimDevBase &trim) = delete;
    TrimDevBase &operator=(const TrimDevBase &trim) = delete;

    // Allow moving
    TrimDevBase(TrimDevBase &&trim);
    TrimDevBase &operator =(TrimDevBase &&trim);

    QLayout *layout(void) const;
    QSlider *slider(void) const;
    virtual double value(void) const;

private:
    std::unique_ptr<TrimDevBasePrivate> _this;
};

#endif // TRIM_DEV_BASE_H
