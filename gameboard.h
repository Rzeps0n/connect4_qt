#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QPainter>

class GameBoard : public QWidget {
Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void columnClicked(int column);

public slots:
    QPoint calculatePosition(int column, int row);
    int calculateSquareSize();

};

#endif // GAMEBOARD_H