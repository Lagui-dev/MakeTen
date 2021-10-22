#ifndef GAME_H
#define GAME_H

#include <QObject>

#include "models/deck.h"
#include "models/card.h"
#include "models/player.h"
#include "models/table.h"

enum State {
    WAITING,
    CANCEL,
    WINNING1CARD,
    WINNING2ARDS,
    WINNING3CARDS,
    NOTHING
};

class Game : public QObject
{
    Q_OBJECT

public:
    Game(QObject *parent = nullptr);
    Card *getCard(const int stackIdx);
    State check(const int stackIdx);
    bool draw(const int stackIdx);
    bool isPlayable(const int stackIdx);
    int size();

private:
    Table  *mTableOne;
    Deck   *mDeck;
    Player *mPlayerOne;
    QVector<Card *> mStacks;
    int    mSumOfCard;
    int    mNumberOfCardSelected;



};

#endif // GAME_H
