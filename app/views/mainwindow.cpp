#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mStackedCards.append(ui->pushButton_1);
    mStackedCards.append(ui->pushButton_2);
    mStackedCards.append(ui->pushButton_3);
    mStackedCards.append(ui->pushButton_4);
    mStackedCards.append(ui->pushButton_5);
    mStackedCards.append(ui->pushButton_6);
    mStackedCards.append(ui->pushButton_7);
    mStackedCards.append(ui->pushButton_8);
    mStackedCards.append(ui->pushButton_9);

    ui->toolBar->actions().at(4)->setVisible(false);
    ui->statusbar->showMessage("Tens Solitaire v0.1.01 - MIT Licence - 2021 - Lagui-dev");
    mGame = new Game();
    int stackIdx = 0;
    QList<QPushButton *>::iterator it;
    for (it = mStackedCards.begin(); it != mStackedCards.end(); ++it) {
        (*it)->setIcon(mGame->getCard(stackIdx)->mPicture);
        connect((*it), &QPushButton::clicked, this, [=]() {this->cardSelected(stackIdx); });
        stackIdx++;
    }
    connect(&mChrono, &QTimer::timeout, this, &MainWindow::chronoUpate);

    mChronoHMS = QTime(0,0,0,0);
    ui->lblChrono->setText(mChronoHMS.toString("hh:mm:ss"));
    ui->lblNumberOfCards->setText(QString::number(mGame->size()));
    mChrono.setInterval(1000);
    mChrono.start();
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cardSelected(const int currentStackIdx)
{
    QList<QPushButton *>::iterator it;
    int stackIdx = 0;
    switch (mGame->check(currentStackIdx)) {
    case State::NOTHING:
        mGame->draw(currentStackIdx);
        mStackedCards.at(currentStackIdx)->setEnabled(true);
        mStackedCards.at(currentStackIdx)->setIcon(mGame->getCard(currentStackIdx)->mPicture);
        break;
    case State::WAITING:
        mStackedCards.at(currentStackIdx)->setEnabled(false);
        break;
    case State::CANCEL:
        for (it = mStackedCards.begin(); it != mStackedCards.end(); ++it) {
            (*it)->setEnabled(true);
        }
        break;
    case State::WINNING1CARD:
        if (mGame->draw(currentStackIdx)) {
            mStackedCards.at(currentStackIdx)->setEnabled(true);
            mStackedCards.at(currentStackIdx)->setIcon(mGame->getCard(currentStackIdx)->mPicture);
            break;
        } else {
            mStackedCards.at(currentStackIdx)->setVisible(false);
        }
        break;
    case State::WINNING2ARDS:
        for (it = mStackedCards.begin(); it != mStackedCards.end(); ++it) {
            if (!(*it)->isEnabled()) {
                (*it)->setEnabled(true);
                if (mGame->draw(stackIdx)) {
                    mStackedCards.at(stackIdx)->setIcon(mGame->getCard(stackIdx)->mPicture);
                } else {
                    mStackedCards.at(stackIdx)->setVisible(false);
                }
                break;
            }
            stackIdx++;
        }
        if (mGame->draw(currentStackIdx)) {
            mStackedCards.at(currentStackIdx)->setEnabled(true);
            mStackedCards.at(currentStackIdx)->setIcon(mGame->getCard(currentStackIdx)->mPicture);
        } else {
            mStackedCards.at(currentStackIdx)->setVisible(false);
        }
        break;
    case State::WINNING3CARDS:
        for (it = mStackedCards.begin(); it != mStackedCards.end(); ++it) {
            if (!(*it)->isEnabled()) {
                (*it)->setEnabled(true);
                if (mGame->draw(stackIdx)) {
                    mStackedCards.at(stackIdx)->setIcon(mGame->getCard(stackIdx)->mPicture);
                } else {
                    mStackedCards.at(stackIdx)->setVisible(false);
                }
            }
            stackIdx++;
        }
        if (mGame->draw(currentStackIdx)) {
            mStackedCards.at(currentStackIdx)->setEnabled(true);
            mStackedCards.at(currentStackIdx)->setIcon(mGame->getCard(currentStackIdx)->mPicture);
        } else {
            mStackedCards.at(currentStackIdx)->setVisible(false);
        }
        break;
    }
    if (mGame->areYouWin()) {
        ui->lblNumberOfCards->setText("YOU WIN!");
        mChrono.stop();
    } else {
        ui->lblNumberOfCards->setText(QString::number(mGame->size()));
    }
}

