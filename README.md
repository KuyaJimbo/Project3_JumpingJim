
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

