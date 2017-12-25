//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX2_HUMANPLAYER_H
#define EX2_HUMANPLAYER_H

#include "Player.h"

/**
 * the class HumanPlayer defines HumanPlayer object.
 */
class HumanPlayer: public Player{
public:
    /**
     * constructor of HumanPlayer object.
     * @param playerSign value from enum Sign.
     */
    HumanPlayer(Sign playerSign = EMPTY);
    /**
     * copy constructor.
     * @param otherPlayer
     */
    HumanPlayer(HumanPlayer *otherPlayer);
    /**
     * get the sign of the player(BLACK or WHITE).
     * @return sign of the player.
     */
    Sign getPlayerSign() const;
    /**
     * set the sign of the player(BLACK or WHITE).
     * @param playerSign.
     */
    void setPlayerSign(Sign playerSign);
    /**
     * get the score of the player.
     * @return playerScore.
     */
    int getPlayerScore() const;
    /**
     * set the score of the player.
     * @param addToPlayerScore number to add to the current score.
     */
    void setPlayerScore(int addToPlayerScore);
    /**
     * destructor of HumanPlayer object.
     */
    virtual ~HumanPlayer();
};

#endif //EX2_HUMANPLAYER_H