void MainWindow::chronoUpate()
{
    mChronoHMS = mChronoHMS.addSecs(1);
    ui->lblChrono->setText(mChronoHMS.toString("hh:mm:ss"));
}

void MainWindow::on_actionPlay_triggered()
{
    mChrono.stop();
    delete mGame;
    mGame = new Game();
    mChronoHMS = QTime(0,0,0,0);
    ui->lblChrono->setText(mChronoHMS.toString("hh:mm:ss"));
    mChrono.start();
    int stackIdx = 0;
    QList<QPushButton *>::iterator it;
    for (it = mStackedCards.begin(); it != mStackedCards.end(); ++it) {
        (*it)->setIcon(mGame->getCard(stackIdx)->mPicture);
        (*it)->setVisible(true);
        (*it)->setEnabled(true);
        stackIdx++;
    }
    ui->lblNumberOfCards->setText(QString::number(mGame->size()));
}


void MainWindow::on_actionHelp_triggered()
{
    auto Help = new about();
    Help->exec();
}



void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

bool MainWindow::playForMe()
{
    for (int idx = 0; idx < 9; idx++) {
        cardSelected(idx);
    }

    bool played = true;
    while (played) {
        played = false;

        int stackIdx1 = 0;
        QList<QPushButton *>::iterator it1;
        for (it1 = mStackedCards.begin(); it1 != mStackedCards.end(); ++it1) {
            if ((*it1)->isVisible()) {
                if (mGame->getCard(stackIdx1)->value() == 10) {
                    cardSelected(stackIdx1);
                    played = true;
                    goto exitFor;
                } else {
                    int stackIdx2 = 0;
                    QList<QPushButton *>::iterator it2;
                    for (it2 = mStackedCards.begin(); it2 != mStackedCards.end(); ++it2) {
                        if ((*it2)->isVisible() && (stackIdx1 != stackIdx2)) {
                            switch (mGame->getCard(stackIdx1)->value()+mGame->getCard(stackIdx2)->value()) {
                            case 10:
                                cardSelected(stackIdx1);
                                cardSelected(stackIdx2);
                                played = true;
                                goto exitFor;
                            case 23 ... 25:
                                if ((mGame->getCard(stackIdx1)->value() == 12 && mGame->getCard(stackIdx2)->value() == 12)
                                        || mGame->getCard(stackIdx2)->value() == 10) {
                                    break;
                                }
                                int stackIdx3 = 0;
                                QList<QPushButton *>::iterator it3;
                                for (it3 = mStackedCards.begin(); it3 != mStackedCards.end(); ++it3) {
                                    if ((*it3)->isVisible() && ((stackIdx1 != stackIdx2) && (stackIdx1 != stackIdx3) && (stackIdx2 != stackIdx3))) {
                                        if ((mGame->getCard(stackIdx1)->value()
                                                +mGame->getCard(stackIdx2)->value()
                                                +mGame->getCard(stackIdx3)->value()) == 36) {
                                            cardSelected(stackIdx1);
                                            cardSelected(stackIdx2);
                                            cardSelected(stackIdx3);
                                            played = true;
                                            goto exitFor;
                                        }
                                    }
                                    stackIdx3++;
                                }
                                break;
                            }
                        }
                        stackIdx2++;
                    }
                }
            }
            stackIdx1++;

        }

exitFor:
        if (mGame->areYouWin()) {
            break;
        }
    }

    return true;
}


void MainWindow::on_actionPFM_triggered()
{
    playForMe();
}


void MainWindow::on_btnActivePFM_clicked()
{
    ui->toolBar->actions().at(4)->setVisible(true);
}

