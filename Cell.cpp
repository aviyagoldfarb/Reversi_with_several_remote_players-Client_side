//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "Cell.h"

Cell::Cell(Sign cell) : cell(cell) {}

Sign Cell::getCell() const {
    return cell;
}

void Cell::setCell(Sign cell) {
    this->cell = cell;
}

string Cell::cellToPrint() const{
    return string(1, this->cell);
}
