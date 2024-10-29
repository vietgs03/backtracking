#include <iostream>

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
                std::cout << board[i][j] << " ";
                if ((j + 1) % 3 == 0 && j < 8) {
                    std::cout << "| ";
                }
            }
            std::cout << "\n";
            if ((i + 1) % 3 == 0 && i < 8) {
                std::cout << "------+-------+------\n";
            }
        }
    }

    void inputBoard(int board[9][9]) {
        std::cout << "Please enter the Sudoku board (use 0 for empty cells):\n";
        for (int i = 0; i < 9; i++) {
            std::cout << "Enter row " << i + 1 << " (9 numbers separated by space): ";
            for (int j = 0; j < 9; j++) {
                std::cin >> board[i][j];
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
    int board[9][9];

    SudokuClass& solver = SudokuClass::getInstance();

    solver.inputBoard(board);

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
