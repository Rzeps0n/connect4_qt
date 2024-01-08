#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QResizeEvent>
#include "gameboard.h"

class MainWindow : public QMainWindow
{
Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleColumnClicked(int column);
    //void showMainMenu();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    GameBoard *gameBoard;
    QGridLayout *gridLayout;
    QPushButton *buttons[6][7];
    int currentPlayer;
    int findEmptyRow(int column);

    void setupBoard();
    bool checkForWin(int row, int col);
    bool checkDirection(int row, int col, int xDir, int yDir);
    //void showWinMessage(int player);
};

#endif // MAINWINDOW_H