//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX1_BOARD_H
#define EX1_BOARD_H

#include "Cell.h"
#include <vector>
#include <iostream>
using namespace std;

/**
 * the class Board defines Board object.
 * the board is vector of vectors of cells.
 */
class Board {
public:

    /**
     * constructor of Board object.
     * @param rows = 8 by default.
     * @param columns = 8 by default.
     */
    Board(int rows=8, int columns=8);
    /**
     * copy constructor.
     * @param otherBoard
     */
    Board(Board *otherBoard);
    /**
     * get the number of rows.
     * @return numer of rows.
     */
    int getRows() const;
    /**
     * get the number of columns.
     * @return numer of columns.
     */
    int getColumns() const;
    /**
     * get the board.
     * @return vector<vector<Cell> >.
     */
    const vector<vector<Cell> > &getBoard() const;
    /**
     * set a cell in the board.
     * @param i row.
     * @param j column.
     * @param cell sign of the cell.
     */
    void setBoard(int i, int j, Sign cell);
    /**
     * destructor of Board object.
     */
    ~Board();

private:
    //will hold the value of the rows of the board
    int rows;
    //will hold the value of the columns of the board
    int columns;
    //will hold to the board
    vector< vector<Cell> > board;
};

#endif //EX1_BOARD_H
