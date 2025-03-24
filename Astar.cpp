#include "Astar.h"
#include "PuzzleState.h"

//priority_queue<PuzzleState, vector<PuzzleState>, ComparePuzzleState> openList;

priority_queue<pair<PuzzleState, pair<int, int>>, vector<pair<PuzzleState, pair<int,int>>>, ComparePuzzleState> openList;

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

// void Astar (const PuzzleState& startState, const PuzzleState& goalState) {
//     set<vector<int>> visited;    // stores the visited state's tiles in order
//     vector<PuzzleState> nextStates;
//     //vector<pair<PuzzleState, MoveType>> nextStates;

//     if (startState == goalState) {
//         cout << "Start state is the goal state." << endl;
//         return;
//     }

//     PuzzleState start = startState;
//     start.setG(0);
//     start.setF(manhattanDistance(start, goalState));
//     openList.push(start);

//     PuzzleState currState;

//     while(true) {
//         currState = openList.top();
//         openList.pop();

//         if (currState.getTiles() == goalState.getTiles()) {
//             cout << "Current State: " << endl << endl;
//             cout << currState << endl;
//             return;
//         }

//         visited.insert(currState.getTiles());
//         nextStates = {currState.moveBlankDown(),
//                       currState.moveBlankLeft(),
//                       currState.moveBlankRight(),
//                       currState.moveBlankUp()};

//         for (auto& state : nextStates) {
//             if (state == currState) continue;

//             if (visited.find(state.getTiles()) == visited.end()) {
//                 state.setG(state.getG() + 1);
//                 state.setF(state.getG() + manhattanDistance(state, goalState));
//                 openList.push(state);
//             }
//         }
//     }
// }


int printPath(const set<PuzzleMove>& moves, const PuzzleMove& finalMove) {
    vector<PuzzleMove> path;
    PuzzleMove currMove = finalMove;

    while (!(currMove.getState() == startState)) {
        path.push_back(currMove);

        auto it = find_if(moves.begin(), moves.end(),
            [&currMove](const PuzzleMove& m) {
                return m.getState() == currMove.getParent();
            });

        if (it == moves.end()) {
            cerr << "Error: could not find parent in path." << endl;
            break;
        }

        currMove = *it;
    }

    // Push start node
    path.push_back(PuzzleMove(startState, startState, nullMove));

    reverse(path.begin(), path.end());

    for (const auto& node : path) {
        switch (node.getMoveName()) {
            case MoveType::down:
                cout << "down";
                break;
            case MoveType::left:
                cout << "left";
                break;
            case MoveType::right:
                cout << "right";
                break;
            case MoveType::up:
                cout << "up";
                break;
            default:
                break;
        }
        cout << endl << endl << endl;
        cout << node.getState() << endl << endl;
    }

    return path.size() - 1;
}

void Astar (const PuzzleState& startState, const PuzzleState& goalState) {
    set<pair<PuzzleState, pair<int, int>>> openListSet;
    set<pair<PuzzleState, pair<int, int>>> closedList;
    set<PuzzleMove> moves;
    vector<pair<pair<PuzzleState, pair<int, int>>, MoveType>> successors;

    openListSet.insert({startState, {0, 0}});
    openList.push({startState, {0, 0}});


    while(!openList.empty()) {
        pair<PuzzleState, pair <int, int>> currState = openList.top();
        openListSet.erase(currState);
        openList.pop();

        successors = {
            {{currState.first.moveBlankDown(), {currState.second.first, currState.second.second}}, MoveType::down},
            {{currState.first.moveBlankLeft(), {currState.second.first, currState.second.second}}, MoveType::left},
            {{currState.first.moveBlankRight(), {currState.second.first, currState.second.second}}, MoveType::right},
            {{currState.first.moveBlankUp(), {currState.second.first, currState.second.second}}, MoveType::up}
        };

        for (auto &successor : successors) {
            PuzzleMove move;
            if (successor.first.second.first == 0) {
                move = PuzzleMove(successor.first.first, startState, successor.second);
                moves.insert(move);
            }
            else {
                move = PuzzleMove(successor.first.first, currState.first, successor.second);
                moves.insert(move);
            }

            if (successor.first.first == goalState) {
                cout << "\nSolution:" << endl;
                PuzzleMove finalMove = move;
                // call the printPath function with finalMove as the parameter
                int length = printPath(moves, finalMove);
                cout << "Steps to goal: " << length << endl;
                return;
            }
            else {
                int g = currState.second.first + 1;
                int h = manhattanDistance(successor.first.first, goalState);
                int f = g + h;
                successor.first.second.first = g;
                successor.first.second.second = f;

                // current puzzle state excluding g and f values
                PuzzleState currNode = successor.first.first;
                bool skip = false;
                for (auto it = openListSet.begin(); it != openListSet.end(); ++it) {
                    if ((*it).first == currNode && (*it).second.second <= successor.first.second.second) {
                        skip = true;
                        break;
                    }
                }
                for (auto it = closedList.begin(); it != closedList.end(); ++it) {
                    if ((*it).first == currNode && (*it).second.second <= successor.first.second.second) {
                        skip = true;
                        break;
                    }
                }
                if (!skip) {
                        openList.push(successor.first);
                        openListSet.insert(successor.first);
                    }
            }
        }
        closedList.insert(currState);
    }
}



