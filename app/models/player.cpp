#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{

}

Player::Player(QString name, QObject *parent) : QObject(parent)
{
    mName = name;
}

const QString &Player::name() const
{
    return mName;
}

void Player::setName(const QString &newName)
{
    mName = newName;
}

int Player::totalPoints() const
{
    int total = 0;
    QList<Card *>::const_iterator it;
    for (it = mCards.begin(); it != mCards.end(); ++it) {
        total += (*it)->point();
        qDebug() << (*it)->print();
    }
    return total;
}

void Player::addCard(Card *card)
{
    mCards.append(card);
}
