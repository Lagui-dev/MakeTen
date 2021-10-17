#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include "models/card.h"

class Table : public QObject
{
    Q_OBJECT

public:
    Table(QObject *parent = nullptr);

    void addCard(Card *card);
    Card *getCard();
private:

    QList<Card *> mCardsStack;
};

#endif // TABLE_H
