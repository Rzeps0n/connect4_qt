#include "mainwindow.h"
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QAbstractAnimation>
#include <QLabel>
#include "GameConfig.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), currentPlayer(1)
{
    resize(800, 600);
    gameBoard = new GameBoard(this);
    setCentralWidget(gameBoard);

    gridLayout = new QGridLayout(gameBoard);
    connect(gameBoard, &GameBoard::columnClicked, this, &MainWindow::handleColumnClicked);
    setWindowTitle("Connect 4");

    for (int row = 0; row < GameConfig::numRows; ++row) {
        for (int col = 0; col < GameConfig::numColumns; ++col) {
            labels[row][col] = nullptr;
        }
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleColumnClicked(int column) {
    int row = findEmptyRow(column);
    if (row < 0) {
        qDebug() << "Column" << column << "is full!";
        return;
    }

    QLabel *token = new QLabel(gameBoard);
    QString color = (currentPlayer == 1) ? "red" : "yellow";
    token->setStyleSheet(QString("QLabel { background-color: %1; }").arg(color));

    int squareSize = gameBoard->calculateSquareSize();
    token->setFixedSize(squareSize, squareSize);

    int columnWidth = gameBoard->width() / GameConfig::numColumns;
    int xCenterOfColumn = column * columnWidth + columnWidth / 2 - squareSize / 2;

    QPoint startPos = QPoint(xCenterOfColumn, 0);
    token->move(startPos);
    token->show();

    // Animate the token falling
    QPropertyAnimation *animation = new QPropertyAnimation(token, "geometry");
    animation->setDuration(500);
    QPoint endPos = gameBoard->calculatePosition(column, row);
    endPos.setX(xCenterOfColumn); // Adjust the x position to be centered
    animation->setStartValue(QRect(startPos, token->size()));
    animation->setEndValue(QRect(endPos, token->size()));
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start(QAbstractAnimation::DeleteWhenStopped);

    labels[row][column] = token;

    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

int MainWindow::findEmptyRow(int column) {
    if (column < 0 || column >= GameConfig::numColumns) {
        qDebug() << "Column index out of bounds:" << column;
        return -1;
    }

    for (int row = GameConfig::numRows - 1; row >= 0; --row) {
        if (labels[row][column] == nullptr || labels[row][column]->text().isEmpty()) {
            return row;
        }
    }

    return -1; // Column is full
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

        if (r >= 0 && r < GameConfig::numRows&& c >= 0 && c < GameConfig::numColumns&& buttons[r][c]->text() == QString::number(currentPlayer))
            count++;
        else
            break;
    }

    for (int i = 1; i < 4; ++i)
    {
        r = row - i * xDir;
        c = col - i * yDir;

        if (r >= 0 && r < GameConfig::numRows&& c >= 0 && c < GameConfig::numColumns&& buttons[r][c]->text() == QString::number(currentPlayer))
            count++;
        else
            break;
    }

    return count >= 4;
}