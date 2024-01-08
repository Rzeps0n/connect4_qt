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
        return; // Column is full
    }

    QLabel *token = new QLabel(gameBoard);
    QString color = (currentPlayer == 1) ? "red" : "yellow";
    token->setStyleSheet(QString("QLabel { background-color: %1; }").arg(color));

    int columnWidth = gameBoard->width() / GameConfig::numColumns;
    int tokenSpacing = columnWidth/10;
    int totalSpacing = (GameConfig::numRows - 1) * tokenSpacing;
    int availableHeight = gameBoard->height() - totalSpacing;
    int heightPerToken = availableHeight / GameConfig::numRows;
    int xCenterOfColumn = column * columnWidth + columnWidth / 2 - heightPerToken / 2;


    token->setFixedSize(heightPerToken, heightPerToken);

    QPoint startPos = QPoint(xCenterOfColumn, 0); // Start position at the top of the column
    token->move(startPos);
    token->show();

    int yEndPosition = row * (heightPerToken + tokenSpacing);

    // Animate the token falling
    QPropertyAnimation *animation = new QPropertyAnimation(token, "geometry");
    animation->setDuration(500);
    QPoint endPos = QPoint(xCenterOfColumn, yEndPosition);
    animation->setStartValue(QRect(startPos, token->size()));
    animation->setEndValue(QRect(endPos, token->size()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    // Store the token in the labels array
    labels[row][column] = token;

    // Update game logic here
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}



int MainWindow::findEmptyRow(int column) {
    for (int row = GameConfig::numRows - 1; row >= 0; --row) {
        if (labels[row][column] == nullptr) {
            return row;
        }
    }
    return -1; // No empty row found, column is full
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