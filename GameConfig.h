#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#import "QString"

namespace GameConfig {
    constexpr int numColumns = 7;
    constexpr int numRows = 6;
    constexpr int windowWidth = 800;
    constexpr int windowHeight = 600;

    const QString playerOneColor = "red";
    const QString playerTwoColor = "yellow";
    const QString tokenBackgroundColor = "darkgrey";
    const QString backgroundColor = "#383434";
    const QString buttonColor = "#f0f0f0";
    const QString buttonTextColor = "#000000";
    const QString mainWindowBackgroundColor = "#383434";
}

#endif // GAMECONFIG_H