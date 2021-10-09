#include "views/mainwindow.h"
#include <QApplication>

#include "maketenglobal.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MakeTenGlobal *myMakeTenGlobal;
    myMakeTenGlobal = MakeTenGlobal::getInstance();
    myMakeTenGlobal->demo();
    MainWindow w;

    return a.exec();
}
