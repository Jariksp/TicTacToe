
#include "tictactoe.h"

inline void TicTacToe::initBoard()
{
    board.resize(size, vector<CellState>(size, CellState::EMPTY));
}

TicTacToe::TicTacToe(int size, CellState playerSymbol) : size(size), playerSymbol(playerSymbol) {
    initBoard();
    botSymbol = (playerSymbol == CellState::CROSS) ? CellState::CIRCLE : CellState::CROSS;
}


void TicTacToe::play() {
    bool playerTurn = true;
    while (true) {
        printBoard();
        if (playerTurn) {
            playerMove();
        }
        else {
            botMove();
        }
        GameState gameState = getGameState();
        if (gameState == GameState::PLAYER_WIN) {
            printBoard();
            cout << "You win!\n";
            break;
        }
        else if (gameState == GameState::BOT_WIN) {
            printBoard();
            cout << "Bot wins!\n";
            break;
        }
        else if (gameState == GameState::DRAW) {
            printBoard();
            cout << "Draw!\n";
            break;
        }
        playerTurn = !playerTurn;
    }
}


GameState TicTacToe::getGameState() {
    // Check rows
    for (int i = 0; i < size; i++) {
        if (board[i][0] != CellState::EMPTY) {
            bool rowEqual = true;
            for (int j = 1; j < size; j++) {
                if (board[i][j] != board[i][j - 1]) {
                    rowEqual = false;
                    break;
                }
            }
            if (rowEqual) {
                return (board[i][0] == playerSymbol) ? GameState::PLAYER_WIN : GameState::BOT_WIN;
            }
        }
    }

    // Check columns
    for (int j = 0; j < size; j++) {
        if (board[0][j] != CellState::EMPTY) {
            bool colEqual = true;
            for (int i = 1; i < size; i++) {
                if (board[i][j] != board[i - 1][j]) {
                    colEqual = false;
                    break;
                }
            }
            if (colEqual) {
                return (board[0][j] == playerSymbol) ? GameState::PLAYER_WIN : GameState::BOT_WIN;
            }
        }
    }

    // Check diagonal from top-left to bottom-right
    if (board[0][0] != CellState::EMPTY) {
        bool diagonalEqual = true;
        for (int i = 1; i < size; i++) {
            if (board[i][i] != board[i - 1][i - 1]) {
                diagonalEqual = false;
                break;
            }
        }
        if (diagonalEqual) {
            return (board[0][0] == playerSymbol) ? GameState::PLAYER_WIN : GameState::BOT_WIN;
        }
    }

    // Check diagonal from top-right to bottom-left
    if (board[0][size - 1] != CellState::EMPTY) {
        bool diagonalEqual = true;
        for (int i = 1; i < size; i++) {
            if (board[i][size - 1 - i] != board[i - 1][size - i]) {
                diagonalEqual = false;
                break;
            }
        }
        if (diagonalEqual) {
            return (board[0][size - 1] == playerSymbol) ? GameState::PLAYER_WIN : GameState::BOT_WIN;
        }
    }

    // Check if board is full
    bool isFull = true;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == CellState::EMPTY) {
                isFull = false;
                break;
            }
        }
        if (!isFull) {
            break;
        }
    }
    if (isFull) {
        return GameState::DRAW;
    }

    return GameState::IN_PROGRESS;
}

void TicTacToe::printBoard() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == CellState::EMPTY)
                cout << ".";
            else if (board[i][j] == CellState::CROSS)
                cout << "X";
            else
                cout << "O";
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void TicTacToe::playerMove() {
    while (true) {
        cout << "Enter row and column (1-" << size << ") for your move: ";
        int row, col;
        cin >> row >> col;
        row--;
        col--;
        if (row < 0 || row >= size || col < 0 || col >= size) {
            cout << "Invalid input. Please enter a row and column within range.\n";
            continue;
        }
        if (board[row][col] != CellState::EMPTY) {
            cout << "That cell is already taken. Please choose another.\n";
            continue;
        }
        board[row][col] = playerSymbol;
        break;
    }
}


void TicTacToe::botMove() {
    // Check if bot symbol is already on the board
    bool symbolOnBoard = false;
    int symbolRow, symbolCol;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == botSymbol) {
                symbolOnBoard = true;
                symbolRow = i;
                symbolCol = j;
                break;
            }
        }
        if (symbolOnBoard) {
            break;
        }
    }

    // Make move
    if (symbolOnBoard) {
        // Make a random move
        vector<pair<int, int>> emptyCells;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == CellState::EMPTY) {
                    emptyCells.push_back(make_pair(i, j));
                }
            }
        }
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, emptyCells.size() - 1);
        int index = dis(gen);
        int row = emptyCells[index].first;
        int col = emptyCells[index].second;
        board[row][col] = botSymbol;
    }
    else {
        // Place bot symbol in center if possible
        if (board[size / 2][size / 2] == CellState::EMPTY) {
            board[size / 2][size / 2] = botSymbol;
        }
        else {
            // Place bot symbol in a random corner
            vector<pair<int, int>> corners = { make_pair(0, 0), make_pair(0, size - 1), make_pair(size - 1, 0), make_pair(size - 1, size - 1) };
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, corners.size() - 1);
            int index = dis(gen);
            int row = corners[index].first;
            int col = corners[index].second;
            board[row][col] = botSymbol;
        }
    }
}