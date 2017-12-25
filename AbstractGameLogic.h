//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX2_ABSTRACTGAMELOGIC_H
#define EX2_ABSTRACTGAMELOGIC_H

#include "Board.h"
#include "Point.h"
#include "Player.h"

/**
 * abstract class AbstractGameLogic.
 */
class AbstractGameLogic {
public:
    /**
     * constructor of AbstractGameLogic object.
     * @param board pointer to board object.
     */
    AbstractGameLogic(Board *board): board(board){}
    /**
     * copy constructor.
     * @param otherAbstractGameLogic
     */
    AbstractGameLogic(AbstractGameLogic *otherAbstractGameLogic){
        this->board = new Board(otherAbstractGameLogic->board);
    }
    /**
     * check cell existence before inserting it to the possibleMovesVector.
     * @param possibleMovesVector.
     * @param cell.
     * @return boolean.
     */
    virtual bool checkCellExistence(vector<Point> possibleMovesVector, Point cell) = 0;
    /**
     * returns possible moves for the current player.
     * @param player current player.
     * @param enemy current enemy.
     * @return vector<Point> of possible moves.
     */
    virtual vector<Point> possibleMoves(Player *player, Player *enemy) = 0;
    /**
     * operates the player's chosen move.
     * @param chosenCell of the current player.
     * @param player.
     * @param enemy.
     */
    virtual void moveMaker(Point chosenCell, Player *player, Player *enemy) = 0;
    /**
     * checks if the board is full.
     * @return boolean.
     */
    virtual bool fullBoard() = 0;
    /**
     * destructor of AbstractGameLogic object
     */
    virtual ~AbstractGameLogic(){}

protected:
    //points to the game's board
    Board *board;
};

#endif //EX2_ABSTRACTGAMELOGIC_H
