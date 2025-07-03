#include <bits/stdc++.h>
#include "GameController.hpp"
using namespace std;

GameController::GameController(Board* board){
    this->board = board;
    this->whiteTurn = true;
}

void GameController::startGame(){
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


bool GameController::isWhiteTurn(){
    return whiteTurn;
}

void GameController::switchTurn(){
    whiteTurn = whiteTurn ? false : true;
}

void GameController::makeMove(){
    if(isWhiteTurn()) cout << "Turn : White" << endl;
    else cout << "Turn : Black" << endl;

    int fromRow,fromCol,toRow,toCol;

    Piece* currentPiece;

    char Lock = 'n';
    while(Lock == 'n'){
        while(true){
            cout << "Enter current row and current column of the desired piece (current row , current column) : ";
            cin >> fromRow >> fromCol;
            Piece* piece = board->getPieceAt(fromRow,fromCol);
            if(board->getPieceAt(fromRow,fromCol) == nullptr){
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
                board->setPieceAt(toRow,toCol, board->getPieceAt(fromRow,fromCol));
                board->setPieceAt(fromRow,fromCol, nullptr);
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
                board->setPieceAt(fromRow,fromCol, board->getPieceAt(toRow,toCol));
                board->setPieceAt(toRow,toCol, nullptr);
                Lock = confirm;
                break;
            }
            else continue;
        }
    }
}

void GameController::endGame(char winner) {
    cout << "\n===================== Game Over =====================" << endl;
    if (winner == 'W') {
        cout << "Congratulations! White wins the game! Well played!" << endl;
    } else{
        cout << "Congratulations! Black wins the game! Well played!" << endl;
    }
    cout << "========================================================" << endl;
}