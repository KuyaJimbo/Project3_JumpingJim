// Created by: James Ocampo

// Run with:
// g++ *.cpp -o jumpingjim
//          OR 
// g++ -std=c++11 -o jumpingjim *.cpp

// ./jumpingjim

#include <iostream> // For cin, cout
#include <fstream> // For ifstream (file input), ofstream (file output)
#include <vector> // For vector (dynamic array)
#include <cstdlib> // For exit (exit program)

using namespace std;

// This Class represents a trampoline and stores the row and column of the Cell and Direction of the jump to reach that Cell
class Cell {
public:
    int _row;
    int _col;
    char _direction;
    Cell(int row, int col, char direction) : _row(row), _col(col), _direction(direction) {}
};

// Depth First Search to find a path from the bottom right to the top left
bool dfs(int r, int c, int m, int n, vector<vector<vector<Cell>>>& adj_list, vector<char>& path, vector<vector<bool>>& visited) {
    // debug print
    // cout << "dfs(" << r << ", " << c << ")" << endl;

    // Check if the current cell is the bottom-right cell
    if (r == m && c == n) {
        return true;
    }

    // Mark the current cell as visited
    visited[r][c] = true;

    for (Cell neighbor : adj_list[r][c]) {
        // Check if the neighbor cell is valid and has not been visited
        if (!visited[neighbor._row][neighbor._col]) {
            if (dfs(neighbor._row, neighbor._col, m, n, adj_list, path, visited)) {
                // If the neighbor cell leads to the bottom-right cell, append the direction to the path
                path.push_back(neighbor._direction);
                return true;
            }
        }
    }

    // all neighbors searched but none led to the bottom-right goal cell
    return false;
}




int main() {
    // ----------------- Set up the input file -----------------
    ifstream inputFile("input.txt");
    
    // Check if the file is opened successfully
    if (!inputFile) {
        cout << "Unable to open file input.txt" << endl;
        exit(1);
    }

    // -------------- Set up the output file --------------
    ofstream outputFile("output.txt");

    // -------------- Read the input from the file --------------
    int m; // Number of rows in the matrix
    int n; // Number of columns in the matrix

    // First two integers from inputFile are read as m, and n for rows and columns
    inputFile >> m >> n;
    
    // matrix is a 2D vector m rows and n columns storing the matrix values
    vector<vector<int>> matrix(m, vector<int>(n));
    // The next m*n integers in the inputFile are stored in the matrix vector
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> matrix[i][j];
        }
    }

    // -------------- Close the Input File --------------
    inputFile.close();

    // -------------- Create the Adjacency List (Each possible adjacent cells holds its row, column, and direction to reach the cell) --------------
    // This adjacency list stores the neighbors of each cell in the matrix so that each key is accessed in O(1) time and
    // the neighbors of the cell present in the matrix[row][col] can be accessed in O(deg(v)) time or at most O(4) time
    //      Example Entry:
    //      if matrix[0][0] = 2, then adj_list[2][2] = {Cell(0, 2, 'R'), Cell(4, 2, 'L'), Cell(2, 0, 'D'), Cell(2, 4, 'U')}
    vector<vector<vector<Cell>>> adj_list(m, vector<vector<Cell>>(n));

    // iterate through the matrix and create the neighbors adjacency list
    for (int row = 0; row < m; ++row) {
        for (int col = 0; col < n; ++col) {
            
            // create the neighbors based on (row +/- matrix[row][col], col) and (row, col +/- matrix[row][col]) 
            // if they are within the bounds of the matrix
            int tightness = matrix[row][col];

            vector<char> directions = {'N', 'S', 'W', 'E'};

            vector<int> jumps = {row - tightness, row + tightness, col - tightness, col + tightness};

            // add vertical neighbors
            for (int i = 0; i < 2; ++i) {
                if (jumps[i] >= 0 && jumps[i] < m) { // check if the row is within the matrix
                    adj_list[row][col].push_back(Cell(jumps[i], col, directions[i]));
                }
            }
            // add horizontal neighbors
            for (int i = 2; i < 4; ++i) {
                if (jumps[i] >= 0 && jumps[i] < n) { // check if the column is within the matrix
                    adj_list[row][col].push_back(Cell(row, jumps[i], directions[i]));
                }
            }
        }
    }

    // -------------- Display the Adjacency List --------------
    // hashtable[row][col] (tight = matrix[row][col]) = {[row1, col1, direction1], [row2, col2, direction2], ...}
    // for (int row = 0; row < m; ++row) {
    //     for (int col = 0; col < n; ++col) {
    //         cout << "adj_list[" << row << "][" << col << "] (tight = " << matrix[row][col] << ") = {";
    //         for (int i = 0; i < adj_list[row][col].size(); ++i) {
    //             cout << "[" << adj_list[row][col][i]._row << ", " << adj_list[row][col][i]._col << ", " << adj_list[row][col][i]._direction << "], ";
    //         }
    //         cout << "}" << endl;
    //     }
    // }

    // -------------- Use DFS starting from the bottom right to find a path to the top left --------------

    // create a visited matrix to keep track of the visited cells
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    
    // path is a vector of the directions from the top left to the bottom right
    // it will be updated as the DFS finds the path
    vector<char> path;
    
    // start the DFS from the top left cell
    bool path_found = dfs(0, 0, m-1, n-1, adj_list, path, visited);

    // -------------- Write the output to the output file --------------
    // Write the path to the output file
    if (path_found) {
        for (int i = path.size() - 1; i >= 0; --i) {
            outputFile << path[i] << " ";
        }
    } else {
        outputFile << "No path found";
    }

    // -------------- Close the Output File --------------
    outputFile.close();
}
