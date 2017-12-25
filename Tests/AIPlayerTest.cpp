//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "AIPlayerTest.h"

TEST_F(AIPlayerTest, miniMaxAlgorithmTest) {
    EXPECT_NE(*this->point4, this->whitePlayer->miniMaxAlgorithm(this->possibleMovesVector, gameLogic, blackPlayer))
                        << "The function didn't choose the best move";
    EXPECT_EQ(*this->point3, this->whitePlayer->miniMaxAlgorithm(this->possibleMovesVector, gameLogic, blackPlayer))
                        << "The function didn't choose the best move" ;
}

