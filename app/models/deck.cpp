#include "deck.h"

Deck::Deck(bool init, QObject *parent) : QObject(parent)
{
    if (init) {
    // create the deck
        for (Value v=Value::ONE; v<Value::VALUE_END; v++) {
             for (Color c=COLOR_BEGIN; c<COLOR_END; c++) {
//                 if (v <= Value::TEN) {
                     mCards.prepend(new Card(c, v, v, this));
//                 } else {
//                     mCards.prepend(new Card(c, v, 50, this));
//                 }
             }
        }

        mBackground = new Card();
        //mBackground->setColorBackground(ColorBackground::GREEN);
        shuffle(INIT_SHUFFLE);

    }
}

int Deck::size()
{
    return mCards.size();
}

void Deck::print()
{
    QList<Card *>::iterator it;
    for (it = mCards.begin(); it != mCards.end(); ++it) {
        qDebug() << (*it)->print();
    }
}


void Deck::shuffle(int times)
{
    if (!mCards.empty()) {
        for (int i=0; i< times; i++) {
            mCards.move(mRandInt(0, mCards.size()), mCards.size() - 1);
        }
    }
}

Card *Deck::draw()
{
    Card *card = nullptr;
    if (!mCards.empty()) {
        card = mCards.first();
        mCards.removeFirst();
    }
    return card;
}

Card *Deck::drawBack()
{
    return mBackground;
}

void Deck::insert(Card *card)
{
    mCards.append(card);
}

int Deck::mRandInt(int begin, int end)
{
    if (begin > end) {
        throw "Error when calling randInt()";
    }
    return (QRandomGenerator::system()->generate() % (end - begin)) + begin;
}
