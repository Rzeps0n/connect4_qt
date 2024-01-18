#include "GameBoard.h"

GameBoard::GameBoard(QWidget *parent) : QWidget(parent) {}

void GameBoard::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QColor backgroundColor = QColor(GameConfig::backgroundColor);
    QColor tokenBackgroundColor = QColor(GameConfig::tokenBackgroundColor);
    QColor lineColor =
            QColor(GameConfig::buttonTextColor); // Color for the vertical lines

    painter.setPen(backgroundColor);

    int diameter = calculateDiameter();
    int cellWidth = width() / GameConfig::numColumns;

    for (int row = 0; row < GameConfig::numRows; ++row) {
        for (int col = 0; col < GameConfig::numColumns; ++col) {
            QPoint center = calculateCenter(col, row);
            painter.setBrush(tokenBackgroundColor);
            painter.drawEllipse(center, diameter / 2, diameter / 2);
        }
    }
    QPen linePen(lineColor);
    linePen.setWidth(3); // Set the line width as needed
    painter.setPen(linePen);

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
    int columnWidth = width() / GameConfig::numColumns;
    int rowHeight = height() / GameConfig::numRows;
    int diameter = qMin(columnWidth, rowHeight) - (columnWidth / 5);
    return diameter;
}

QPoint GameBoard::calculateCenter(int column, int row) const {
    int columnWidth = width() / GameConfig::numColumns;
    int rowHeight = height() / GameConfig::numRows;
    int centerX = column * columnWidth + columnWidth / 2;
    int centerY = row * rowHeight + rowHeight / 2;
    return QPoint(centerX, centerY);
}