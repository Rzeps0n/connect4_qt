#include "gameboard.h"
#include <QMouseEvent>
#include "GameConfig.h"

GameBoard::GameBoard(QWidget *parent) : QWidget(parent) {
}

QPoint GameBoard::calculatePosition(int column, int row) {
    int width = this->width() / GameConfig::numColumns;
    int height = this->height() / GameConfig::numRows;
    int x = column * width;
    int y = row * height;
    return QPoint(x, y);
}

int GameBoard::calculateSquareSize() {
    return qMin(this->width() / GameConfig::numColumns, this->height() / GameConfig::numRows);
}

void GameBoard::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::lightGray);

    int columnWidth = this->width() / GameConfig::numColumns;
    int rowHeight = this->height() / GameConfig::numRows;

   /* for (int row = 0; row < GameConfig::numRows; ++row) {
        for (int col = 0; col < GameConfig::numColumns; ++col) {
            int x = col * columnWidth;
            int y = row * rowHeight;
            painter.drawRect(x, y, columnWidth, rowHeight);  // Draw a rectangle with the top-left corner at (x, y)
        }
    }*/

    for (int col = 1; col < GameConfig::numColumns; col++) {
        int x = col * columnWidth;
        painter.drawLine(x, 0, x, this->height());
    }
}

void GameBoard::mousePressEvent(QMouseEvent *event) {
    int columnWidth = width() / GameConfig::numColumns;
    int clickedColumn = event->x() / columnWidth;
    emit columnClicked(clickedColumn);
}