#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

enum class CellState {
    EMPTY, CROSS, CIRCLE
};

enum class GameState {
    IN_PROGRESS, PLAYER_WIN, BOT_WIN, DRAW
};

class TicTacToe {
private:
    const int size;
    vector<vector<CellState>> board; 
    CellState playerSymbol, botSymbol;

public:
    TicTacToe(int size, CellState playerSymbol);
    void initBoard();
    void play();
    void printBoard();
    GameState getGameState();
    void playerMove();
    void botMove();

};
