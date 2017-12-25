//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(Sign playerSign) : Player(playerSign) {

}

HumanPlayer::HumanPlayer(HumanPlayer *otherPlayer) : Player(otherPlayer){

}

Sign HumanPlayer::getPlayerSign() const {
    return playerSign;
}

void HumanPlayer::setPlayerSign(Sign playerSign) {
    this->playerSign = playerSign;
}

int HumanPlayer::getPlayerScore() const {
    return playerScore;
}

void HumanPlayer::setPlayerScore(int addToPlayerScore) {
    this->playerScore += addToPlayerScore;
}

HumanPlayer::~HumanPlayer() {

}


