#ifndef WINDIALOG_H
#define WINDIALOG_H

#include "GameConfig.h"
#include <QDialog>
#include <QLabel>

class WinDialog : public QDialog {
Q_OBJECT

public:
    explicit WinDialog(QWidget *parent = nullptr, std::function<void()> onRematchCallback = nullptr, std::function<void()> onReturnToMainMenuCallback = nullptr);
    void setWinner(int playerNumber);
    void setMessage(const QString& message);

private:
    QPushButton *rematchButton;
    QPushButton *returnToMainMenuButton;
    std::function<void()> onRematchCallback;
    std::function<void()> onReturnToMainMenuCallback;
};

#endif // WINDIALOG_H