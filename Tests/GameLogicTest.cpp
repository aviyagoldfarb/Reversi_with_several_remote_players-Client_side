//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "GameLogicTest.h"

TEST_F(GameLogicTest, checkCellExistenceTest) {
    EXPECT_EQ(true, gameLogic->checkCellExistence(this->possibleMovesVector, *this->cell)) << "the function didn't find an existence cell";
    this->possibleMovesVector.pop_back();
    EXPECT_NE(true, gameLogic->checkCellExistence(this->possibleMovesVector, *this->cell)) << "the function found a cell that not exists";
}

TEST_F(GameLogicTest, possibleMovesTest) {
    //create a vector that will get the return value of possibleMoves function
    vector<Point> returnedPossibleMovesVector;
    returnedPossibleMovesVector = gameLogic->possibleMoves(blackPlayer, whitePlayer);
    for(int i = 0; i < this->possibleMovesVector.size(); i++){
        EXPECT_EQ(returnedPossibleMovesVector[i], this->possibleMovesVector[i]) << "the function does not returns the right possible moves";
    }

}

TEST_F(GameLogicTest, fullBoardTest){
    for(int i = 0; i < board->getRows(); i++){
        for(int j = 0; j < board->getColumns(); j++){
            this->board->setBoard(i, j, WHITE);
        }
    }
    EXPECT_EQ(this->gameLogic->fullBoard(), true) << "the function fullBoard does not recognize full board";
    this->board->setBoard(1, 1, EMPTY);
    EXPECT_EQ(this->gameLogic->fullBoard(), false) << "the function fullBoard does not recognize unfull board";
}
