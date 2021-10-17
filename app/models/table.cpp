#include "table.h"

Table::Table(QObject *parent) : QObject(parent)
{

}

void Table::addCard(Card *card)
{
    mCardsStack.append(card);

}

Card *Table::getCard()
{
    Card *card = nullptr;
    if (!mCardsStack.empty()) {
        card = mCardsStack.last();
        mCardsStack.removeLast();
    }
    return card;
}
