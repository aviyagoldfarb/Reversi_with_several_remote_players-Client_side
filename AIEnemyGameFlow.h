//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX3_AIENEMYGAMEFLOW_H
#define EX3_AIENEMYGAMEFLOW_H

#include "GameFlow.h"
#include "AbstractGameLogic.h"

/**
 * the class AIEnemyGameFlow defines AIEnemyGameFlow object.
 */
class AIEnemyGameFlow: public GameFlow {
public:
    /**
     * constructor of HumanEnemyGameFlow object.
     * @param blackPlayer
     * @param whitePlayer
     * @param gameLogic
     * @param DisplayGameOnConsole
     */
    AIEnemyGameFlow(Player *blackPlayer, Player *whitePlayer, AbstractGameLogic *gameLogic, DisplayGame *displayGameOnConsole);
    /**
     * checks if the chosen cell is in the possibleMovesVector.
     * @param possibleMovesVector
     * @param chosenCell
     * @return boolean
     */
    bool chosenCellValidity(vector<Point> possibleMovesVector, Point chosenCell);
    /**
     * responsible for the turn exchanges between the players.
     */
    void setNextTurn();
    /**
     * responsible for the game's running.
     */
    void playTheGame();
    /**
     * destructor of HumanEnemyGameFlow object.
     */
    virtual ~AIEnemyGameFlow();

};

#endif //EX3_AIENEMYGAMEFLOW_H
