#include "Board.hpp"
#pragma once

class RuleChecker {
public :
    static bool isCheck(Board* board, bool whiteTurn);
    static bool isCheckmate(Board* board, bool whiteTurn);
};