#ifndef TRIM_DEV_BASE_P_H
#define TRIM_DEV_BASE_P_H

class QLayout;
class QSlider;

class TrimDevBasePrivate
{
public:
    double val;
    QLayout *main_layout;
    QSlider *main_slider;
};

#endif // TRIM_DEV_BASE_P_H
