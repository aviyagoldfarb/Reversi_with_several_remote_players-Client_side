//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX3_GAMEFLOW_H
#define EX3_GAMEFLOW_H

#include "Player.h"
#include "AIPlayer.h"
#include "AbstractGameLogic.h"
#include "DisplayGameOnConsole.h"
#include "Point.h"
#include <limits>

/**
 * the class GameFlow defines GameFlow object.
 */
class GameFlow {
public:
    /**
     * constructor of HumanEnemyGameFlow object.
     * @param blackPlayer
     * @param whitePlayer
     * @param gameLogic
     * @param DisplayGameOnConsole
     */
    GameFlow(Player *blackPlayer, Player *whitePlayer, AbstractGameLogic *gameLogic, DisplayGame *displayGameOnConsole):
            blackPlayer(blackPlayer), whitePlayer(whitePlayer), gameLogic(gameLogic), displayGameOnConsole(displayGameOnConsole){}
    /**
     * checks if the chosen cell is in the possibleMovesVector.
     * @param possibleMovesVector
     * @param chosenCell
     * @return boolean
     */
    virtual bool chosenCellValidity(vector<Point> possibleMovesVector, Point chosenCell) = 0;
    /**
     * responsible for the turn exchanges between the players.
     */
    virtual void setNextTurn() = 0;
    /**
     * responsible for the game's running.
     */
    virtual void playTheGame() = 0;
    /**
     * destructor of GameFlow object
     */
    virtual ~GameFlow(){}
protected:
    //pointers to HumanPlayer object
    Player *blackPlayer, *whitePlayer;
    //pointer to GameLogic object
    AbstractGameLogic *gameLogic;
    //pointer to DisplayGameOnConsole object
    DisplayGame *displayGameOnConsole;
    //pointers to HumanPlayer object
    Player *turn, *nextTurn;
};

#endif //EX3_GAMEFLOW_H
