#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "tictactoe.h"
using namespace std;

int main() {
    cout << "Welcome to Tic Tac Toe!\n";
    cout << "Enter board size (minimum 3): ";
    int size;
    cin >> size;
    if (size < 3) {
        cout << "Invalid size. Board size set to 3.\n";
        size = 3;
    }
    cout << "Do you want to play as X or O? ";
    char symbol;
    cin >> symbol;
    symbol = toupper(symbol);
    if (symbol == 'X') {
        TicTacToe game(size, CellState::CROSS);
        game.play();
    }
    else if (symbol == 'O') {
        TicTacToe game(size, CellState::CIRCLE);
        game.play();
    }
    else {
        cout << "Invalid symbol. Default symbol set to X.\n";
        TicTacToe game(size, CellState::CROSS);
        game.play();
    }
    return 0;
}