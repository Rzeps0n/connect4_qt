#include "WinDialog.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

WinDialog::WinDialog(QWidget *parent, std::function<void()> onRematchCallback, std::function<void()> onReturnToMainMenuCallback)
        : QDialog(parent), onRematchCallback(onRematchCallback), onReturnToMainMenuCallback(onReturnToMainMenuCallback) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *messageLabel = new QLabel(this);

    rematchButton = new QPushButton(tr("Rematch"), this);
    returnToMainMenuButton = new QPushButton(tr("Return to Main Menu"), this);

    layout->addWidget(messageLabel);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(rematchButton);
    buttonsLayout->addWidget(returnToMainMenuButton);

    layout->addLayout(buttonsLayout);

    connect(rematchButton, &QPushButton::clicked, this, [this, onRematchCallback]() {
        if (onRematchCallback) onRematchCallback();
        close();
    });
    connect(returnToMainMenuButton, &QPushButton::clicked, this, [this, onReturnToMainMenuCallback]() {
        if (onReturnToMainMenuCallback) onReturnToMainMenuCallback();
        close();
    });
}

void WinDialog::setWinner(int playerNumber) {
    QLabel *messageLabel = findChild<QLabel *>();
    QString playerColor = (playerNumber == 1) ? GameConfig::playerOneColor : GameConfig::playerTwoColor;

    if (messageLabel) {
        messageLabel->setText(tr("Player %1 Wins!").arg(playerNumber));
        messageLabel->setStyleSheet(QString("color: %1;").arg(playerColor));
    }
}
