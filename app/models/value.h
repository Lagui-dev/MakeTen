#ifndef VALUE_H
#define VALUE_H

/**
 * @brief The Value enum represent de value of a card
 */
enum Value
{
    VALUE_BEGIN,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    VALUE_END
};

// Definition of ++ operator for Value
    Value &operator++(Value &v);
    Value  operator++(Value &v, int);

// Definition of -- operator for Value
    Value &operator--(Value &v);
    Value  operator--(Value &v, int);


#endif // VALUE_H
