#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
    this->setStyleSheet(QString("background-color: %1;").arg(GameConfig::backgroundColor));
    numColumnsSpinBox = new QSpinBox(this);
    numRowsSpinBox = new QSpinBox(this);
    numColumnsSpinBox->setRange(1, 20); // Adjust these ranges as needed
    numRowsSpinBox->setRange(1, 20);
    resolutionComboBox = new QComboBox(this);
    saveButton = new QPushButton(tr("Save"), this);
    exitButton = new QPushButton(tr("Exit"), this);
    allowResizeCheckBox = new QCheckBox(tr("Allow window resize (experimental)"), this);

    QStringList resolutions = {"800x600", "1024x768", "1280x720", "1366x768", "1920x1080", "2560x1440"};
    resolutionComboBox->addItems(resolutions);

    // Define and apply the button style
    QString buttonStyle = QString(
            "QPushButton { "
            "background-color: %1; "
            "color: %2; "
            "}"
    ).arg(GameConfig::buttonColor, GameConfig::buttonTextColor);

    saveButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle);


    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *numColumnsLayout = new QHBoxLayout();
    QLabel *numColumnsLabel = new QLabel(tr("Number of Columns:"), this);
    numColumnsLayout->addWidget(numColumnsLabel);
    numColumnsLayout->addWidget(numColumnsSpinBox);
    mainLayout->addLayout(numColumnsLayout);

    QHBoxLayout *numRowsLayout = new QHBoxLayout();
    QLabel *numRowsLabel = new QLabel(tr("Number of Rows:"), this);
    numRowsLayout->addWidget(numRowsLabel);
    numRowsLayout->addWidget(numRowsSpinBox);
    mainLayout->addLayout(numRowsLayout);

    QHBoxLayout *resolutionLayout = new QHBoxLayout();
    QLabel *resolutionLabel = new QLabel(tr("Resolution:"), this);
    resolutionLayout->addWidget(resolutionLabel);
    resolutionLayout->addWidget(resolutionComboBox);
    mainLayout->addLayout(resolutionLayout);

    QHBoxLayout *playerOneColorLayout = new QHBoxLayout();
    QLabel *playerOneColorLabel = new QLabel(tr("Player One Color:"), this);
    playerOneColorButton = new QPushButton(tr("Choose Color"), this);
    playerOneColorLayout->addWidget(playerOneColorLabel);
    playerOneColorLayout->addWidget(playerOneColorButton);
    mainLayout->addLayout(playerOneColorLayout);

    QHBoxLayout *playerTwoColorLayout = new QHBoxLayout();
    QLabel *playerTwoColorLabel = new QLabel(tr("Player Two Color:"), this);
    playerTwoColorButton = new QPushButton(tr("Choose Color"), this);
    playerTwoColorLayout->addWidget(playerTwoColorLabel);
    playerTwoColorLayout->addWidget(playerTwoColorButton);
    mainLayout->addLayout(playerTwoColorLayout);

    mainLayout->addWidget(allowResizeCheckBox);
    allowResizeCheckBox->setChecked(GameConfig::allowWindowResize);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(exitButton);
    mainLayout->addLayout(buttonsLayout);

    connect(playerOneColorButton, &QPushButton::clicked, this, &SettingsDialog::choosePlayerOneColor);
    connect(playerTwoColorButton, &QPushButton::clicked, this, &SettingsDialog::choosePlayerTwoColor);
    connect(saveButton, &QPushButton::clicked, this, &SettingsDialog::saveSettings);
    connect(exitButton, &QPushButton::clicked, this, &SettingsDialog::close);

    setLayout(mainLayout);
    loadSettings();
}
void SettingsDialog::loadSettings() {
    numColumnsSpinBox->setValue(GameConfig::numColumns);
    numRowsSpinBox->setValue(GameConfig::numRows);
    currentPlayerOneColor = QColor(GameConfig::playerOneColor);
    currentPlayerTwoColor = QColor(GameConfig::playerTwoColor);
    playerOneColorButton->setStyleSheet(QString("background-color: %1").arg(currentPlayerOneColor.name()));
    playerTwoColorButton->setStyleSheet(QString("background-color: %1").arg(currentPlayerTwoColor.name()));
    QString currentResolution = QString("%1x%2").arg(GameConfig::windowWidth).arg(GameConfig::windowHeight);
    int index = resolutionComboBox->findText(currentResolution);
    if (index != -1) {
        resolutionComboBox->setCurrentIndex(index);
    }
}

void SettingsDialog::saveSettings() {
    // Update the number of columns and rows
    GameConfig::numColumns = numColumnsSpinBox->value();
    GameConfig::numRows = numRowsSpinBox->value();

    // Update player colors
    GameConfig::playerOneColor = currentPlayerOneColor.name();
    GameConfig::playerTwoColor = currentPlayerTwoColor.name();

    // Handle resolution change
    QString selectedResolution = resolutionComboBox->currentText();
    QStringList dimensions = selectedResolution.split("x");
    if (dimensions.size() == 2) {
        int width = dimensions[0].toInt();
        int height = dimensions[1].toInt();
        GameConfig::windowWidth = width;
        GameConfig::windowHeight = height;
    }
    GameConfig::allowWindowResize = allowResizeCheckBox->isChecked();

    accept();
}

void SettingsDialog::choosePlayerOneColor() {
    QColor color = QColorDialog::getColor(currentPlayerOneColor, this, tr("Choose Player One Color"));
    if (color.isValid()) {
        currentPlayerOneColor = color;
        playerOneColorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
    }
}
void SettingsDialog::choosePlayerTwoColor() {
    QColor color = QColorDialog::getColor(currentPlayerTwoColor, this, tr("Choose Player Two Color"));
    if (color.isValid()) {
        currentPlayerTwoColor = color;
        playerTwoColorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
    }
}