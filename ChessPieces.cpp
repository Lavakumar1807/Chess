#include<bits/stdc++.h>
#include "Piece.hpp"
#include "Board.hpp"

using namespace std;


// Pawn
class Pawn : public Piece {
    bool moved;
public:
    Pawn(bool isWhite): Piece(isWhite) {
        setSymbol(isWhite ? 'P' : 'p');
        moved = false;
    }

    void setMoved(bool val) { 
        moved = val;
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board* board) {
        if (toRow == fromRow && toCol == fromCol) return false;
        if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) return false;

        int direction = isWhite() ? 1 : -1;
        int rowDiff = toRow - fromRow;
        int colDiff = toCol - fromCol;

        // Forward move
        if (colDiff == 0) {
            if (rowDiff == direction && board->getPieceAt(toRow, toCol) == nullptr) {
                return true;
            }
            if (!moved && rowDiff == 2 * direction) {
                int midRow = fromRow + direction;
                if (board->getPieceAt(toRow, toCol) == nullptr &&
                    board->getPieceAt(midRow, toCol) == nullptr) {
                    return true;
                }
            }
        }

        // Diagonal capture
        if (abs(colDiff) == 1 && rowDiff == direction) {
            Piece* target = board->getPieceAt(toRow, toCol);
            if (target != nullptr && target->isWhite() != this->isWhite()) {
                return true;
            }
        }

        return false;
    }
};

// King
class King : public Piece {
public : 
    King(bool isWhite): Piece(isWhite){
      setSymbol(isWhite ? 'K' : 'k');
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol,  Board* board){
        if(toRow == fromRow && toCol == fromCol) return false;
        if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) return false;

        int rowDiff = abs(fromRow - toRow);
        int colDiff = abs(fromCol - toCol);

        if (max(rowDiff, colDiff) != 1) return false;

        if (board->getPieceAt(toRow,toCol) != nullptr && board->getPieceAt(toRow,toCol)->isWhite() == this->isWhite())
            return false;

        return true;
    }
};

// Queen
class Queen : public Piece {
public : 
    Queen(bool isWhite): Piece(isWhite){
      setSymbol(isWhite ? 'Q' : 'q');
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol,  Board* board){
       if(toRow == fromRow && toCol == fromCol) return false;
       if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) return false;
       
       int rowDiff = abs(toRow - fromRow);
       int colDiff = abs(toCol - fromCol);

       if(toRow == fromRow){
        // Horizontal Movement

         if(toCol > fromCol){
            for(int column = fromCol + 1; column < toCol; column++){
                if(board->getPieceAt(fromRow,column) != nullptr) return false;
            }
         }else{
            for(int column = fromCol - 1; column > toCol; column--){
                if(board->getPieceAt(fromRow,column) != nullptr) return false;
            }
         }
       }else if(toCol == fromCol){
        // Vertical Movement

          if(toRow > fromRow){
            for(int row = fromRow + 1; row < toRow; row++){
                if(board->getPieceAt(row,fromCol) != nullptr) return false;
            }
          }else{
             for(int row = fromRow - 1; row > toRow; row--){
                if(board->getPieceAt(row,fromCol)  != nullptr) return false;
            }
          }
       }else if(rowDiff == colDiff){
        // Diagonal Movement

          if(toRow < fromRow  && toCol > fromCol){
            for(int diff = 1;diff < rowDiff; diff++){
                if(board->getPieceAt(fromRow - diff,fromCol + diff) != nullptr) return false;
            }
          }else if(toRow < fromRow && toCol < fromCol){
            for(int diff = 1; diff < rowDiff; diff++){
                if(board->getPieceAt(fromRow - diff,fromCol - diff) != nullptr) return false;
            }
          }else if(toRow > fromRow && toCol < fromCol){
            for(int diff = 1; diff < rowDiff; diff++){
                if(board->getPieceAt(fromRow + diff,fromCol - diff) != nullptr) return false;
            }
          }else if(toRow > fromRow && toCol > fromCol){
            for(int diff = 1;diff < rowDiff; diff++){
                if(board->getPieceAt(fromRow + diff,fromCol + diff) != nullptr) return false;
            }
          }
       }else return false;

