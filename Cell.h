//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX2_CELL_H
#define EX2_CELL_H

#include <string>
#include <iostream>
using namespace std;

enum Sign {BLACK = 'X', WHITE = 'O', EMPTY = ' '};

/**
 * the class Cell defines Cell object.
 */
class Cell {
public:
    /**
     * constructor of Cell object.
     * @param cell = EMPTY by default.
     */
    Cell(Sign cell = EMPTY);
    /**
     * returns the sign of the cell.
     * @return sign of the cell.
     */
    Sign getCell() const;
    /**
     * sets the cell's sign.
     * @param cell.
     */
    void setCell(Sign cell);
    /**
     * making the cell's enum value printable.
     * @return the cell's enum value as a string.
     */
    string cellToPrint() const;

private:
    //will hold the sign of the cell
    Sign cell;
};

#endif //EX2_CELL_H
