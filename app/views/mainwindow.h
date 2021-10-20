#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include <QDebug>

#include "models/game.h"
#include "models/card.h"
#include "views/about.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQ_triggered();
    void cardSelected(const int currentStackIdx);

    void on_actionPlay_triggered();

    void on_actionHelp_triggered();

private:
    Ui::MainWindow *ui;
    Game *mGame;
    QList<QPushButton *> mStackedCards;


};
#endif // MAINWINDOW_H
