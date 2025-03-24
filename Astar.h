#ifndef _ASTAR_
#define _ASTAR_

#include "PuzzleMove.h"
#include "PuzzleState.h"
#include <iostream>
#include <queue>
#include <functional>
#include <cmath>
#include <set>
#include <map>


using namespace std;

// create a min-heap priority queue
// create a custom bool operator to sort the states by f(n) when pushed into the queue
// initialize an infinite loop: while(true) and it would break when the goal is found
// implement a function to calculate Manhattan distance


// create a custom bool operator to sort the states by f(n) when pushed into the queue
//bool operator>(const PuzzleState& currState, const PuzzleState& goalState);

int printPath(PuzzleMove* move);

// struct ComparePuzzleState {
//     bool operator()(const pair<PuzzleState, MoveType>& a, const pair<PuzzleState, MoveType>& b) const {
//         return a.first.getF() > b.first.getF(); // use the PuzzleState part of the pair
//     }
// };

struct ComparePuzzleState {
     bool operator()(const PuzzleState& a, const PuzzleState& b) const {
         return a.getF() > b.getF(); // use the PuzzleState part of the pair
     }
};

// create a min-heap priority queue named openList
extern priority_queue<PuzzleState, vector<PuzzleState>, ComparePuzzleState> openList;
//extern priority_queue<pair<PuzzleState, MoveType>, vector<pair<PuzzleState, MoveType>>, ComparePuzzleState> openList;

// computes the Manhattan Distance for a single tile
int singleTileManhattanDistance (const PuzzleState& currState, const PuzzleState& goalState, const int currTileIndex);

// implement the function to calculate Manhattan distance
int manhattanDistance (const PuzzleState& currState, const PuzzleState& goalState);

// the A* search
void Astar (const PuzzleState& startState, const PuzzleState& goalState);

#endif