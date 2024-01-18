#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include "mainwindow.h"
#include "SettingsDialog.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    showStartMenu(app);

    return app.exec();
}