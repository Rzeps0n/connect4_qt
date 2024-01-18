#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent, std::function<void()> showMenuCallback)
        : QMainWindow(parent), showMainMenuCallback(showMenuCallback) {
    gameBoard = new GameBoard(this);
    setCentralWidget(gameBoard);
    this->setStyleSheet(QString("background-color: %1;").arg(GameConfig::backgroundColor));
    if (GameConfig::allowWindowResize) {
        this->setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
        resize(GameConfig::windowWidth, GameConfig::windowHeight);

    } else {
        this->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
        setFixedSize(GameConfig::windowWidth, GameConfig::windowHeight);
    }
    connect(gameBoard, &GameBoard::columnClicked, this,&MainWindow::handleColumnClicked);
    setWindowTitle("Connect 4");
    labels.resize(GameConfig::numRows, std::vector<QLabel*>(GameConfig::numColumns, nullptr));
    for (int row = 0; row < GameConfig::numRows; ++row) {
        for (int col = 0; col < GameConfig::numColumns; ++col) {
            labels[row][col] = nullptr;
        }
    }
}

MainWindow::~MainWindow() {}

void MainWindow::handleColumnClicked(int column) {
    int row = findEmptyRow(column);
    if (row < 0) {
        return; // Column is full
    }
    int columnWidth = this->width() / GameConfig::numColumns;
    int rowHeight = gameBoard->height() / GameConfig::numRows;
    int diameter = qMin(columnWidth, rowHeight) - (columnWidth / 5);
    QPoint center = gameBoard->calculateCenter(column, row);
    QLabel *token = new QLabel(gameBoard);
    QString color = (currentPlayer == 1) ? GameConfig::playerOneColor
                                         : GameConfig::playerTwoColor;
    token->setStyleSheet(QString("QLabel { background-color: %1; }").arg(color));
    token->setFixedSize(diameter, diameter);
    token->setStyleSheet(
            token->styleSheet() +
            QString(" QLabel { border-radius: %1px; }").arg(diameter / 2));

    QPoint startPos = center - QPoint(diameter / 2, gameBoard->height());
    QPoint endPos = center - QPoint(diameter / 2, diameter / 2);

    token->move(startPos);
    token->show();

    // Animate the token falling
    QPropertyAnimation *animation = new QPropertyAnimation(token, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(startPos, token->size()));
    animation->setEndValue(QRect(endPos, token->size()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    labels[row][column] = token;

    if (checkForWin(row, column)) {
        showWinDialog("Player " + QString::number(currentPlayer) + " Wins!");
    }
    else if (isBoardFull()) {
        // Show win dialog with a draw message
        showWinDialog("It's a Draw!");
    }
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

void MainWindow::showWinDialog(const QString& message) {
    auto onRematch = [this]() {
        this->hide();  // Ensure this line is being executed
        MainWindow *newGame = new MainWindow();
        newGame->show();
    };

    auto onReturnToMainMenu = [this]() {
        this->hide();
        showStartMenu(*qApp);
    };

    WinDialog winDialog(this, onRematch, onReturnToMainMenu);
    winDialog.setWinner(currentPlayer);
    winDialog.setMessage(message);
    winDialog.exec();
}

int MainWindow::findEmptyRow(int column) {
    for (int row = GameConfig::numRows - 1; row >= 0; --row) {
        if (labels[row][column] == nullptr) {
            return row;
        }
    }
    return -1; // No empty row found, column is full
}

bool MainWindow::checkForWin(int row, int column) {
    QString lastTokenColor = labels[row][column]->styleSheet();

    // Check horizontal
    for (int col = 0; col < GameConfig::numColumns - 3; col++) {
        if (checkLine(lastTokenColor, row, col, 0, 1)) {
            return true;
        }
    }

    // Check vertical
    for (int row = 0; row < GameConfig::numRows - 3; row++) {
        if (checkLine(lastTokenColor, row, column, 1, 0)) {
            return true;
        }
    }

    // Check diagonal
    for (int row = 3; row < GameConfig::numRows; row++) {
        for (int col = 0; col < GameConfig::numColumns - 3; col++) {
            if (checkLine(lastTokenColor, row, col, -1, 1)) {
                return true;
            }
        }
    }

    // Check diagonal
    for (int row = 0; row < GameConfig::numRows - 3; row++) {
        for (int col = 0; col < GameConfig::numColumns - 3; col++) {
            if (checkLine(lastTokenColor, row, col, 1, 1)) {
                return true;
            }
        }
    }

    return false;
}

bool MainWindow::checkLine(const QString& color, int startRow, int startCol, int deltaY, int deltaX) {
    for (int i = 0; i < 4; i++) {
        int row = startRow + i * deltaY;
        int col = startCol + i * deltaX;
        if (row < 0 || row >= GameConfig::numRows || col < 0 || col >= GameConfig::numColumns) {
            return false;
        }

        QLabel *label = labels[row][col];
        if (label == nullptr || label->styleSheet() != color) {
            return false;
        }
    }
    return true;
}

bool MainWindow::isBoardFull() {
    for (int row = 0; row < GameConfig::numRows; ++row) {
        for (int col = 0; col < GameConfig::numColumns; ++col) {
            if (labels[row][col] == nullptr) {
                return false; // Found an empty spot
            }
        }
    }
    return true; // No empty spots found
}