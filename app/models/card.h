#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QPixmap>

#include "color.h"
#include "value.h"

/**
 * @brief The Card class represents a card of the game
 */

class Card : public QObject
{
    Q_OBJECT

public:
    explicit Card();
    explicit Card(Color c, Value v, int p, QObject *parent = nullptr);

    QPixmap mPicture0;
    QPixmap image() const;

    QString print();


    Color color() const;
    void setColor(Color newColor);

    Value value() const;
    void setValue(Value newValue);

    int point() const;
    void setPoint(int newPoint);

    bool isPlayable() const;
    void setIsPlayable(bool newIsPlayable);

    void setColorBackground(ColorBackground newColorBackground);

private:
    Color   mColor;
    Value   mValue;
    int     mPoint;
    bool    mIsPlayable;
    ColorBackground mColorBackground;
    QString mImage;

};

#endif // CARD_H
