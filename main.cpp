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
    PuzzleState startState = PuzzleState(numRowsCols, numRowsCols);
    PuzzleState goalState = PuzzleState(numRowsCols, numRowsCols);

    cout << "Enter Start State row by row: ";
    cin >> startState;

    cout << "\nEnter Goal State row by row: ";
    cin >> goalState;

    // call A*
    Astar(startState, goalState);

    return 0;
}