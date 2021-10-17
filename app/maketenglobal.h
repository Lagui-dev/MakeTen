#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QDebug>


class MakeTenGlobal : QObject
{
    Q_OBJECT
public:

    static MakeTenGlobal *getInstance();
    bool removeInstance();

private:

    explicit MakeTenGlobal();
    ~MakeTenGlobal();
    MakeTenGlobal& operator=(const MakeTenGlobal&) = delete;

    static MakeTenGlobal *currentInstance;

signals:

public slots:

};



#endif // CONFIG_H
