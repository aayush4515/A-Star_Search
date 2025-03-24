#ifndef _PUZZLEMOVE_
#define _PUZZLEMOVE_

#include "PuzzleState.h"
using namespace std;

enum MoveType { down, left, right, up, nullMove };

class PuzzleMove {
public:
	PuzzleMove() { }

	PuzzleMove(PuzzleState s, PuzzleState p, MoveType m) : state(s),parent(p),move(m) { }

    const PuzzleState & getState() const { 	return state; }

	const PuzzleState getParent() const { return parent; }

	MoveType getMoveName() const { return move; }

private:
	PuzzleState state;
	PuzzleState parent;
	MoveType move;
};

inline bool operator<(const PuzzleMove& lhs, const PuzzleMove& rhs) {
    return lhs.getState() < rhs.getState(); // Compare based on resulting state
}

#endif