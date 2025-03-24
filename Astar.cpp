#include "Astar.h"

priority_queue<PuzzleState, vector<PuzzleState>, ComparePuzzleState> openList;

//priority_queue<pair<PuzzleState, MoveType>, vector<pair<PuzzleState, MoveType>>, ComparePuzzleState> openList;

int singleTileManhattanDistance (const PuzzleState& currState, const PuzzleState& goalState, const int currTileIndex) {
    int distance = 0;

    // find goal position of the tile
    int currTile = currState.getCurrTile(currTileIndex);
    int goalIndex = goalState.getTileIndex(currTile);

    // tile 0 is not considered--it's the blank; return the distance as 0
    if (currTile == 0) {
        return 0;
    }

    // curr position
    int currRow = currTileIndex / currState.getNumRows();
    int currCol = currTileIndex % currState.getNumCols();

    // goal position
    int goalRow = goalIndex / goalState.getNumRows();
    int goalCol = goalIndex % goalState.getNumCols();

    // calculate distance;
    distance = abs(currRow - goalRow) + abs(currCol - goalCol);

    return distance;
}

int manhattanDistance (const PuzzleState& currState, const PuzzleState& goalState) {
    int manhattanDistance = 0;
    for (int i = 0; i < currState.getTilesSize(); i++) {
        manhattanDistance += singleTileManhattanDistance(currState, goalState, i);
    }
    return manhattanDistance;
}

void Astar (const PuzzleState& startState, const PuzzleState& goalState) {
    set<vector<int>> visited;    // stores the visited state's tiles in order
    vector<PuzzleState> nextStates;
    //vector<pair<PuzzleState, MoveType>> nextStates;

    if (startState == goalState) {
        cout << "Start state is the goal state." << endl;
        return;
    }

    PuzzleState start = startState;
    start.setG(0);
    start.setF(manhattanDistance(start, goalState));
    openList.push(start);

    PuzzleState currState;

    while(true) {
        currState = openList.top();
        openList.pop();

        if (currState.getTiles() == goalState.getTiles()) {
            cout << "Current State: " << endl << endl;
            cout << currState << endl;
            return;
        }

        visited.insert(currState.getTiles());
        nextStates = {currState.moveBlankDown(),
                      currState.moveBlankLeft(),
                      currState.moveBlankRight(),
                      currState.moveBlankUp()};

        for (auto& state : nextStates) {
            if (state == currState) continue;

            if (visited.find(state.getTiles()) == visited.end()) {
                state.setG(state.getG() + 1);
                state.setF(state.getG() + manhattanDistance(state, goalState));
                openList.push(state);
            }
        }
    }
}




