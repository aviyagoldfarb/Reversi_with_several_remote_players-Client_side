//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX2_PLAYER_H
#define EX2_PLAYER_H

#include "Cell.h"

/**
 * abstract class Player.
 */
class Player {
public:
    /**
     * constructor of Player object.
     * @param playerSign value from enum Sign.
     */
    Player(Sign playerSign = EMPTY) : playerSign(playerSign) , playerScore(2) {}
    /**
     * copy constructor.
     * @param otherPlayer
     */
    Player(Player *otherPlayer) : playerSign(otherPlayer->getPlayerSign()) , playerScore(otherPlayer->getPlayerScore()) {}
    /**
     * get the sign of the player(BLACK or WHITE).
     * @return sign of the player.
     */
    virtual Sign getPlayerSign() const = 0;
    /**
     * set the sign of the player(BLACK or WHITE).
     * @param playerSign.
     */
    virtual void setPlayerSign(Sign playerSign) = 0;
    /**
     * get the score of the player.
     * @return playerScore.
     */
    virtual int getPlayerScore() const = 0;
    /**
     * set the score of the player.
     * @param addToPlayerScore number to add to the current score.
     */
    virtual void setPlayerScore(int addToPlayerScore) = 0;
    /**
     * destructor of HumanPlayer object.
     */
    virtual ~Player(){}

protected:
    //the sign of the player(BLACK or WHITE)
    Sign playerSign;
    //the score of the player
    int playerScore;
};

#endif //EX2_PLAYER_H
