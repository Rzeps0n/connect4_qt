#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QResizeEvent>
#include "gameboard.h"
#include "GameConfig.h"
#include "QLabel"

class MainWindow : public QMainWindow
{
Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleColumnClicked(int column);

protected:
    //void resizeEvent(QResizeEvent *event);

private:
    QLabel* labels[GameConfig::numRows][GameConfig::numColumns];
    GameBoard *gameBoard;
    QGridLayout *gridLayout;
    QPushButton *buttons[GameConfig::numRows][GameConfig::numColumns];
    int currentPlayer;
    int findEmptyRow(int column);
    bool checkForWin(int row, int col);
    bool checkDirection(int row, int col, int xDir, int yDir);
};

#endif // MAINWINDOW_H