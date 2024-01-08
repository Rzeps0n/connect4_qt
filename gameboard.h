#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "GameConfig.h"

class GameBoard : public QWidget {
Q_OBJECT

public:
    int calculateDiameter() const;
    QPoint calculateCenter(int column, int row) const;
    explicit GameBoard(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void columnClicked(int column);
};

#endif // GAMEBOARD_H