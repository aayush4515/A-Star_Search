#include <iostream>
#include "PuzzleState.h"
#include "PuzzleMove.h"
#include "Astar.h"
#include <vector>
using namespace std;

int main() {

    // Project Description
    cout << "*** P01 Puzzle Uninformed Search - BFS ***" << endl;
    cout << "< ======================================================== >" << endl << endl;

    // identifiers
    int numRowsCols;

    // Input # of rows and columns
    cout << "Enter number of rows and columns: ";
    cin >> numRowsCols;
    cout << endl;

    // initialize the start state and goal state
    startState = PuzzleState(numRowsCols, numRowsCols);
    goalState = PuzzleState(numRowsCols, numRowsCols);

    cout << "Enter Start State row by row: ";
    cin >> startState;

    cout << "\nEnter Goal State row by row: ";
    cin >> goalState;

    // // print the num rows and cols, start state and the goal state after user input
    // cout << "Number of rows and columns: " << numRowsCols << endl;
    // cout << "Start State:" << endl;
    // cout << startState << endl;
    // cout << "Goal state:" << endl;
    // cout << goalState << endl;

    // call A*
    Astar(startState, goalState);

    // // print out the Mahhattan Distance for checking
    // cout << "Manhattan Distance is: " << manhattanDistance(startState, goalState) << endl;

    return 0;
}