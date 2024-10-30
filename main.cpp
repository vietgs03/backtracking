#include <iostream>
#include <string>

class SudokuClass {
public:
    static SudokuClass& getInstance() {
        static SudokuClass instance;
        return instance;
    }

    bool sudoku(int board[9][9]) {
        return solve(board, 0, 0);
    }

    void displayBoard(const int board[9][9]) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                std::cout << ";" << board[i][j];
                if ((j + 1) % 3 == 0 && j < 8) {
                    std::cout << ";//";
                }
            }
            std::cout << "\n";
            if ((i + 1) % 3 == 0 && i < 8) {
                std::cout << "=======//=======//======\n";
            }
        }
    }

    void inputBoard(int board[9][9], const std::string& input) {
        int row = 0, col = 0;
        for (char ch : input) {
            if (ch == '.') {
                board[row][col] = 0;
                col++;
            } else if (ch >= '1' && ch <= '9') {
                board[row][col] = ch - '0'; // Convert char to int
                col++;
            } else if (ch == '|') {
                continue; // Skip column dividers
            } else if (ch == '-') {
                continue; // Skip row dividers
            }
            if (col == 9) {
                col = 0;
                row++;
            }
        }
    }

private:
    SudokuClass() {}

    SudokuClass(const SudokuClass&) = delete;
    SudokuClass& operator=(const SudokuClass&) = delete;

    bool isValid(const int board[9][9], int row, int col, int num) {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == num || board[i][col] == num ||
                board[row / 3 * 3 + i / 3][col / 3 * 3 + i % 3] == num)
                return false;
        }
        return true;
    }

    bool solve(int board[9][9], int row, int col) {
        if (row == 9) return true;
        if (col == 9) return solve(board, row + 1, 0);

        if (board[row][col] != 0)
            return solve(board, row, col + 1);

        for (int num = 1; num <= 9; num++) {
            if (isValid(board, row, col, num)) {
                board[row][col] = num;
                if (solve(board, row, col + 1))
                    return true;
                board[row][col] = 0;
            }
        }
        return false;
    }
};

int main() {
    // Fixed input format
    std::string input = 
        ".5.1.4.|.8.6.9.|.7.2.3"
        ".8.7.2.|.3.4.5.|.6.1.9"
        ".9.6.3.|.2.1.7.|.5.4.8"
        "-------|-------|------"
        ".6.2.8.|.1.3.4.|.9.5.7"
        ".1.9.7.|.6.5.2.|.3.4.8"
        ".4.3.5.|.7.9.8.|.1.6.2"
        "-------|-------|------"
        ".2.4.6.|.9.7.1.|.3.8.5"
        ".7.5.1.|.4.8.3.|.2.9.6"
        ".3.8.9.|.5.2.6.|.4.7.1";

    int board[9][9];
    SudokuClass& solver = SudokuClass::getInstance();

    solver.inputBoard(board, input);

    std::cout << "The entered Sudoku board is:\n";
    solver.displayBoard(board);

    if (solver.sudoku(board)) {
        std::cout << "\nSolved Sudoku board:\n";
        solver.displayBoard(board);
    } else {
        std::cout << "\nNo solution exists for the given Sudoku board.\n";
    }

    return 0;
}
