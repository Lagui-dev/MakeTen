#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QDebug>

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
    Card *getCard(int stackIdx);
    State check(int stackIdx);
    void draw(int stackIdx);
    bool isPlayable(int stackIdx);
    int size();

private:
    Table  *mTableOne;
    Deck   *mDeck;
    Player *mplayerOne;
    QVector<Card *> mStacks;
    int    mSumOfCard;
    int    mNumberOfCardSelected;



};

#endif // GAME_H
