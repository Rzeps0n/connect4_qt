#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameConfig.h"
#include "QLabel"
#include "gameboard.h"
#include <QAbstractAnimation>
#include <QApplication>
#include <QEasingCurve>
#include <QGridLayout>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QResizeEvent>
#include "WinDialog.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, std::function<void()> showMenuCallback = nullptr);
    ~MainWindow();

private slots:
    void handleColumnClicked(int column);
    void showWinDialog();

private:
    std::function<void()> showMainMenuCallback;
    GameBoard *gameBoard;
    QLabel *labels[GameConfig::numRows][GameConfig::numColumns];
    int currentPlayer;
    int findEmptyRow(int column);
    bool checkForWin(int row, int column);
    bool checkLine(const QString& color, int startRow, int startCol, int deltaY, int deltaX);

};

#endif // MAINWINDOW_H