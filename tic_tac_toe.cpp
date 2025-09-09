#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

class Game {
    enum class Player { none = '-', human = 'X', computer = 'O' };
    struct Move { unsigned int x = 0; unsigned int y = 0; };
    Player board[3][3];

public:
    Game() {
        for (unsigned int i = 0; i < 3; i++) {
            for (unsigned int j = 0; j < 3; j++) {
                board[i][j] = Player::none;
            }
        }
    }

    void printBoard() {
        cout << "+-----------------+";
        for (unsigned int i = 0; i < 3; i++) {
            cout << "\n|";
            for (unsigned int j = 0; j < 3; j++) {
                cout << setw(3) << static_cast<char>(board[i][j]) << setw(3) << " |";
            }
        }
        cout << "\n+-----------------+\n";
    }

    bool isTie() {
        for (unsigned int i = 0; i < 3; i++) {
            if (board[i][0] == Player::none || board[i][1] == Player::none || board[i][2] == Player::none)
                return false;
        }
        return true;
    }

    bool checkWin(Player player) {
        for (unsigned int i = 0; i < 3; i++) {
            // Check horizontals
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
            // Check verticals
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
        }
        // Check diagonals
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
        return false;
    }

    Move minimax() {
        int score = numeric_limits<int>::max();
        Move move;
        for (unsigned int i = 0; i < 3; i++) {
            for (unsigned int j = 0; j < 3; j++) {
                if (board[i][j] == Player::none) {
                    board[i][j] = Player::computer;
                    int temp = maxSearch();
                    if (temp < score) {
                        score = temp;
                        move.x = i;
                        move.y = j;
                    }
                    board[i][j] = Player::none;
                }
            }
        }
        return move;
    }

    int maxSearch() {
        if (checkWin(Player::human)) return 10;
        else if (checkWin(Player::computer)) return -10;
        else if (isTie()) return 0;

        int score = numeric_limits<int>::min();

        for (unsigned int i = 0; i < 3; i++) {
            for (unsigned int j = 0; j < 3; j++) {
                if (board[i][j] == Player::none) {
                    board[i][j] = Player::human;
                    score = max(score, minSearch());
                    board[i][j] = Player::none;
                }
            }
        }
        return score;
    }

    int minSearch() {
        if (checkWin(Player::human)) return 10;
        else if (checkWin(Player::computer)) return -10;
        else if (isTie()) return 0;

        int score = numeric_limits<int>::max();

        for (unsigned int i = 0; i < 3; i++) {
            for (unsigned int j = 0; j < 3; j++) {
                if (board[i][j] == Player::none) {
                    board[i][j] = Player::computer;
                    score = min(score, maxSearch());
                    board[i][j] = Player::none;
                }
            }
        }
        return score;
    }

    void play() {
        bool playing = true;
        printBoard();

        while (playing) {
            unsigned int x = 0, y = 0;

            cout << "Enter x: ";
            cin >> x;
            cout << "Enter y: ";
            cin >> y;

            if (board[x][y] != Player::none || x > 2 || y > 2) {
                cout << "Invalid input\n";
                continue;
            }

            board[x][y] = Player::human;
            printBoard();

            if (checkWin(Player::human)) {
                cout << "Human wins!\n";
                playing = false;
                break;
            } else if (isTie()) {
                cout << "Tie game\n";
                playing = false;
                break;
            }

            Move ai_move = minimax();
            board[ai_move.x][ai_move.y] = Player::computer;
            printBoard();

            if (checkWin(Player::computer)) {
                cout << "Computer wins!\n";
                playing = false;
            } else if (isTie()) {
                cout << "Tie game\n";
                playing = false;
            }
        }
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}