       if (board->getPieceAt(toRow,toCol) != nullptr && board->getPieceAt(toRow,toCol)->isWhite() == this->isWhite()) return false;

       return true;
    }
};

// Bishop
class Bishop : public Piece {
public : 
    Bishop(bool isWhite): Piece(isWhite){
       setSymbol(isWhite ? 'B' : 'b');
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol,  Board* board){
        if(toRow == fromRow && toCol == fromCol) return false;
        if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) return false;

        int rowDiff = abs(toRow - fromRow);
        int colDiff = abs(toCol - fromCol);

        if(rowDiff != colDiff) return false;

        // Diagonal Movement
        if(toRow < fromRow  && toCol > fromCol){
            for(int diff = 1;diff < rowDiff; diff++){
                if(board->getPieceAt(fromRow - diff,fromCol + diff) != nullptr) return false;
            }
        }else if(toRow < fromRow && toCol < fromCol){
            for(int diff = 1; diff < rowDiff; diff++){
                if(board->getPieceAt(fromRow - diff,fromCol - diff) != nullptr) return false;
            }
        }else if(toRow > fromRow && toCol < fromCol){
            for(int diff = 1; diff < rowDiff; diff++){
                if(board->getPieceAt(fromRow + diff,fromCol - diff) != nullptr) return false;
            }
        }else if(toRow > fromRow && toCol > fromCol){
            for(int diff = 1;diff < rowDiff; diff++){
                if(board->getPieceAt(fromRow + diff,fromCol + diff) != nullptr) return false;
            }
        }else return false;


        if (board->getPieceAt(toRow,toCol) != nullptr && board->getPieceAt(toRow,toCol) ->isWhite() == this->isWhite()) return false;

        return true; 
    }
};

// Knight
class Knight : public Piece {
public :
    Knight(bool isWhite): Piece(isWhite){
      setSymbol(isWhite ? 'N' : 'n');
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol,  Board* board){
       if(toRow == fromRow && toCol == fromCol) return false;
       if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) return false;

       int rowDiff = abs(fromRow - toRow);
       int colDiff = abs(fromCol - toCol);
        
       if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))) return false;

       if (board->getPieceAt(toRow,toCol)  != nullptr && board->getPieceAt(toRow,toCol)->isWhite() == this->isWhite()) return false;

       return true; 
    }
};

// Rook
class Rook : public Piece{
public : 
    Rook(bool isWhite): Piece(isWhite){
      setSymbol(isWhite ? 'R' : 'r');
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol,  Board* board){
       if(toRow == fromRow && toCol == fromCol) return false;
       if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) return false;

       if(toRow == fromRow){
        // Horizontal Movement

         if(toCol > fromCol){
            for(int column = fromCol + 1; column < toCol; column++){
                if(board->getPieceAt(fromRow,column) != nullptr) return false;
            }
         }else{
            for(int column = fromCol - 1; column > toCol; column--){
                if(board->getPieceAt(fromRow,column) != nullptr) return false;
            }
         }
       }else if(toCol == fromCol){
        // Vertical Movement

          if(toRow > fromRow){
            for(int row = fromRow + 1; row < toRow; row++){
                if(board->getPieceAt(row,fromCol) != nullptr) return false;
            }
          }else{
             for(int row = fromRow - 1; row > toRow; row--){
                if(board->getPieceAt(row,fromCol) != nullptr) return false;
            }
          }
       }else return false;

       if (board->getPieceAt(toRow,toCol) != nullptr && board->getPieceAt(toRow,toCol)->isWhite() == this->isWhite()) return false;

       return true; 
    }
};