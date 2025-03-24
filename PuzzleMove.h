#ifndef _PUZZLEMOVE_
#define _PUZZLEMOVE_

#include "PuzzleState.h"
using namespace std;

enum MoveType { down, left, right, up, nullMove };

class PuzzleMove {
public:
	PuzzleMove() { }

	PuzzleMove(PuzzleState s, PuzzleMove* p, MoveType m) : state(s),parent(p),move(m) { }

	void setParent(PuzzleMove* parent) {
		this->parent = parent;
	}

    PuzzleState & getState() { 	return state; }

	PuzzleMove* getParent() { return parent; }

	MoveType getMoveName() { return move; }

private:
	PuzzleState state;
	PuzzleMove* parent;
	MoveType move;
};

#endif