//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX4_REMOTEPLAYER_H
#define EX4_REMOTEPLAYER_H

#include "Player.h"
#include "Point.h"

class RemotePlayer: public Player{
public:
    /**
     * constructor of RemotePlayer object.
     * @param playerSign
     * @param serverIP
     * @param serverPort
     */
    RemotePlayer(Sign playerSign, const char *serverIP, int serverPort);

    /**
     * copy constructor.
     * @param otherPlayer
     */
    RemotePlayer(RemotePlayer *otherPlayer);
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
     * destructor of RemotePlayer object.
     */
    virtual ~RemotePlayer();
    /**
     * connect to server
     * @return
     */
    int connectToServer();
    /**
     * send cell to the server
     * @param x coordinate
     * @param y coordinate
     */
    void sendCell(int x, int y);
    /**
     * receive cell from the server
     * @return
     */
    Point receiveCell();
private:
    const char *serverIP;
    int serverPort;
    int clientSocket;
};

#endif //EX4_REMOTEPLAYER_H
