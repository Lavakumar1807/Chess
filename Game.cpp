#include<bits/stdc++.h>
#include "Board.hpp"
#include "GameController.hpp"
#include "RuleChecker.hpp"

using namespace std;

int main(){
    Board* chessBoard = new Board();
    GameController gameController(chessBoard);
    RuleChecker ruleChecker;

    gameController.startGame();
    chessBoard->displayBoard();

    while(true){
        gameController.makeMove();
        gameController.switchTurn();

        bool turn = gameController.isWhiteTurn();

        if(ruleChecker.isCheckmate(chessBoard,turn)){
            chessBoard->displayBoard();
            char winner = gameController.isWhiteTurn() ? 'B' : 'W';
            gameController.endGame(winner);
            break;
        }

        chessBoard->displayBoard();
    }

    return 0;
}