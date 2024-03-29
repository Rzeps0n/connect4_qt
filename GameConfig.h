#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#include "QString"

namespace GameConfig {
    extern int numColumns;
    extern int numRows;
    extern int windowWidth;
    extern int windowHeight;

    extern QString playerOneColor;
    extern QString playerTwoColor;
    extern QString tokenBackgroundColor;
    extern QString backgroundColor;
    extern QString buttonColor;
    extern QString buttonTextColor;
    extern bool allowWindowResize;
}

#endif // GAMECONFIG_H