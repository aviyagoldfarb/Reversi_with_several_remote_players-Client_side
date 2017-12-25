//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "HumanEnemyGameFlowTest.h"

TEST_F(HumanEnemyGameFlowTest, chosenCellValidityTest) {
    EXPECT_EQ(true, this->gameFlow->chosenCellValidity(this->possibleMovesVector, *this->cell)) << "the function didn't find an existence cell";
    this->possibleMovesVector.pop_back();
    EXPECT_NE(true, gameLogic->checkCellExistence(this->possibleMovesVector, *this->cell)) << "the function found a cell that not exists";
}
