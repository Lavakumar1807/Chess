#pragma once

class Piece{
private : 
   bool white;
   char symbol;
   bool moved;
public : 
   Piece(bool isWhite);
   ~Piece();

   bool isWhite();
   char getSymbol();
   void setSymbol(char symbol);
   bool isMoved();
   void setMoved(bool moved);

   virtual bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) = 0;
};
