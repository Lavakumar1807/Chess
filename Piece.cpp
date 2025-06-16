#include<bits/stdc++.h>
#include "Piece.hpp"

using namespace std;

Piece::Piece(bool isWhite){
    this->white = isWhite;
}

bool Piece::isWhite(){
    return white;
}

char Piece::getSymbol(){
    return symbol;
}

void Piece::setSymbol(char symbol){
    this->symbol = symbol;
}

bool Piece::isMoved(){
   return moved;
}

void Piece::setMoved(bool moved){
    this->moved = moved;
}