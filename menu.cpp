#include "menu.h"
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include "GameConfig.h"
#include "MainWindow.h"
#include "SettingsDialog.h"

void showStartMenu(QApplication& app) {
    QDialog startMenu;
    startMenu.setWindowTitle("Start Menu");
    startMenu.resize(GameConfig::windowWidth, GameConfig::windowHeight);

    QPushButton startButton("Start Game", &startMenu);
    QPushButton settingsButton("Settings", &startMenu);
    QPushButton quitButton("Quit Game", &startMenu);

    QString buttonStyle = QString(
            "QPushButton { "
            "font-size: 20px; "
            "min-width: 200px; "
            "min-height: 50px; "
            "background-color: %1; "
            "color: %2; "
            "}"
    ).arg(GameConfig::buttonColor, GameConfig::buttonTextColor);
    startButton.setStyleSheet(buttonStyle);
    settingsButton.setStyleSheet(buttonStyle);
    quitButton.setStyleSheet(buttonStyle);

    QVBoxLayout layout;
    layout.addWidget(&startButton);
    layout.addWidget(&settingsButton);
    layout.addWidget(&quitButton);
    startMenu.setLayout(&layout);

    QObject::connect(&startButton, &QPushButton::clicked, [&]() {
        startMenu.close();
        MainWindow* mainWindow = new MainWindow();
        mainWindow->show();
    });

    QObject::connect(&settingsButton, &QPushButton::clicked, [&]() {
        SettingsDialog settingsDialog;
        settingsDialog.exec();
    });

    QObject::connect(&quitButton, &QPushButton::clicked, &app, &QApplication::exit);

    startMenu.exec();
}