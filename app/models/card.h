#ifndef CARD_H
#define CARD_H

#include <QObject>

#include "color.h"
#include "value.h"

/**
 * @brief The Card class represents a card of the game
 */

class Card
{
    Q_OBJECT

public:
    Card();

private:
    Color   myColor;
    Value   myValue;
    int     myPoint;
    bool    myIsPlayable;

};

#endif // CARD_H
