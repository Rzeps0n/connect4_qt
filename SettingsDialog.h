#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QSpinBox>
#include <QColorDialog>
#include <QPushButton>
#include "GameConfig.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <qlabel.h>
#include <qcheckbox.h>

class SettingsDialog : public QDialog {
Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

private slots:
    void choosePlayerOneColor();
    void choosePlayerTwoColor();

private:
    QColor currentPlayerOneColor;
    QColor currentPlayerTwoColor;
    QSpinBox *numColumnsSpinBox;
    QSpinBox *numRowsSpinBox;
    QComboBox *resolutionComboBox;
    QPushButton *playerOneColorButton;
    QPushButton *playerTwoColorButton;
    QPushButton *saveButton;
    QPushButton *exitButton;
    QCheckBox *allowResizeCheckBox;

    void loadSettings();
    void saveSettings();
};

#endif // SETTINGSDIALOG_H