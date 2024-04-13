// Created by: James Ocampo
// github repo: https://github.com/KuyaJimbo/Project3_JumpingJim/tree/main

// Run with:
// g++ *.cpp -o jumpingjim
//          OR 
// g++ -std=c++11 -o jumpingjim *.cpp

// ./jumpingjim

#include <iostream> // For cin, cout
#include <fstream> // For ifstream (file input), ofstream (file output)
#include <vector> // For vector (dynamic array)
#include <cstdlib> // For exit (exit program)
#include <unordered_map> // For unordered_map (hash table)

#include <utility> // For pair (pair of values)

using namespace std;

// This Class represents a trampoline and stores the row and column of the Cell
class Cell {
public:
    int _key;
    int _row;
    int _col;
    char _direction;
    Cell(int key, int row, int col, char direction) : _key(key), _row(row), _col(col), _direction(direction) {}
};

// Depth First Search to find a path from the bottom right to the top left
bool dfs(unordered_map<int, bool>& visited, unordered_map<int, vector<Cell>>& adj_list, int key, int m, int n, vector<char>& path) { 
    // Get the row and column from the key
    int r = key / n;
    int c = key % n;

    // debug print
    // cout << "dfs @ " << r << ", " << c << endl;
    
    // Check if the current cell is the bottom-right cell
    if (r == m - 1 && c == n - 1) {
        // return true
        return true;
    }

    // Mark the current cell as visited
    visited[key] = true;

    // for each neighbor of the current cell
    for (Cell neighbor : adj_list[key]) {
        // Check if the neighbor cell has not been visited
        if (!visited[neighbor._key]) {
            // If dfs returns true, then the neighbor cell leads to the bottom-right cell
            if (dfs(visited, adj_list, neighbor._key, m, n, path)) {
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
    //      if matrix[2][2] = 2, then adj_list[key @ (2,2)] = {Cell(0, 2, 'R'), Cell(4, 2, 'L'), Cell(2, 0, 'D'), Cell(2, 4, 'U')}

    // adj_list is a hashtable with a key as the cell number and the value as the vector of neighbors of the cell
    unordered_map<int, vector<Cell>> adj_list;

    // define a key
    int key = 0;

    // iterate through the matrix and create the neighbors adjacency list
    for (int row = 0; row < m; ++row) {
        for (int col = 0; col < n; ++col) {

            // create the neighbors based on (row +/- matrix[row][col], col) and (row, col +/- matrix[row][col]) 
            int tightness = matrix[row][col];

            // directions are N, S, W, E and jumps are the row and column values to reach the neighbor cell
            vector<char> directions = {'N', 'S', 'W', 'E'};
            vector<int> jumps = {row - tightness, row + tightness, col - tightness, col + tightness};

            // add vertical neighbors
            for (int i = 0; i < 2; ++i) {
                // check if the row is within the matrix
                if (jumps[i] >= 0 && jumps[i] < m) { 
                    // calculate the key of the neighbor cell
                    int Nkey = jumps[i] * n + col;
                    // add the neighbor cell to the adjacency list
                    adj_list[key].push_back(Cell(Nkey, jumps[i], col, directions[i]));
                }
            }

            // add horizontal neighbors
            for (int i = 2; i < 4; ++i) {
                // check if the column is within the matrix
                if (jumps[i] >= 0 && jumps[i] < n) { 
                    // calculate the key of the neighbor cell
                    int Nkey = row * n + jumps[i];
                    // add the neighbor cell to the adjacency list
                    adj_list[key].push_back(Cell(Nkey, row, jumps[i], directions[i]));
                }
            }

            // increment the key
            ++key;
        }
    }

    // -------------- Display the Adjacency List --------------
    //display the adjacency list by iterating through keys starting from 0 to m*n
    // for (int i = 0; i < m*n; ++i) {
    //     cout << "(" << i << "): ";
    //     for (Cell neighbor : adj_list[i]) {
    //         cout << "(" << neighbor._key << ", " << neighbor._row << ", " << neighbor._col << ", " << neighbor._direction << ") ";
    //     }
    //     cout << endl;
    // }

    // -------------- Use DFS starting from the bottom right to find a path to the top left --------------

    // create a visited hashtable to keep track of the visited cells
    unordered_map<int, bool> visited;
    
    // path is a vector of the directions from the top left to the bottom right
    // it will be updated as the DFS finds the path
    vector<char> path;
    
    // start the DFS from the top left cell
    bool path_found = dfs(visited, adj_list, 0, m, n, path);

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
