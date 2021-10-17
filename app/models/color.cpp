#include "color.h"


Color &operator++(Color &c)
{
    if (c == COLOR_END) {
        throw "Cannot use ++ operator for COLOR_MAX value";
    }
    c = static_cast<Color>(c + 1);
    return c;
}

Color operator++(Color &c, int)
{
    return static_cast<Color>(++c);
}

Color &operator--(Color &c)
{
    if (c == COLOR_BEGIN) {
        throw "Cannot use -- operator for COLOR_BEGIN value";
    }
    c = static_cast<Color>(c - 1);
    return c;
}

Color operator--(Color &c, int)
{
    return static_cast<Color>(--c);
}

