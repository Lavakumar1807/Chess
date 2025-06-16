#include "Piece.hpp"
#pragma once

class Board{
private :
    bool whiteTurn;
    Piece* board[8][8];
public : 
    Board();
    ~Board();

    void startGame();
    void endGame(char winner);
    void displayBoard();
    
    void makeMove();
    bool isCheck();   
    bool isCheckmate();

    void switchTurn();
    bool isWhiteTurn();
};