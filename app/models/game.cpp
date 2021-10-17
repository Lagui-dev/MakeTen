#include "game.h"

Game::Game(QObject *parent) : QObject(parent)
{
    mDeck = new Deck(true);
    mTableOne = new Table();
    mplayerOne = new Player("Robert");
    mStacks = QVector<Card *>(9,nullptr);

    for (int c = 0; c < mStacks.size(); c++) {
        mStacks.replace(c, mDeck->drawBack());
    }
    mNumberOfCardSelected = 0;
    mSumOfCard = 0;
}

Card *Game::getCard(int stackIdx)
{
    return mStacks.at(stackIdx - 1);
}


State Game::check(int stackIdx)
{
    // backgrounded card
    if (!isPlayable(stackIdx)) {
        return State::NOTHING;
    }

    auto sumOfCardBefore = mSumOfCard;
    mSumOfCard += mStacks.at(stackIdx - 1)->point();
    mNumberOfCardSelected++;
    qDebug() << mSumOfCard << mNumberOfCardSelected;

    switch (mNumberOfCardSelected) {
    case 1:
        if (mStacks.at(stackIdx - 1)->value() == Value::TEN) {
            mSumOfCard = 0;
            mNumberOfCardSelected = 0;
            return State::WINNING1CARD;
        }
        return State::WAITING;
        break;
    case 2:
        switch (mSumOfCard) {
        case 10:
            mSumOfCard = 0;
            mNumberOfCardSelected = 0;
            return State::WINNING2ARDS;
            break;
        case 23 ... 25:
            /**
             * Jack, Queen and King
             *
             * SumBefore = 12 && CurrentCard = 12 Then 2 Queens => Cancel
             */
            if ((sumOfCardBefore == 12) && (mStacks.at(stackIdx - 1)->point()==12)) {
                mSumOfCard = 0;
                mNumberOfCardSelected = 0;
                return State::CANCEL;
            } else {
                return State::WAITING;
            }
            break;
        default:
            mSumOfCard = 0;
            mNumberOfCardSelected = 0;
            return State::CANCEL;
            break;
        }
        break;
    case 3:
        if (mSumOfCard == 36) {
            mSumOfCard = 0;
            mNumberOfCardSelected = 0;
            return State::WINNING3CARDS;
        } else {
            mSumOfCard = 0;
            mNumberOfCardSelected = 0;
            return State::CANCEL;
        }
        break;
    default:
        return State::WAITING;
        break;
    }
    qDebug() << "Here ?";
    return State::CANCEL;
}

void Game::draw(int stackIdx)
{
    mStacks.replace(stackIdx - 1, mDeck->draw());
}

bool Game::isPlayable(int stackIdx)
{
    return mStacks.at(stackIdx - 1)->isPlayable();
}

int Game::size()
{
    return mDeck->size();
}
