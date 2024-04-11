Jumping Jim
-----------

Jumping Jim is a C++ program that finds a path from the bottom right of a matrix to the top left using Depth First Search (DFS). In this matrix, each cell contains a value indicating the maximum jump distance in four directions (North, South, West, East).

### How to Run

To compile and run the program, use the following commands in your terminal:
g++ *.cpp -o jumpingjim
- Or, if you encounter issues with C++11 features: g++ -std=c++11 -o jumpingjim *.cpp

Then, execute the compiled program:
./jumpingjim

### Input File

The program expects the input data to be provided in a file named `input.txt`. This file should contain:

- The number of rows `m` and columns `n` in the matrix.
- The matrix itself, where each cell contains a non-negative integer representing the maximum jump distance.

### Output File

The program outputs the result to a file named `output.txt`. If a path from the bottom right to the top left exists, the output file contains the sequence of directions (N, S, W, E) representing the path. If no such path exists, it prints "No path found".

### Code Structure

- **Cell Class**: Represents a cell in the matrix, storing its row, column, and the direction of the jump to reach that cell.
- **DFS Function**: Implements Depth First Search to find a path from the bottom right to the top left of the matrix.
- **Main Function**: Reads input from `input.txt`, constructs an adjacency list representing neighbors for each cell, performs DFS, and writes the result to `output.txt`.

### Example

For example, given the following input in `input.txt`:
7 7
3 6 4 3 2 4 3
2 1 2 3 2 5 2
2 3 4 3 4 2 3
2 4 4 3 4 2 2
4 5 1 3 2 5 4
4 3 2 2 4 5 6
2 5 2 5 6 1 0

The output in `output.txt` should be:
E S S N S W E N W E E W S E N W S E

This indicates a working path from the top right to the bottom left.

--- 
