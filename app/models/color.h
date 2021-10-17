#ifndef COLOR_H
#define COLOR_H

/**
 * @brief The Color enum represent the color of a card
 */

enum Color
{
    COLOR_BEGIN,
    BLACK_CLUBS = COLOR_BEGIN,  // 0
    BLACK_SPADE,                // 1
    RED_HEART,                  // 2
    RED_DIAMOND,                // 3
    COLOR_END
};

enum ColorBackground
{
    BLUE,
    GRAY,
    GREEN,
    PURPLE,
    YELLOW,
    RED
};

Color &operator++(Color &c);
Color  operator++(Color &c, int);

Color &operator--(Color &c);
Color  operator--(Color &c, int);

#endif // COLOR_H
