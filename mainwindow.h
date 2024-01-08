#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QLabel"
#include <QApplication>
#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QAbstractAnimation>
#include "gameboard.h"
#include "GameConfig.h"

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void handleColumnClicked(int column);

protected:
    //void resizeEvent(QResizeEvent *event) override;

private:

    GameBoard* gameBoard;
    QPushButton* buttons[GameConfig::numRows][GameConfig::numColumns];
    QLabel* labels[GameConfig::numRows][GameConfig::numColumns];  // 2D array of pointers to QLabel tokens
    void updateTokenPositions();  // Function to update the position and size of tokens
    int currentPlayer;
    int findEmptyRow(int column);
    bool checkForWin(int row, int col);
    bool checkDirection(int row, int col, int xDir, int yDir);
};

#endif // MAINWINDOW_H