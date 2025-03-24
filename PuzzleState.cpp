#include "PuzzleState.h"
#include "Astar.h"

int numRowsCols = 0;
PuzzleState startState(0, 0);
PuzzleState goalState(0, 0);

// equal operator definition
bool PuzzleState::operator==(const PuzzleState & rhs) const {
     return (this->rows == rhs.rows) &&
     (this->cols == rhs.cols) &&
     (this->tiles == rhs.tiles) &&
     (this->blank_position_row == rhs.blank_position_row) &&
     (this->blank_position_col == rhs.blank_position_col);
}

// not-equal op definition
bool PuzzleState::operator!=(const PuzzleState & rhs) const {
return !(*this == rhs);
}

// assignment op definition
const PuzzleState & PuzzleState::operator=( const PuzzleState & rhs ) {
    if (*this != rhs) {          // checking for self-assignment
        this->rows = rhs.rows;
        this->cols = rhs.cols;
        this->tiles = rhs.tiles;
        this->blank_position_row = rhs.blank_position_row;
        this->blank_position_col = rhs.blank_position_col;
    }
    return *this;
}

// getters

int PuzzleState::getTileIndex (int tile) const {
    auto it = find(tiles.begin(), tiles.end(), tile);
    return distance(tiles.begin(), it);
}
// return a tile at the index i
int PuzzleState::getCurrTile(int i) const {
    return tiles.at(i);
}
// get the vector size
int PuzzleState::getTilesSize () const {
    return tiles.size();
}

// get the number of rows and columns
int PuzzleState::getNumRows () const {
    return rows;
}
int PuzzleState::getNumCols() const {
    return cols;
}

vector<int> PuzzleState::getTiles () const {
    return this->tiles;
}

// bool function definitons
bool PuzzleState::canMoveUp() {
    return blank_position_row > 0;
}

bool PuzzleState::canMoveDown() {
    return blank_position_row < rows - 1;
}

bool PuzzleState::canMoveLeft() {
    return blank_position_col > 0;
}

bool PuzzleState::canMoveRight() {
    return blank_position_col < cols - 1;
}

PuzzleState PuzzleState::moveBlankUp() {
    // return the object unchanged if moving up is not possible
    if (!canMoveUp()) {
        return *this;
    }

    // create a new state invoke the copy constructor
    PuzzleState newState = *this;

    // find and store the indices to be swapped
    int currBlankIndex = (cols * blank_position_row) + blank_position_col;
    int newBlankPosition = currBlankIndex - cols;

    // swap the tiles using the STL function swap()
    swap(newState.tiles.at(currBlankIndex), newState.tiles.at(newBlankPosition));

    // decrease blank_position_row of the new state by 1
    newState.blank_position_row -= 1;

    // return the new state
    return newState;
}

PuzzleState PuzzleState::moveBlankDown() {
    if (!canMoveDown()) {
        return *this;
    }

    PuzzleState newState = *this;
    int currBlankIndex = (cols * blank_position_row) + blank_position_col;
    int newBlankPosition = currBlankIndex + cols;
    swap(newState.tiles.at(currBlankIndex), newState.tiles.at(newBlankPosition));
    newState.blank_position_row += 1;

    return newState;
}

PuzzleState PuzzleState::moveBlankLeft() {
    if (!canMoveLeft()) {
        return *this;
    }

    PuzzleState newState = *this;
    int currBlankIndex = (cols * blank_position_row) + blank_position_col;
    int newBlankPosition = currBlankIndex - 1;
    swap(newState.tiles.at(currBlankIndex), newState.tiles.at(newBlankPosition));
    newState.blank_position_col -= 1;

    return newState;
}

PuzzleState PuzzleState::moveBlankRight() {
    if (!canMoveRight()) {
        return *this;
    }

    PuzzleState newState = *this;
    int currBlankIndex = (cols * blank_position_row) + blank_position_col;
    int newBlankPosition = currBlankIndex + 1;
    swap(newState.tiles.at(currBlankIndex), newState.tiles.at(newBlankPosition));
    newState.blank_position_col += 1;

    return newState;
}

void PuzzleState::read(istream & in) {
    // read input values into tiles
    for (int i = 0; i < tiles.size(); i++) {
        in >> tiles.at(i);

        // track the blank tile of the starting state
        if (tiles.at(i) == 0) {
            blank_position_row = i / cols;
            blank_position_col = i % cols;
        }
    }
}

void PuzzleState::print( ostream & out) const {
    for (int i = 0; i < tiles.size(); i++) {
        out << tiles.at(i);
        if ((i + 1) % cols == 0) {
            out << endl;            // new line at the end of each row
        }
        else {
            out << " ";             // space between numbers
        }
    }
}

istream & operator>>( istream &  in, PuzzleState & rhs ) {
    rhs.read(in);
    return in;
}

ostream & operator<<( ostream & out, const PuzzleState & rhs ) {
    rhs.print(out);
    return out;
}