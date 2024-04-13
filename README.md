Jumping Jim
-----------
This project revolves around the "Jumping Jim" maze problem, a challenging puzzle where Jumping Jim navigates through a maze of trampolines, each marked with a number indicating the distance Jim will move when bouncing off it in adjacent directions (N, S, W, E). The goal is for Jim to traverse from the upper left corner to the lower right corner of the maze.

I solved this by modeling the problem as a graph with an adjacency list representation and using a DFS algorithm to search for the path to the bottom right corner.

0) Create a Cell object which represents a reachable Trampoline and keeps track of that trampoline's id, row, column, and direction to reach the column.
1) Create a 2D Matrix based on the input to represent the maze of trampolines. 
2) Create an adjacency list hashtable using a key-value pair of int (id/key) and list of reachable trampolines as Cell objects.
3) Populate the adjacency list by first assigning a id/key to a trampoline and adding the reachable neighbors as Cell objects to its neighbor list onto the adjacency list.
4) Create a visited hashtable using a key-valye pair of int (id/key) and a boolean (if visited?) to improve time complexity with dynamic programming while using DFS.
   - This is better than a matrix as it mitigates space cost if trampolines are unreachable (will never be visited)
5) Create a 2D char list called path to keep track of the path from the start to end.
6) Run DFS starting from the top left corner of the matrix (id=0) and consider all of its neighbors and their neighbors and so on until a path to the bottom right is found.
   - This demonstrates the benefit of using an adjacency list since only the true neighbors are considered with a faster lookup time.
   - After finding the bottom-right goal square (base case), each DFS call leading up to it adds the move required to the back of the path list and returns true to denote a pass was found.
8) Finally, the path will be stored in the path list and simply needs to be written onto the output file.

### How to Run

To compile and run the program, use the following commands in your terminal:<br />
**g++ \*.cpp -o jumpingjim**
- Or, if you encounter issues with C++11 features:
  **g++ -std=c++11 -o jumpingjim \*.cpp**

Then, execute the compiled program:<br />
**./jumpingjim**

### Input File

The program expects the input data to be provided in a file named `input.txt`. This file should contain:

- The number of rows `m` and columns `n` in the matrix.
- The matrix itself, where each cell contains a non-negative integer representing the maximum jump distance.
- For example, given the following input in `input.txt`:<br />
7 7<br />
3 6 4 3 2 4 3<br />
2 1 2 3 2 5 2<br />
2 3 4 3 4 2 3<br />
2 4 4 3 4 2 2<br />
4 5 1 3 2 5 4<br />
4 3 2 2 4 5 6<br />
2 5 2 5 6 1 0<br />

### Output File

The program outputs the result to a file named `output.txt`. If a path from the bottom right to the top left exists, the output file contains the sequence of directions (N, S, W, E) representing the path. If no such path exists, it prints "No path found".

The output in `output.txt` for the input.txt above should be:<br />
E S S N S W E N W E E W S E N W S E<br />

This indicates a working path from the top right to the bottom left.

### Code Structure

- **Cell Class**: Represents a cell in the matrix, storing its row, column, and the direction of the jump to reach that cell.
- **DFS Function**: Implements Depth First Search to find a path from the bottom right to the top left of the matrix.
- **Main Function**: Reads input from `input.txt`, constructs an adjacency list representing neighbors for each cell, performs DFS, and writes the result to `output.txt`.

--- 
