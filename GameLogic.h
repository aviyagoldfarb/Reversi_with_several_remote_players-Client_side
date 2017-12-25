//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX2_GAMELOGIC_H
#define EX2_GAMELOGIC_H

#include "AbstractGameLogic.h"

/**
 * the class GameLogic defines GameLogic object.
 */
class GameLogic: public AbstractGameLogic {
public:
    /**
     * constructor of GameLogic object.
     * @param board pointer to board object.
     */
    GameLogic(Board *board);
    /**
     * copy constructor.
     * @param otherAbstractGameLogic
     */
    GameLogic(GameLogic *otherAbstractGameLogic);
    /**
     * check cell existence before inserting it to the possibleMovesVector.
     * @param possibleMovesVector.
     * @param cell.
     * @return boolean.
     */
    bool checkCellExistence(vector<Point> possibleMovesVector, Point cell);
    /**
     * returns possible moves for the current player.
     * @param player current player.
     * @param enemy current enemy.
     * @return vector<Point> of possible moves.
     */
    vector<Point> possibleMoves(Player *player, Player *enemy);
    /**
     * operates the player's chosen move.
     * @param chosenCell of the current player.
     * @param player.
     * @param enemy.
     */
    void moveMaker(Point chosenCell, Player *player, Player *enemy);
    /**
     * checks if the board is full.
     * @return boolean.
     */
    bool fullBoard();
    /**
     * destructor of GameLogic object
     */
    virtual ~GameLogic();
};

#endif //EX2_GAMELOGIC_H
