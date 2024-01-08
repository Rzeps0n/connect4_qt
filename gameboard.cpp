#include "gameboard.h"
#include <QMouseEvent>

GameBoard::GameBoard(QWidget *parent) : QWidget(parent) {
}

void GameBoard::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::black);

    int numColumns = 7;
    int columnWidth = width() / numColumns;
    for (int i = 1; i < numColumns; i++) {
        painter.drawLine(i * columnWidth, 0, i * columnWidth, height());
    }
}


void GameBoard::mousePressEvent(QMouseEvent *event) {
    int numColumns = 7;
    int columnWidth = width() / numColumns;
    int clickedColumn = event->x() / columnWidth;
    emit columnClicked(clickedColumn);
}