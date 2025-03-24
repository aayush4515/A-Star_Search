#include "Astar.h"

//priority_queue<PuzzleState, vector<PuzzleState>, ComparePuzzleState> openList;

priority_queue<pair<PuzzleState, MoveType>, vector<pair<PuzzleState, MoveType>>, ComparePuzzleState> openList;

int printPath(PuzzleMove* move) {
    vector<PuzzleMove*> path;               // stores the path from current move upto the root move
    // store the path
    while (move != nullptr) {
        path.push_back(move);
        move = move->getParent();
    }

    // reverse the path for printing
    reverse(path.begin(), path.end());

    // print the path
    cout << "\nSolution:" << endl;
    for (const auto& node : path) {
        int i = node->getMoveName();
        string moveName = "";
        switch (i) {
            case 0:
                moveName = "down";
                break;
            case 1:
                moveName = "left";
                break;
            case 2:
                moveName = "right";
                break;
            case 3:
                moveName = "up";
                break;
            default:
                break;
        }
        cout << moveName << endl << endl;
        cout << node->getState() << endl;
    }
    return path.size() - 1;
}


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
    //vector<PuzzleState> nextStates;
    vector<pair<PuzzleState, MoveType>> nextStates;

    if (startState == goalState) {
        cout << "Start state is the goal state." << endl;
        return;
    }

    PuzzleState start = startState;
    start.setG(0);
    start.setF(manhattanDistance(start, goalState));
    openList.push({start, nullMove});

    PuzzleMove* rootMove = new PuzzleMove(startState, nullptr, nullMove);
    PuzzleMove* currMove = rootMove;

    PuzzleState currState;

    while(true) {
        currState = openList.top().first;
        MoveType currMoveType = openList.top().second;
        openList.pop();

        if (currState.getTiles() == goalState.getTiles()) {
            int pathLength = printPath(currMove);
            cout << "Steps to goal: " << pathLength << endl;
            cout << "Current State: " << endl << endl;
            cout << currState << endl;
            return;
        }

        visited.insert(currState.getTiles());
        nextStates = {{currState.moveBlankDown(), MoveType::down},
                      {currState.moveBlankLeft(), MoveType::left},
                      {currState.moveBlankRight(), MoveType::right},
                      {currState.moveBlankUp(), MoveType::up}};

        for (auto& state : nextStates) {
            if (state.first == currState) continue;

            if (visited.find(state.first.getTiles()) == visited.end()) {
                state.first.setG(state.first.getG() + 1);
                state.first.setF(state.first.getG() + manhattanDistance(state.first, goalState));
                openList.push(state);
            }
        }
    }
}




