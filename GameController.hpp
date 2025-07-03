#include "Board.hpp"
#pragma once

class GameController{
private :
   Board* board;
   bool whiteTurn;

public :
    GameController(Board* board);
    void startGame();
    void makeMove();
    void endGame(char winner);
    void switchTurn();
    bool isWhiteTurn();
};