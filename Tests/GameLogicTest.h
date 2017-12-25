//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX3_GAMELOGICTEST_H
#define EX3_GAMELOGICTEST_H

#include "gtest/gtest.h"
#include "../GameLogic.h"
#include "../HumanPlayer.h"

#include <iostream>
using namespace std;

class GameLogicTest: public testing::Test {
public:
    GameLogicTest(){
        //creating an instance of Board object
        this->board = new Board();
	    this->cell = new Point(5, 6);
        this->gameLogic = new GameLogic(board);
        this->blackPlayer = new HumanPlayer(BLACK);
        this->whitePlayer = new HumanPlayer(WHITE);
    }

    virtual void SetUp() {
        Point cell2(3, 4);
        Point cell3(4, 3);
        Point cell4(6, 5);
        this->possibleMovesVector.push_back(cell4);
        this->possibleMovesVector.push_back(cell3);
        this->possibleMovesVector.push_back(cell2);
        this->possibleMovesVector.push_back(*cell);
    }

    virtual void TearDown() {
    }

    ~GameLogicTest(){
        delete cell;
        delete gameLogic;
        delete blackPlayer;
        delete whitePlayer;
    }

protected:
    Board *board;
    GameLogic *gameLogic;
    vector<Point> possibleMovesVector;
    Point *cell;
    Player *blackPlayer, *whitePlayer;
};

#endif //EX3_GAMELOGICTEST_H
