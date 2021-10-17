#include "value.h"

Value &operator++(Value &v)
{
    if (v == VALUE_END) {
        throw "Cannot use ++ operator for VALUE_MAX value";
    }

    v = static_cast<Value>(v + 1);

    return v;
}

Value operator++(Value &v, int)
{
    return static_cast<Value>(++v);
}

Value &operator--(Value &v)
{
    if (v == VALUE_BEGIN) {
        throw "Cannot use -- operator for VALUE_BEGIN value";
    }

    v = static_cast<Value>(v - 1);

    return v;
}

Value operator--(Value &v, int)
{
    return static_cast<Value>(--v);
}
