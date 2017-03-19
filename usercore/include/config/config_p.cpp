
#include "config/config_p.h"

#include "core/template_decl.h"

template<typename T>
ConfigPrivate<T>::ConfigPrivate()
    : impl(this)
{
}

INSTANTIATE_CONFIG_PRIVATE
