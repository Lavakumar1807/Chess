#include<bits/stdc++.h>
#include "Board.hpp"

using namespace std;

int main(){
    Board chessBoard;
    chessBoard.startGame();
    chessBoard.displayBoard();

    while(true){
        chessBoard.makeMove();
        chessBoard.switchTurn();

        if(chessBoard.isCheckmate()){
            chessBoard.displayBoard();
            char winner = chessBoard.isWhiteTurn() ? 'B' : 'W';
            chessBoard.endGame(winner);
            break;
        }

        chessBoard.displayBoard();
    }

    return 0;
}