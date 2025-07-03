#include <bits/stdc++.h>
#include "RuleChecker.hpp"
using namespace std;


bool RuleChecker::isCheck(Board* board,bool whiteTurn){
    int kingRowPosition,kingColPosition;
    bool foundKing = false;

    for(int row = 0;row < 8 && !foundKing;row++){
        for(int col = 0;col < 8 && !foundKing;col++){
            if(board->getPieceAt(row,col) != nullptr){
                if((whiteTurn && board->getPieceAt(row,col)->getSymbol() == 'K') || (!whiteTurn && board->getPieceAt(row,col)->getSymbol() == 'k')){
                    kingRowPosition = row;
                    kingColPosition = col;
                    foundKing = true;
                    break;
                }
            }
        }
    }

     for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece* attacker = board->getPieceAt(row,col);
            if (attacker != nullptr && attacker->isWhite() != whiteTurn) {
                if (attacker->isValidMove(row, col, kingRowPosition, kingColPosition, board)) {
                    return true; 
                }
            }
        }
    }

    return false;
}

bool RuleChecker::isCheckmate(Board* board,bool whiteTurn){
    if(!isCheck(board,whiteTurn)) return false;

    for (int fromRow = 0; fromRow < 8; fromRow++) {
        for (int fromCol = 0; fromCol < 8; fromCol++) {
            Piece* piece = board->getPieceAt(fromRow,fromCol);

            if (piece != nullptr && piece->isWhite() == whiteTurn) {
                for (int toRow = 0; toRow < 8; toRow++) {
                    for (int toCol = 0; toCol < 8; toCol++) {
                        if (piece->isValidMove(fromRow, fromCol, toRow, toCol, board)) {
                            Piece* captured = board->getPieceAt(toRow,toCol);
                            board->setPieceAt(toRow,toCol,piece);
                            board->setPieceAt(fromRow,fromCol,piece);

                            bool stillInCheck = isCheck(board,whiteTurn);

                            board->setPieceAt(fromRow,fromCol,piece);
                            board->setPieceAt(toRow,toCol,captured);

                            if (!stillInCheck) return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}
