#include "gameboard.h"
#include <QMouseEvent>
#include "GameConfig.h"

GameBoard::GameBoard(QWidget *parent) : QWidget(parent) {
}

void GameBoard::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::lightGray);

    int diameter = calculateDiameter();
    int cellWidth = width() / GameConfig::numColumns;

    for (int row = 0; row < GameConfig::numRows; ++row) {
        for (int col = 0; col < GameConfig::numColumns; ++col) {
            QPoint center = calculateCenter(col, row);
            painter.drawEllipse(center, diameter / 2, diameter / 2);
        }
    }

    // Draw vertical lines
    for (int col = 1; col < GameConfig::numColumns; col++) {
        int x = col * cellWidth;
        painter.drawLine(x, 0, x, height());
    }
}

void GameBoard::mousePressEvent(QMouseEvent *event) {
    int columnWidth = this->width() / GameConfig::numColumns;
    int clickedColumn = event->position().x() / columnWidth;
    emit columnClicked(clickedColumn);
}

int GameBoard::calculateDiameter() const {
    int cellWidth = width() / GameConfig::numColumns;
    int cellHeight = height() / GameConfig::numRows;
    int padding = cellWidth / 10;
    return qMin(cellWidth, cellHeight) - padding;
}

QPoint GameBoard::calculateCenter(int column, int row) const {
    int cellWidth = width() / GameConfig::numColumns;
    int cellHeight = height() / GameConfig::numRows;
    int centerX = (column * cellWidth) + (cellWidth / 2);
    int centerY = (row * cellHeight) + (cellHeight / 2);
    return QPoint(centerX, centerY);
}