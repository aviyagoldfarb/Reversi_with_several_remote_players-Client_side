//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX3_AIENEMYGAMEFLOWTEST_H
#define EX3_AIENEMYGAMEFLOWTEST_H

#include "gtest/gtest.h"
#include "../GameLogic.h"
#include "../HumanPlayer.h"
#include "../AIPlayer.h"
#include "../HumanEnemyGameFlow.h"
#include "../AIEnemyGameFlow.h"

#include <iostream>
using namespace std;

class AIEnemyGameFlowTest: public testing::Test {
public:
    AIEnemyGameFlowTest(){
        //creating an instance of Board object
        this->board = new Board();
        this->cell = new Point(5, 6);
        this->gameLogic = new GameLogic(board);
        this->blackPlayer = new HumanPlayer(BLACK);
        this->whitePlayer = new AIPlayer(WHITE);
        this->displayGameOnConsole = new DisplayGameOnConsole(board);
        this->gameFlow = new HumanEnemyGameFlow(blackPlayer, whitePlayer, gameLogic, displayGameOnConsole);
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

    ~AIEnemyGameFlowTest(){
        delete blackPlayer;
        delete whitePlayer;
        delete gameLogic;
        delete displayGameOnConsole;
        delete gameFlow;
    }

protected:
    Board *board;
    GameLogic *gameLogic;
    vector<Point> possibleMovesVector;
    Point *cell;
    Player *blackPlayer, *whitePlayer;
    DisplayGame *displayGameOnConsole;
    GameFlow *gameFlow;
};

#endif //EX3_AIENEMYGAMEFLOWTEST_H
