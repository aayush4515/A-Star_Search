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

// first int is g, second int is f
struct ComparePuzzleState {
     bool operator()(const pair<PuzzleState, pair<int, int>>& a, const pair<PuzzleState, pair<int, int>>& b) const {
         return a.second.second > b.second.second;
     }
};

// create a min-heap priority queue named openList
extern priority_queue<pair<PuzzleState, pair<int, int>>, vector<pair<PuzzleState, pair<int, int>>>, ComparePuzzleState> openList;

// computes the Manhattan Distance for a single tile
int singleTileManhattanDistance (const PuzzleState& currState, const PuzzleState& goalState, const int currTileIndex);

// implement the function to calculate Manhattan distance
int manhattanDistance (const PuzzleState& currState, const PuzzleState& goalState);

// the A* search
void Astar (const PuzzleState& startState, const PuzzleState& goalState);

#endif