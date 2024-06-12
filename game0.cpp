#include <iostream>
#include <vector>

const int BOARD_SIZE = 3;

enum class Player { X, O, None };

struct Move {
    int row;
    int col;
};

class TicTacToe {
private:
    std::vector<std::vector<Player>> board;

public:
    TicTacToe() : board(BOARD_SIZE, std::vector<Player>(BOARD_SIZE, Player::None)) {}

    void displayBoard() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == Player::None) {
                    std::cout << "-";
                } else if (board[i][j] == Player::X) {
                    std::cout << "X";
                } else {
                    std::cout << "O";
                }
                std::cout << " ";
            }
            std::cout << "\n";
        }
    }

    bool makeMove(const Move& move, Player player) {
        if (move.row < 0 || move.row >= BOARD_SIZE || move.col < 0 || move.col >= BOARD_SIZE ||
            board[move.row][move.col] != Player::None) {
            return false;
        }

        board[move.row][move.col] = player;
        return true;
    }

    bool checkWin(Player player) {
        // Check rows
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
                return true;
            }
        }

        // Check diagonals
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
            return true;
        }
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
            return true;
        }

        return false;
    }
};

int main() {
    TicTacToe game;
    Player currentPlayer = Player::X;

    for (int turn = 0; turn < BOARD_SIZE * BOARD_SIZE; ++turn) {
        game.displayBoard();
        std::cout << "Player " << (currentPlayer == Player::X ? "X" : "O") << ", enter row and column (0-2): ";
        int row, col;
        std::cin >> row >> col;

        Move move = {row, col};
        if (game.makeMove(move, currentPlayer)) {
            if (game.checkWin(currentPlayer)) {
                game.displayBoard();
                std::cout << "Player " << (currentPlayer == Player::X ? "X" : "O") << " wins!\n";
                return 0;
            }
            currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
        } else {
            std::cout << "Invalid move. Try again.\n";
            --turn; // Re-do this turn
        }
    }

    std::cout << "It's a draw!\n";

    return 0;
}
