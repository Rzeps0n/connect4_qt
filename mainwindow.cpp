#include "mainwindow.h"
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QAbstractAnimation>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), currentPlayer(1)
{
    resize(800, 600);
    gameBoard = new GameBoard(this);
    setCentralWidget(gameBoard);

    gridLayout = new QGridLayout(gameBoard);
    setupBoard();
    connect(gameBoard, &GameBoard::columnClicked, this, &MainWindow::handleColumnClicked);
    setWindowTitle("Connect 4");
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupBoard() {
    int numColumns = 7;
    int numRows = 6;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numColumns; ++col) {
            buttons[row][col] = new QPushButton(this);

            buttons[row][col]->setStyleSheet("QPushButton { background-color: lightgray; }");

            connect(buttons[row][col], &QPushButton::clicked, this, [this, col] { handleColumnClicked(col); });

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

void MainWindow::handleColumnClicked(int column) {
    int row = findEmptyRow(column);
    if (row < 0) return;

    int squareSize = qMin(gameBoard->width() / 7, gameBoard->height() / 6);

    QLabel *token = new QLabel(this);
    QString color = (currentPlayer == 1) ? "red" : "yellow";
    token->setStyleSheet(QString("QLabel { background-color: %1; }").arg(color));
    token->setFixedSize(squareSize, squareSize);

    int startX = column * squareSize;
    int startY = 0;
    int endY = row * squareSize;

    token->move(startX, startY);
    token->show();

    QPropertyAnimation *animation = new QPropertyAnimation(token, "geometry");
    animation->setDuration(500);
    animation->setStartValue(token->geometry());
    animation->setEndValue(QRect(startX, endY, token->width(), token->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    if (checkForWin(row, column)) {
        qDebug() << "Player " << currentPlayer << " wins!";
    }

    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}
int MainWindow::findEmptyRow(int column) {
    for (int row = 5; row >= 0; --row) {
        if (buttons[row][column]->text() == "") {
            return row;
        }
    }
    return -1; // Indicate that the column is full
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