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

    QString buttonStyle = QString(
            "QPushButton { "
            "font-size: 20px; "
            "min-width: 200px; "
            "min-height: 50px; "
            "background-color: %1; "
            "color: %2; "
            "}"
    ).arg(GameConfig::buttonColor, GameConfig::buttonTextColor);

    rematchButton->setStyleSheet(buttonStyle);
    returnToMainMenuButton->setStyleSheet(buttonStyle);

    layout->addWidget(messageLabel);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(rematchButton);
    buttonsLayout->addWidget(returnToMainMenuButton);

    layout->addLayout(buttonsLayout);

    connect(rematchButton, &QPushButton::clicked, this, [this, onRematchCallback]() {
        if (onRematchCallback) onRematchCallback();
        this->close();
    });
    connect(returnToMainMenuButton, &QPushButton::clicked, this, [this, onReturnToMainMenuCallback]() {
        if (onReturnToMainMenuCallback) onReturnToMainMenuCallback();
        this->close();
    });
}

void WinDialog::setWinner(int playerNumber) {
    QLabel *messageLabel = findChild<QLabel *>();
    QString playerColor = (playerNumber == 1) ? GameConfig::playerOneColor : GameConfig::playerTwoColor;

    if (messageLabel) {
        messageLabel->setText(tr("Player %1 Wins!").arg(playerNumber));
        messageLabel->setStyleSheet(QString(
                "QLabel { "
                "color: %1; "
                "font-size: 20px; "
                "}"
        ).arg(playerColor));
    }
}

void WinDialog::setMessage(const QString& message) {
    QLabel *messageLabel = findChild<QLabel *>();
    if (messageLabel) {
        messageLabel->setText(message);
    }
}