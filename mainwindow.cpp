#include "mainwindow.h"

#include <QPropertyAnimation>

#include <QEasingCurve>

#include <QAbstractAnimation>

#include <QLabel>

#include "GameConfig.h"

MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent)
        , currentPlayer(1)
{
    resize(800, 600);
    gameBoard = new GameBoard(this);
    setCentralWidget(gameBoard);
    connect(gameBoard, &GameBoard::columnClicked, this, &MainWindow::handleColumnClicked);
    setWindowTitle("Connect 4");

    for (int row = 0; row < GameConfig::numRows; ++row) {
        for (int col = 0; col < GameConfig::numColumns; ++col) {
            labels[row][col] = nullptr;
        }
    }
}

MainWindow::~MainWindow() {}

void
MainWindow::handleColumnClicked(int column)
{
    int row = findEmptyRow(column);
    if (row < 0) {
        qDebug() << "Column" << column << "is full!";
        return; // Column is full
    }
    int columnWidth = this->width() / GameConfig::numColumns;
    int rowHeight = gameBoard->height() / GameConfig::numRows;
    int diameter = qMin(columnWidth, rowHeight) - (columnWidth / 5);
    int tokenSpacing = columnWidth / 10;

    QPoint center = gameBoard->calculateCenter(column, row);
    QLabel* token = new QLabel(gameBoard);
    QString color = (currentPlayer == 1) ? "red" : "yellow";
    token->setStyleSheet(QString("QLabel { background-color: %1; }").arg(color));

    int verticalPadding = columnWidth / 5;
    int totalSpacing = (GameConfig::numRows - 1) * tokenSpacing + 2 * verticalPadding;

    token->setFixedSize(diameter, diameter);
    token->setStyleSheet(token->styleSheet() + QString(" QLabel { border-radius: %1px; }").arg(diameter / 2));

    QPoint startPos = center - QPoint(diameter / 2, gameBoard->height());
    QPoint endPos = center - QPoint(diameter / 2, diameter / 2);

    token->move(startPos);
    token->show();

    // Animate the token falling
    QPropertyAnimation* animation = new QPropertyAnimation(token, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(startPos, token->size()));
    animation->setEndValue(QRect(endPos, token->size()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    labels[row][column] = token;

    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

int
MainWindow::findEmptyRow(int column)
{
    for (int row = GameConfig::numRows - 1; row >= 0; --row) {
        if (labels[row][column] == nullptr) {
            return row;
        }
    }
    return -1; // No empty row found, column is full
}

bool
MainWindow::checkForWin(int row, int col)
{
    // Check horizontally
    if (checkDirection(row, col, 0, 1) || checkDirection(row, col, 0, -1))
        return true;

    // Check vertically
    if (checkDirection(row, col, 1, 0))
        return true;

    // Check diagonally
    if (checkDirection(row, col, 1, 1) || checkDirection(row, col, -1, -1) || checkDirection(row, col, -1, 1) || checkDirection(row, col, 1, -1))
        return true;

    return false;
}

bool
MainWindow::checkDirection(int row, int col, int xDir, int yDir)
{
    int count = 1;
    int r, c;

    for (int i = 1; i < 4; ++i) {
        r = row + i * xDir;
        c = col + i * yDir;

        if (r >= 0 && r < GameConfig::numRows && c >= 0 && c < GameConfig::numColumns && buttons[r][c]->text() == QString::number(currentPlayer))
            count++;
        else
            break;
    }

    for (int i = 1; i < 4; ++i) {
        r = row - i * xDir;
        c = col - i * yDir;

        if (r >= 0 && r < GameConfig::numRows && c >= 0 && c < GameConfig::numColumns && buttons[r][c]->text() == QString::number(currentPlayer))
            count++;
        else
            break;
    }

    return count >= 4;
}