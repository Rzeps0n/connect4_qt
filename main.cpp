#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include "mainwindow.h"
#include "GameConfig.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QDialog startMenu;
    startMenu.setWindowTitle("Start Menu");
    startMenu.resize(GameConfig::windowWidth, GameConfig::windowHeight);

    // Create buttons
    QPushButton startButton("Start Game");
    QPushButton settingsButton("Settings");
    QPushButton quitButton("Quit Game");

    // Set button styles to be larger and square
    QString buttonStyle = "QPushButton { font-size: 20px; min-width: 200px; min-height: 50px; }";
    startButton.setStyleSheet(buttonStyle);
    settingsButton.setStyleSheet(buttonStyle);
    quitButton.setStyleSheet(buttonStyle);

    // Set up layout for the dialog
    QVBoxLayout layout;
    layout.addWidget(&startButton);
    layout.addWidget(&settingsButton);
    layout.addWidget(&quitButton);
    startMenu.setLayout(&layout);

    QObject::connect(&startButton, &QPushButton::clicked, &startMenu, &QDialog::accept);

    QObject::connect(&settingsButton, &QPushButton::clicked, []() {
        QMessageBox::information(nullptr, "Settings", "Settings go here.");
    });

    QObject::connect(&quitButton, &QPushButton::clicked, &startMenu, &QDialog::reject);

    if (startMenu.exec() == QDialog::Accepted) {
        MainWindow mainWindow;
        mainWindow.show();
        return a.exec();
    } else {
        return 0;
    }
}