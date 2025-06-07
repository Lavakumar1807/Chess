#pragma once

class Board{
private :
    bool whiteTurn;
    //Piece* board[8][8];
public : 
    Board();
    ~Board();

    void initializeBoard();
    void displayBoard();
    bool isValidPosition(int row, int col) const;
    
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol);
    bool isCheck(bool whiteTurn);   
    bool isCheckmate(bool whiteTurn);

    void switchTurn();
    bool isWhiteTurn();
};