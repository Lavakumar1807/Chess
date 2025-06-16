#include<bits/stdc++.h>
#include "Piece.hpp"

using namespace std;

// Pawn
class Pawn : public Piece {
public :
    Pawn(bool isWhite): Piece(isWhite){
      setSymbol(isWhite ? 'P' : 'p');
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]){
        if(toRow == fromRow && toCol == fromCol) return false;
        if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) return false;

        char pawnColor = this->isWhite() ? 'W' : 'B';
        bool firstMove = this->isMoved() ? false : true;

        if(pawnColor == 'W'){
        // White pawn moves from lowRow to highRow (1 -> 7)
            int rowDiff = toRow - fromRow;
            if(rowDiff <= 0){
                return false;
            }

            if(firstMove && rowDiff <=2  && toCol == fromCol){
                if(rowDiff == 2 && (board[toRow][toCol] != nullptr || board[fromRow + 1][toCol] != nullptr)) return false;
                else if(rowDiff ==1 && board[toRow][toCol] != nullptr) return false;
                return true;
            }

            if (rowDiff == 1 && toCol == fromCol && board[toRow][toCol] == nullptr) {
                return true;
            }
            return false;
        }else{
        // Black pawn moves from highRow to lowRow (6 -> 0)
            int rowDiff = fromRow - toRow;
            if(rowDiff <= 0){
                return false;
            }

            if(firstMove && rowDiff <=2  && toCol == fromCol){
                if(rowDiff == 2 && (board[toRow][toCol] != nullptr || board[fromRow - 1][toCol] != nullptr)) return false;
                else if(rowDiff ==1 && board[toRow][toCol] != nullptr) return false;
                return true;
            }
            
            if (rowDiff == 1 && toCol == fromCol && board[toRow][toCol] == nullptr) {
                return true;
            }
            return false;
        }
    }
};

// King
class King : public Piece {
public : 
    King(bool isWhite): Piece(isWhite){
      setSymbol(isWhite ? 'K' : 'k');
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]){
        if(toRow == fromRow && toCol == fromCol) return false;
        if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) return false;

        int rowDiff = abs(fromRow - toRow);
        int colDiff = abs(fromCol - toCol);

        if (max(rowDiff, colDiff) != 1) return false;

        if (board[toRow][toCol] != nullptr && board[toRow][toCol]->isWhite() == this->isWhite())
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

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]){
       if(toRow == fromRow && toCol == fromCol) return false;
       if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) return false;
       
       int rowDiff = abs(toRow - fromRow);
       int colDiff = abs(toCol - fromCol);

       if(toRow == fromRow){
        // Horizontal Movement

         if(toCol > fromCol){
            for(int column = fromCol + 1; column < toCol; column++){
                if(board[fromRow][column] != nullptr) return false;
            }
         }else{
            for(int column = fromCol - 1; column > toCol; column--){
                if(board[fromRow][column] != nullptr) return false;
            }
         }
       }else if(toCol == fromCol){
        // Vertical Movement

          if(toRow > fromRow){
            for(int row = fromRow + 1; row < toRow; row++){
                if(board[row][fromCol] != nullptr) return false;
            }
          }else{
             for(int row = fromRow - 1; row > toRow; row--){
                if(board[row][fromCol] != nullptr) return false;
            }
          }
       }else if(rowDiff == colDiff){
        // Diagonal Movement

          if(toRow < fromRow  && toCol > fromCol){
            for(int diff = 1;diff < rowDiff; diff++){
                if(board[fromRow - diff][fromCol + diff] != nullptr) return false;
            }
          }else if(toRow < fromRow && toCol < fromCol){
            for(int diff = 1; diff < rowDiff; diff++){
                if(board[fromRow - diff][fromCol - diff] != nullptr) return false;
            }
          }else if(toRow > fromRow && toCol < fromCol){
            for(int diff = 1; diff < rowDiff; diff++){
                if(board[fromRow + diff][fromCol - diff] != nullptr) return false;
            }
          }else if(toRow > fromRow && toCol > fromCol){
            for(int diff = 1;diff < rowDiff; diff++){
                if(board[fromRow + diff][fromCol + diff] != nullptr) return false;
            }
          }
       }else return false;

       if (board[toRow][toCol] != nullptr && board[toRow][toCol]->isWhite() == this->isWhite()) return false;

       return true;
    }
};

// Bishop
class Bishop : public Piece {
public : 
    Bishop(bool isWhite): Piece(isWhite){
       setSymbol(isWhite ? 'B' : 'b');
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]){
        if(toRow == fromRow && toCol == fromCol) return false;
        if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) return false;

        int rowDiff = abs(toRow - fromRow);
        int colDiff = abs(toCol - fromCol);

        if(rowDiff != colDiff) return false;

        // Diagonal Movement
        if(toRow < fromRow  && toCol > fromCol){
            for(int diff = 1;diff < rowDiff; diff++){
                if(board[fromRow - diff][fromCol + diff] != nullptr) return false;
            }
        }else if(toRow < fromRow && toCol < fromCol){
            for(int diff = 1; diff < rowDiff; diff++){
                if(board[fromRow - diff][fromCol - diff] != nullptr) return false;
            }
        }else if(toRow > fromRow && toCol < fromCol){
            for(int diff = 1; diff < rowDiff; diff++){
                if(board[fromRow + diff][fromCol - diff] != nullptr) return false;
            }
        }else if(toRow > fromRow && toCol > fromCol){
            for(int diff = 1;diff < rowDiff; diff++){
                if(board[fromRow + diff][fromCol + diff] != nullptr) return false;
            }
        }else return false;


        if (board[toRow][toCol] != nullptr && board[toRow][toCol]->isWhite() == this->isWhite()) return false;

        return true; 
    }
};

// Knight
class Knight : public Piece {
public :
    Knight(bool isWhite): Piece(isWhite){
      setSymbol(isWhite ? 'N' : 'n');
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]){
       if(toRow == fromRow && toCol == fromCol) return false;
       if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) return false;

       int rowDiff = abs(fromRow - toRow);
       int colDiff = abs(fromCol - toCol);
        
       if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))) return false;

       if (board[toRow][toCol] != nullptr && board[toRow][toCol]->isWhite() == this->isWhite()) return false;

       return true; 
    }
};

// Rook
class Rook : public Piece{
public : 
    Rook(bool isWhite): Piece(isWhite){
      setSymbol(isWhite ? 'R' : 'r');
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]){
       if(toRow == fromRow && toCol == fromCol) return false;
       if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) return false;

       if(toRow == fromRow){
        // Horizontal Movement

         if(toCol > fromCol){
            for(int column = fromCol + 1; column < toCol; column++){
                if(board[fromRow][column] != nullptr) return false;
            }
         }else{
            for(int column = fromCol - 1; column > toCol; column--){
                if(board[fromRow][column] != nullptr) return false;
            }
         }
       }else if(toCol == fromCol){
        // Vertical Movement

          if(toRow > fromRow){
            for(int row = fromRow + 1; row < toRow; row++){
                if(board[row][fromCol] != nullptr) return false;
            }
          }else{
             for(int row = fromRow - 1; row > toRow; row--){
                if(board[row][fromCol] != nullptr) return false;
            }
          }
       }else return false;

       if (board[toRow][toCol] != nullptr && board[toRow][toCol]->isWhite() == this->isWhite()) return false;

       return true; 
    }
};