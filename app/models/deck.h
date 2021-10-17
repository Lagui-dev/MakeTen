#ifndef DECK_H
#define DECK_H

#include <QObject>
#include <QRandomGenerator>
#include <QDebug>

#include "card.h"

#define INIT_SHUFFLE 1000

/**
 * @brief The Deck class represent a deck with cards
 */

class Deck : public QObject
{
    Q_OBJECT

public:
    explicit Deck(bool init, QObject *parent = nullptr);
    int size();
    void print();
    void shuffle(int times);

    Card *draw();
    Card *drawBack();
    void insert(Card *card);

private:
    int mRandInt(int begin, int end);
    QList<Card *> mCards;
    Card *mBackground;
};

#endif // DECK_H
