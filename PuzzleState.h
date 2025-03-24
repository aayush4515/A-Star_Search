 /*
     * This class describes what a PuzzleState is.
	 * The blank_position is for decreasing the time
	 * to check what tile operator is applicable
 */
#ifndef _PUZZLESTATE_
#define _PUZZLESTATE_
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class PuzzleState
{
  public:
	 // default constructor
	 PuzzleState() { }

	 //constructor
	 PuzzleState(int n, int m) {
		 tiles.resize(n*m);
		 rows = n;
		 cols = m;
	}
	 // destructor
	 ~PuzzleState() { }

	 // copy constructor
	 PuzzleState( const PuzzleState & rhs )
            : rows(rhs.rows), cols(rhs.cols),
			  tiles(rhs.tiles),
			  blank_position_row(rhs.blank_position_row),
			  blank_position_col(rhs.blank_position_col)
			  { }

	 // returns the index of a particular tile
	 auto getTileIndex (int tile) const {
		auto it = find(tiles.begin(), tiles.end(), tile);
		return distance(tiles.begin(), it);
	 }

	 // return a tile at the index i
	 int getCurrTile(int i) const {
		return tiles.at(i);
	 }
	 // get the vector size
	 int getTilesSize () const {
		return tiles.size();
	 }

	 // get the number of rows and columns
	 int getNumRows () const {
		return rows;
	 }
	 int getNumCols() const {
		return cols;
	 }

	 // get g
	 int getG() const{
		return g;
	 }
	 // get f
	 int getF() const {
		return f;
	 }

	 // set g
	 void setG(int g) {
		this->g = g;
	 }

	 // set f
	 void setF(int f) {
		this->f = f;
	 }

	 vector<int> getTiles () const {
		return this->tiles;
	 }

	 bool operator==(const PuzzleState & rhs) const;
	 bool operator!=(const PuzzleState & rhs) const;
	 const PuzzleState & operator=( const PuzzleState & rhs ); //assignment op
	 bool isNullState(){ return rows==0; }

	 bool canMoveUp();
	 bool canMoveDown();
	 bool canMoveLeft();
	 bool canMoveRight();
	 PuzzleState moveBlankUp();
	 PuzzleState moveBlankDown();
	 PuzzleState moveBlankLeft();
	 PuzzleState moveBlankRight();

	 void read( istream & in );
	 void print( ostream & out);

	// test prints

	//  void testPrint() {
	// 	// print tiles, blank position, rows and cols from the input state
    // 	cout << "Tiles: ";
    // 	for (int i = 0; i < tiles.size(); i++) {
    //     cout << tiles.at(i) << " ";
    // 	}
    // 	cout << endl;

	// 	cout << "The number of rows is: " << rows << endl;
	// 	cout << "The number of columns is: " << cols << endl;
	// 	cout << "The row of blank tile is: " << blank_position_row << endl;
	// 	cout << "The column of blank tile is: " << blank_position_col << endl;
	//  }

     static PuzzleState  NullState;
  private:
	  int rows;
	  int cols;
      vector<int> tiles;
      int blank_position_row;
	  int blank_position_col;
	  // identifiers for the A* search algorithm
	  int f = 0;
	  int g = 0;
	  //int h = 0;
};
istream & operator>>( istream &  in, PuzzleState & rhs );
ostream & operator<<( ostream & out, PuzzleState & rhs );

extern int numRowsCols;
extern PuzzleState startState;
extern PuzzleState goalState;

#endif
