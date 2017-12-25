//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX3_AIPLAYERTEST_H
#define EX3_AIPLAYERTEST_H

#include "gtest/gtest.h"
#include "../GameLogic.h"
#include "../AIPlayer.h"
#include "../HumanPlayer.h"
#include "../DisplayGameOnConsole.h"
#include "../AIEnemyGameFlow.h"
#include <iostream>


class AIPlayerTest: public testing::Test {
public:
    AIPlayerTest(){

        this->board = new Board();
	this->point1 = new Point(1, 1);
	this->point2 = new Point(5, 3);
	this->point3 = new Point(3, 3);
	this->point4 = new Point(3, 5);
        this->board->setBoard((board->getRows() / 2) - 1,(board->getColumns() / 2) - 1, BLACK);
        this->board->setBoard((board->getRows() / 2) - 2,(board->getColumns() / 2) - 1, BLACK);
        this->gameLogic = new GameLogic(board);
        this->blackPlayer = new HumanPlayer(BLACK);
        this->whitePlayer = new AIPlayer(WHITE);
    }

    virtual void SetUp() {
        this->possibleMovesVector = this->gameLogic->possibleMoves(this->whitePlayer, this->blackPlayer);
    }

    virtual void TearDown() {
    }

    ~AIPlayerTest() {
	delete point1;
	delete point2;
	delete point3;
	delete point4;
        delete gameLogic;
        delete blackPlayer;
        delete whitePlayer;
    }

protected:
    Board *board;
    GameLogic *gameLogic;
    vector<Point> possibleMovesVector;
    HumanPlayer *blackPlayer;
    AIPlayer *whitePlayer;
    Point *point1;
    Point *point2;
    Point *point3;
    Point *point4;

};

#endif //EX3_AIPLAYERTEST_H
