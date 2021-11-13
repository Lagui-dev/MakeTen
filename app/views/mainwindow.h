#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QTime>
#include <QPropertyAnimation>


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

    void cardSelected(const int currentStackIdx);
    void chronoUpate();
    void animateWin();

    void on_actionPlay_triggered();
    void on_actionHelp_triggered();
    void on_actionQuit_triggered();
    void on_actionPFM_triggered();
    void on_btnActivePFM_clicked();

private:
    Ui::MainWindow *ui;
    Game *mGame;
    QList<QPushButton *> mStackedCards;
    QTimer mChrono;
    QTime  mChronoHMS;

    bool playForMe();
    QPropertyAnimation *animation;



};
#endif // MAINWINDOW_H
