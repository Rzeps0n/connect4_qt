#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameConfig.h"
#include "GameBoard.h"
#include <QAbstractAnimation>
#include <QApplication>
#include <QEasingCurve>
#include <QGridLayout>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QResizeEvent>
#include "WinDialog.h"
#include "menu.h"
#include <vector>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, std::function<void()> showMenuCallback = nullptr);
    ~MainWindow();

private slots:
    void handleColumnClicked(int column);
    void showWinDialog(const QString& message);

private:
    std::function<void()> showMainMenuCallback;
    GameBoard *gameBoard;
    std::vector<std::vector<QLabel*>> labels;
    int currentPlayer;
    int findEmptyRow(int column);
    bool checkForWin(int row, int column);
    bool checkLine(const QString& color, int startRow, int startCol, int deltaY, int deltaX);
    bool isBoardFull();
};

#endif // MAINWINDOW_H