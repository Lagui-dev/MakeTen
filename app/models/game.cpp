#include "game.h"

Game::Game(QObject *parent) : QObject(parent)
{
    mDeck = new Deck(true);
    mPlayerOne = new Player("Robert");
    mStacks = QVector<Card *>(9,nullptr);

    for (int c = 0; c < mStacks.size(); c++) {
        mStacks.replace(c, mDeck->drawBack());
    }
    mNumberOfCardSelected = 0;
    mSumOfCard = 0;
    mLastSackIdx = -1;
    mCounter = 0;

    connect(&mChrono, &QTimer::timeout, this, &Game::chronoAdd1sec);
    mChronoHMS = QTime(0,0,0,0);
    mChrono.setInterval(1000);

}

Card *Game::getCard(const int stackIdx)
{
    return mStacks.at(stackIdx);
}


/**
 * @brief Checks the rules of the game
 * @param stackIdx
 * @return GameState
 */
GameState Game::check(const int stackIdx)
{
   if (!mChrono.isActive()) {
       mChrono.start();
   }

   // card played is the same
   if (mLastSackIdx == stackIdx) {
       mSumOfCard = 0;
       mNumberOfCardSelected = 0;
       mLastSackIdx = -1;
       return GameState::CANCEL;
   }

    // backgrounded card
    if (!isPlayable(stackIdx)) {
        return GameState::NOTHING;
    }

    auto sumOfCardBefore = mSumOfCard;
    mSumOfCard += mStacks.at(stackIdx)->point();
    mNumberOfCardSelected++;
    mLastSackIdx = stackIdx;

    switch (mNumberOfCardSelected) {
    case 1:
        if (mStacks.at(stackIdx)->value() == Value::TEN) {
            mSumOfCard = 0;
            mNumberOfCardSelected = 0;
            mLastSackIdx = -1;
            return GameState::WINNING1CARD;
        }
        return GameState::WAITING;
        break;
    case 2:
        switch (mSumOfCard) {
        case 10:
            mSumOfCard = 0;
            mNumberOfCardSelected = 0;
            mLastSackIdx = -1;
            return GameState::WINNING2CARDS;
            break;
        case 23 ... 25:
            /**
             * Jack, Queen and King
             *
             * SumBefore = 12 && CurrentCard = 12 Then 2 Queens => Cancel
             */
            if (((sumOfCardBefore == 12) && (mStacks.at(stackIdx)->point() == 12))
                    || mStacks.at(stackIdx)->value() == 10) {
                mSumOfCard = 0;
                mNumberOfCardSelected = 0;
                mLastSackIdx = -1;
                return GameState::CANCEL;
            } else {
                return GameState::WAITING;
            }
            break;
        default:
            mSumOfCard = 0;
            mNumberOfCardSelected = 0;
            mLastSackIdx = -1;
            return GameState::CANCEL;
            break;
        }
        break;
    case 3:
        // Jack, Queen and King
        if (mSumOfCard == 36) {
            mSumOfCard = 0;
            mNumberOfCardSelected = 0;
            mLastSackIdx = -1;
            return GameState::WINNING3CARDS;
        } else {
            mSumOfCard = 0;
            mNumberOfCardSelected = 0;
            mLastSackIdx = -1;
            return GameState::CANCEL;
        }
        break;
    default:
        return GameState::WAITING;
        break;
    }
    return GameState::CANCEL;
}

bool Game::draw(const int stackIdx)
{
    mStacks.replace(stackIdx, mDeck->draw());
    if (mStacks.at(stackIdx) == nullptr) {
        return false;
    } else {
        return true;
    }
}

bool Game::isPlayable(const int stackIdx)
{
    if (mStacks.at(stackIdx) == nullptr) {
        return false;
    } else {
        return mStacks.at(stackIdx)->isPlayable();
    }
}

int Game::size()
{
    return mDeck->size();
}

bool Game::areYouWin()
{
    bool win = true;
    QVector<Card *>::iterator it;
    for (it = mStacks.begin(); it != mStacks.end(); ++it) {
        if (((*it) != nullptr) && (*it)->value() < Value::VALUE_END) {
            win = false;
        }
    }
    if (win) {
        mChrono.stop();
    }
    return win;
}

void Game::reStart()
{
    delete mDeck;
    delete mPlayerOne;
    mDeck = new Deck(true);
    mPlayerOne = new Player("Robert");
    mStacks = QVector<Card *>(9,nullptr);

    for (int c = 0; c < mStacks.size(); c++) {
        mStacks.replace(c, mDeck->drawBack());
    }
    mNumberOfCardSelected = 0;
    mSumOfCard = 0;
    mChrono.stop();
    mChronoHMS = QTime(0,0,0,0);
    mCounter++;
}

int Game::counter() const
{
    return mCounter;
}

void Game::chronoAdd1sec()
{
    mChronoHMS = mChronoHMS.addSecs(1);
    emit chronoUpdated(mChronoHMS.toString("hh:mm:ss"));
}


GameStatusClass::GameStatusClass()
{

}
