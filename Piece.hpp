#pragma once

class Board;

class Piece{
private : 
   bool white;
   char symbol;
public : 
   Piece(bool isWhite);
   //~Piece();

   bool isWhite();
   char getSymbol();
   void setSymbol(char symbol);

   virtual bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board* board) = 0;
};
