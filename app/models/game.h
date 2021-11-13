#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTimer>
#include <QTime>

#include "models/deck.h"
#include "models/card.h"
#include "models/player.h"
#include "models/table.h"

class GameStatusClass
{
    Q_GADGET
public:
    enum Status {
        WAITING,
        CANCEL,
        WINNING1CARD,
        WINNING2CARDS,
        WINNING3CARDS,
        NOTHING
    };
    Q_ENUM(Status);
private:
    explicit GameStatusClass();
};

typedef GameStatusClass::Status GameState;



class Game : public QObject
{
    Q_OBJECT

public:

    Game(QObject *parent = nullptr);
    Q_INVOKABLE Card *getCard(const int stackIdx);
    Q_INVOKABLE GameState check(const int stackIdx);
    Q_INVOKABLE bool draw(const int stackIdx);
    Q_INVOKABLE bool isPlayable(const int stackIdx);
    Q_INVOKABLE int size();
    Q_INVOKABLE bool areYouWin();
    Q_INVOKABLE void reStart();


    Q_INVOKABLE int counter() const;

private:
    Table  *mTableOne;
    Deck   *mDeck;
    Player *mPlayerOne;
    QVector<Card *> mStacks; // The nine cards on the table
    int    mLastSackIdx;
    int    mSumOfCard;
    int    mNumberOfCardSelected;
    int    mCounter;

    QTimer mChrono;
    QTime  mChronoHMS;

private slots:
    void   chronoAdd1sec();

signals:
    void   chronoUpdated(QString chronoHMS);
};

#endif // GAME_H
