//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX2_REMOTEENEMYGAMEFLOW_H
#define EX2_REMOTEENEMYGAMEFLOW_H

#include "GameFlow.h"


/**
 * the class RemoteEnemyGameFlow defines RemoteEnemyGameFlow object.
 */
class RemoteEnemyGameFlow: public GameFlow {
public:
    /**
     * constructor of RemoteEnemyGameFlow object.
     * @param mySelfPlayer
     * @param remoteEnemyPlayer
     * @param gameLogic
     * @param DisplayGameOnConsole
     */
    RemoteEnemyGameFlow(Player *mySelfPlayer, Player *remoteEnemyPlayer, AbstractGameLogic *gameLogic, DisplayGame *displayGameOnConsole);
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
    virtual ~RemoteEnemyGameFlow();
private:
    //pointers to Player
    Player *mySelfPlayer, *remoteEnemyPlayer;
};

#endif //EX2_REMOTEENEMYGAMEFLOW_H
