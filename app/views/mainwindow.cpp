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

    mGame = new Game();
    int stackIdx = 0;
    QList<QPushButton *>::iterator it;
    for (it = mStackedCards.begin(); it != mStackedCards.end(); ++it) {
        (*it)->setIcon(mGame->getCard(stackIdx)->mPicture);
        connect((*it), &QPushButton::clicked, this, [=]() {this->cardSelected(stackIdx); });
        stackIdx++;
    }

    ui->lblNumberOfCards->setText(QString::number(mGame->size()));
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQ_triggered()
{
    qApp->quit();
}

void MainWindow::cardSelected(const int currentStackIdx)
{
//    if (currentStackIdx >= 1) {
//        // check if card before is playable ?
//        if (!mGame->isPlayable(currentStackIdx-1)) {
//            return;
//        }
//    }

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
    ui->lblNumberOfCards->setText(QString::number(mGame->size()));
}


void MainWindow::on_actionPlay_triggered()
{
    delete mGame;
    mGame = new Game();
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

