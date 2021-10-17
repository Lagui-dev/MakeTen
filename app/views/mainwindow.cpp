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
    int stackIdx = 1;
    QList<QPushButton *>::iterator it;
    for (it = mStackedCards.begin(); it != mStackedCards.end(); ++it) {
        (*it)->setIcon(mGame->getCard(stackIdx)->mPicture);
        connect((*it), &QPushButton::clicked, this, [=]() {this->cardSelected(stackIdx); });
        stackIdx++;
    }

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

void MainWindow::cardSelected(int stackIdx)
{
    if (stackIdx > 1) {
        if (!mGame->isPlayable(stackIdx - 1)) {
            return;
        }
    }
    QList<QPushButton *>::iterator it;
    int stackIdx2 = 1;
    switch (mGame->check(stackIdx)) {
    case State::NOTHING:
        mGame->draw(stackIdx);
        mStackedCards.at(stackIdx-1)->setEnabled(true);
        mStackedCards.at(stackIdx-1)->setIcon(mGame->getCard(stackIdx)->mPicture);
        return;
        break;
    case State::WAITING:
        mStackedCards.at(stackIdx-1)->setEnabled(false);
        break;
    case State::CANCEL:
        for (it = mStackedCards.begin(); it != mStackedCards.end(); ++it) {
            (*it)->setEnabled(true);
        }
        break;
    case State::WINNING1CARD:
        mGame->draw(stackIdx);
        mStackedCards.at(stackIdx-1)->setEnabled(true);
        mStackedCards.at(stackIdx-1)->setIcon(mGame->getCard(stackIdx)->mPicture);
        return;
        break;
    case State::WINNING2ARDS:
        for (it = mStackedCards.begin(); it != mStackedCards.end(); ++it) {
            if (!(*it)->isEnabled()) {
                (*it)->setEnabled(true);
                mGame->draw(stackIdx2);
                mStackedCards.at(stackIdx2-1)->setIcon(mGame->getCard(stackIdx2)->mPicture);
            }
            stackIdx2++;
        }
        mGame->draw(stackIdx);
        mStackedCards.at(stackIdx-1)->setEnabled(true);
        mStackedCards.at(stackIdx-1)->setIcon(mGame->getCard(stackIdx)->mPicture);
        break;
    case State::WINNING3CARDS:
        for (it = mStackedCards.begin(); it != mStackedCards.end(); ++it) {
            if (!(*it)->isEnabled()) {
                (*it)->setEnabled(true);
                mGame->draw(stackIdx2);
                mStackedCards.at(stackIdx2-1)->setIcon(mGame->getCard(stackIdx2)->mPicture);
            }
            stackIdx2++;
        }
        mGame->draw(stackIdx);
        mStackedCards.at(stackIdx-1)->setEnabled(true);
        mStackedCards.at(stackIdx-1)->setIcon(mGame->getCard(stackIdx)->mPicture);
        break;
    }
    mStackedCards.at(stackIdx-1)->setIcon(mGame->getCard(stackIdx)->mPicture);
    ui->lblNumberOfCards->setText(QString::number(mGame->size()));
}


void MainWindow::on_actionPlay_triggered()
{
    delete mGame;
    mGame = new Game();
    int stackIdx = 1;
    QList<QPushButton *>::iterator it;
    for (it = mStackedCards.begin(); it != mStackedCards.end(); ++it) {
        (*it)->setIcon(mGame->getCard(stackIdx)->mPicture);
        (*it)->setVisible(true);
        (*it)->setEnabled(true);
        stackIdx++;
    }
}


void MainWindow::on_actionHelp_triggered()
{
    auto Help = new about();
    Help->exec();
}

