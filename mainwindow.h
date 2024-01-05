//
// Created by Adam Rzepka on 05/01/2024.
//

#ifndef CONNECT4_PROJECT_MAINWINDOW_H
#define CONNECT4_PROJECT_MAINWINDOW_H

#endif //CONNECT4_PROJECT_MAINWINDOW_H

// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QResizeEvent>

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButtonClicked();
    //void showMainMenu();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QGridLayout *gridLayout;
    QPushButton *buttons[6][7]; // 6 rows, 7 columns
    int currentPlayer;

    void setupBoard();
    bool checkForWin(int row, int col);
    bool checkDirection(int row, int col, int xDir, int yDir);
    //void showWinMessage(int player);
};

#endif // MAINWINDOW_H