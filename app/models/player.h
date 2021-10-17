#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QDebug>

#include "models/card.h"

class Player : public QObject
{
    Q_OBJECT

public:
    Player(QObject *parent = nullptr);
    Player(QString name, QObject *parent = nullptr);

    const QString &name() const;
    void setName(const QString &newName);
    int totalPoints() const;
    void addCard(Card *card);

private:
    QString mName;
    QList<Card *> mCards;
};

#endif // PLAYER_H
