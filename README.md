- Using Singleton Design pattern

- The primary functionality of the class is to solve a Sudoku puzzle using a **backtracking algorithm.**

```solve()``` method :

- The method works cell-by-cell, starting at ```(0,0)```and moving through the entrie grid.

- If a cell is empty (i.e. , it containts ```0```), the algorithm tries to place numbers violates sudoku rule (row,column, or 3x3 subgrid)

- If a valid number is found, it place the number in the cell and recursively attempts to solve the next cells.

- If no number fits, it backtracks by resetting the cell to ```0``` and trying a different number in the previous cells.

```isValid``` method : 

- It checks the current row, column, and 3x3 subgrid to ensure no duplicate numbers exist.