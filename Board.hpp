#include "Piece.hpp"
#pragma once

class Board{
private :
    Piece* boardPieces[8][8];
public : 
    Board();
    ~Board();

    void displayBoard();

    Piece* getPieceAt(int row, int col);
    void setPieceAt(int row, int col, Piece* piece);
};