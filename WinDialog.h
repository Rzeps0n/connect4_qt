#ifndef WINDIALOG_H
#define WINDIALOG_H

#include "GameConfig.h"
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <functional>

class WinDialog : public QDialog {
Q_OBJECT

public:
    explicit WinDialog(QWidget *parent = nullptr, std::function<void()> onRematchCallback = nullptr, std::function<void()> onReturnToMainMenuCallback = nullptr);
    void setWinner(int playerNumber);

private:
    QPushButton *rematchButton;
    QPushButton *returnToMainMenuButton;
    std::function<void()> onRematchCallback;
    std::function<void()> onReturnToMainMenuCallback;
};

#endif // WINDIALOG_H