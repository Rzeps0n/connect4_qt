//
// mainwindow.cpp
#include "mainwindow.h"
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QAbstractAnimation>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), currentPlayer(1)
{
    gridLayout = new QGridLayout;
    setupBoard();

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("Connect 4");
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupBoard()
{
    for (int row = 0; row < 6; ++row)
    {
        for (int col = 0; col < 7; ++col)
        {
            buttons[row][col] = new QPushButton(this);

            buttons[row][col]->setStyleSheet("QPushButton { border-radius: 30px; background-color: lightgray; }");

            buttons[row][col]->setFixedSize(60, 60);

            connect(buttons[row][col], &QPushButton::clicked, this, &MainWindow::handleButtonClicked);
            gridLayout->addWidget(buttons[row][col], row, col);
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    int buttonSize = qMin(width() / 10, height() / 8);
    for (int row = 0; row < 6; ++row)
    {
        for (int col = 0; col < 7; ++col)
        {
            buttons[row][col]->setFixedSize(buttonSize, buttonSize);
        }
    }
}

void MainWindow::handleButtonClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());

    for (int col = 0; col < 7; ++col)
    {
        if (buttons[0][col] == clickedButton)
        {
            qDebug() << "Clicked col:" << col << "by Player:" << currentPlayer;
            int row = 5;
            while (row >= 0 && buttons[row][col]->text() != "")
            {
                --row;
            }

            if (row < 0)
                return;

            QString color = (currentPlayer == 1) ? "red" : "yellow";
            buttons[row][col]->setStyleSheet(QString("QPushButton { border-radius: 30px; background-color: %1; }").arg(color));

            // Set button text to mark the player
            buttons[row][col]->setText(QString::number(currentPlayer));

            // Animate falling token
            QPropertyAnimation *animation = new QPropertyAnimation(buttons[row][col], "geometry");
            animation->setDuration(500);
            animation->setStartValue(QRect(buttons[row][col]->geometry().topLeft(), buttons[row][col]->size()));
            animation->setEndValue(QRect(buttons[row][col]->geometry().topLeft() + QPoint(0, 60 * (5 - row)), buttons[row][col]->size()));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start(QAbstractAnimation::DeleteWhenStopped);

            if (checkForWin(row, col))
            {
                qDebug() << "Player " << currentPlayer << " wins!";
            }

            currentPlayer = (currentPlayer == 1) ? 2 : 1;
            return;
        }
    }
}


bool MainWindow::checkForWin(int row, int col)
{
    // Check horizontally
    if (checkDirection(row, col, 0, 1) || checkDirection(row, col, 0, -1))
        return true;

    // Check vertically
    if (checkDirection(row, col, 1, 0))
        return true;

    // Check diagonally
    if (checkDirection(row, col, 1, 1) || checkDirection(row, col, -1, -1) ||
        checkDirection(row, col, -1, 1) || checkDirection(row, col, 1, -1))
        return true;

    return false;
}

bool MainWindow::checkDirection(int row, int col, int xDir, int yDir)
{
    int count = 1;
    int r, c;

    for (int i = 1; i < 4; ++i)
    {
        r = row + i * xDir;
        c = col + i * yDir;

        if (r >= 0 && r < 6 && c >= 0 && c < 7 && buttons[r][c]->text() == QString::number(currentPlayer))
            count++;
        else
            break;
    }

    for (int i = 1; i < 4; ++i)
    {
        r = row - i * xDir;
        c = col - i * yDir;

        if (r >= 0 && r < 6 && c >= 0 && c < 7 && buttons[r][c]->text() == QString::number(currentPlayer))
            count++;
        else
            break;
    }

    return count >= 4;
}