#include<bits/stdc++.h>
#include "Board.hpp"
#include "ChessPieces.cpp"

using namespace std;

// (true) --> White Piece
// (false) --> Black Piece

// Factory Design Pattern
class PieceFactory {
public:
    static Piece* createPiece(const string& type, bool isWhite) {
        if (type == "pawn") return new Pawn(isWhite);
        else if (type == "rook") return new Rook(isWhite);
        else if (type == "knight") return new Knight(isWhite);
        else if (type == "bishop") return new Bishop(isWhite);
        else if (type == "queen") return new Queen(isWhite);
        else if (type == "king") return new King(isWhite);
        else {
            cerr << "Invalid piece type: " << type << endl;
            return nullptr;
        }
    }
};

Board::Board(){
    for(int row = 0;row < 8; row++){
        for(int col = 0;col < 8; col++){
            boardPieces[row][col] = nullptr;
        }
    }

    for(int col = 0;col < 8; col++){
        boardPieces[1][col] = PieceFactory::createPiece("pawn",true);
        boardPieces[6][col] = PieceFactory::createPiece("pawn",false);
    }

    // King
    boardPieces[0][3] = PieceFactory::createPiece("king",true);
    boardPieces[7][3] = PieceFactory::createPiece("king",false);

    // Queen
    boardPieces[0][4] = PieceFactory::createPiece("queen",true);
    boardPieces[7][4] = PieceFactory::createPiece("queen",false);

    // Rooks
    boardPieces[0][0] = PieceFactory::createPiece("rook",true);
    boardPieces[0][7] = PieceFactory::createPiece("rook",true);
    boardPieces[7][0] = PieceFactory::createPiece("rook",false);
    boardPieces[7][7] = PieceFactory::createPiece("rook",false);

    // Knight
    boardPieces[0][1] = PieceFactory::createPiece("knight",true);
    boardPieces[0][6] = PieceFactory::createPiece("knight",true);
    boardPieces[7][1] = PieceFactory::createPiece("knight",false);
    boardPieces[7][6] = PieceFactory::createPiece("knight",false);

    // Bishop
    boardPieces[0][2] = PieceFactory::createPiece("bishop",true);
    boardPieces[0][5] = PieceFactory::createPiece("bishop",true);
    boardPieces[7][2] = PieceFactory::createPiece("bishop",false);
    boardPieces[7][5] = PieceFactory::createPiece("bishop",false);
}

void Board::displayBoard() {
    cout << "\n    ";
    for (int col = 0; col < 8; col++) {
        cout << col << "   ";
    }
    cout << "\n  +---+---+---+---+---+---+---+---+" << endl;

    for (int row = 0; row < 8; row++) {
        cout << row << " |";
        for (int col = 0; col < 8; col++) {
            if (boardPieces[row][col]) {
                cout << " " << boardPieces[row][col]->getSymbol() << " |";
            } else {
                cout << "   |";
            }
        }
        cout << endl;
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
    }
    cout << endl;
}

Board::~Board(){
    for(int row = 0;row < 8;row++){
        for(int col = 0;col < 8;col++){
            delete boardPieces[row][col];
        }
    }
}

Piece* Board::getPieceAt(int row,int column){
    if (row < 0 || row >= 8 || column < 0 || column >= 8) return nullptr;
    return boardPieces[row][column];
}

void Board::setPieceAt(int row,int column,Piece* piece){
    if (row < 0 || row >= 8 || column < 0 || column >= 8) return;
    boardPieces[row][column] = piece;
}