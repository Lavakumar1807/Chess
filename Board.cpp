#include<bits/stdc++.h>
#include "Board.hpp"
#include "ChessPieces.cpp"

using namespace std;

// (true) --> White Piece
// (false) --> Black Piece

Board::Board(){
    whiteTurn = true;

    for(int row = 0;row < 8; row++){
        for(int col = 0;col < 8; col++){
            board[row][col] = nullptr;
        }
    }

    for(int col = 0;col < 8; col++){
        board[1][col] = new Pawn(true);
        board[6][col] = new Pawn(false);
    }

    // King
    board[0][3] = new King(true);
    board[7][3] = new King(false);

    // Queen
    board[0][4] = new Queen(true);
    board[7][4] = new Queen(false);

    // Rooks
    board[0][0] = new Rook(true);
    board[0][7] = new Rook(true);
    board[7][0] = new Rook(false);
    board[7][7] = new Rook(false);

    // Knight
    board[0][1] = new Knight(true);
    board[0][6] = new Knight(true);
    board[7][1] = new Knight(false);
    board[7][6] = new Knight(false);

    // Bishop
    board[0][2] = new Bishop(true);
    board[0][5] = new Bishop(true);
    board[7][2] = new Bishop(false);
    board[7][5] = new Bishop(false);
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
            if (board[row][col]) {
                cout << " " << board[row][col]->getSymbol() << " |";
            } else {
                cout << "   |";
            }
        }
        cout << endl;
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
    }
    cout << endl;
}

bool Board::isWhiteTurn(){
    return whiteTurn;
}

void Board::switchTurn(){
    whiteTurn = whiteTurn ? false : true;
}

void Board::startGame(){
    cout << "=====================================" << endl;
    cout << "         Welcome to Chess Game       " << endl;
    cout << "=====================================" << endl;
    cout << "White pieces: uppercase" << endl;
    cout << "Black pieces: lowercase" << endl;
    cout << endl;
    
    cout << "Piece Symbols:" << endl;
    cout << "  K / k : King" << endl;
    cout << "  Q / q : Queen" << endl;
    cout << "  R / r : Rook" << endl;
    cout << "  B / b : Bishop" << endl;
    cout << "  N / n : Knight" << endl;
    cout << "  P / p : Pawn" << endl;
    cout << endl;

    cout << "To make a move enter coordinates (0 - 7) :: [row][column]" << endl;
    cout << endl;
}

void Board::makeMove(){
    if(isWhiteTurn()) cout << "Turn : White" << endl; 
    else cout << "Turn : Black" << endl;

    int fromRow,fromCol,toRow,toCol;

    Piece* currentPiece;

    char Lock = 'n';
    while(Lock == 'n'){
        while(true){
            cout << "Enter current row and current column of the desired piece (current row , current column) : ";
            cin >> fromRow >> fromCol;
            Piece* piece = board[fromRow][fromCol];
            if(board[fromRow][fromCol] == nullptr){
                cout << "You have entered a position having no piece.." << endl;
                continue;
            }

            bool isCurrentPieceWhite = piece->isWhite();

            if(isCurrentPieceWhite == isWhiteTurn()){
            currentPiece = piece;
            break;
            }else{
                cout << "Invalid Piece. You can move your pieces only..." << endl;
            }
        }

        while(true){
            cout << "Enter destination row and destination column for the desired piece (destination row , destination column) : ";
            cin >> toRow >> toCol;

            bool isValid = currentPiece->isValidMove(fromRow,fromCol,toRow,toCol,board);
            if(isValid){
                board[toRow][toCol] = board[fromRow][fromCol];
                board[fromRow][fromCol] = nullptr;
                break;
            }else{
                cout << "Invalid move. Enter a valid destination position" << endl;
            }
        }

        char confirm;
        while(true){
            cout << "Lock the move...(y/n) : ";
            cin >> confirm;
            if(confirm == 'y') return;
            else if(confirm == 'n') {
                board[fromRow][fromCol] = board[toRow][toCol];
                board[toRow][toCol] = nullptr;
                Lock = confirm;
                break;
            }
            else continue;
        }
    }
}

bool Board::isCheck(bool whiteTurn){
    int kingRowPosition,kingColPosition;
    bool foundKing = false;

    for(int row = 0;row < 8 && !foundKing;row++){
        for(int col = 0;col < 8 && !foundKing;col++){
            if((whiteTurn && board[row][col]->getSymbol() == 'K') || (!whiteTurn && board[row][col]->getSymbol() == 'k')){
                kingRowPosition = row;
                kingColPosition = col;
                foundKing = true;
                break;
            }
        }
    }

     for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece* attacker = board[row][col];
            if (attacker != nullptr && attacker->isWhite() != whiteTurn) {
                if (attacker->isValidMove(row, col, kingRowPosition, kingColPosition, board)) {
                    return true; 
                }
            }
        }
    }

    return false;
}

bool Board::isCheckmate(){
    if(!isCheck(whiteTurn)) return false;

    for (int fromRow = 0; fromRow < 8; fromRow++) {
        for (int fromCol = 0; fromCol < 8; fromCol++) {
            Piece* piece = board[fromRow][fromCol];

            if (piece != nullptr && piece->isWhite() == isWhiteTurn()) {
                for (int toRow = 0; toRow < 8; toRow++) {
                    for (int toCol = 0; toCol < 8; toCol++) {
                        if (piece->isValidMove(fromRow, fromCol, toRow, toCol, board)) {
                            Piece* captured = board[toRow][toCol];
                            board[toRow][toCol] = piece;
                            board[fromRow][fromCol] = nullptr;

                            bool stillInCheck = isCheck(isWhiteTurn());

                            board[fromRow][fromCol] = piece;
                            board[toRow][toCol] = captured;

                            if (!stillInCheck) return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}

void Board::endGame(char winner) {
    cout << "\n===================== Game Over =====================" << endl;
    if (winner == 'W') {
        cout << "Congratulations! White wins the game! Well played!" << endl;
    } else{
        cout << "Congratulations! Black wins the game! Well played!" << endl;
    }
    cout << "========================================================" << endl;
}

Board::~Board(){
    for(int row = 0;row < 8;row++){
        for(int col = 0;col < 8;col++){
            delete board[row][col];
        }
    }
}