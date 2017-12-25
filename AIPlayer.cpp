//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "AIPlayer.h"

AIPlayer::AIPlayer(Sign playerSign) : Player(playerSign) {

}

AIPlayer::AIPlayer(AIPlayer *otherPlayer) : Player(otherPlayer) {

}

Sign AIPlayer::getPlayerSign() const {
    return playerSign;
}

void AIPlayer::setPlayerSign(Sign playerSign) {
    this->playerSign = playerSign;
}

int AIPlayer::getPlayerScore() const {
    return playerScore;
}

void AIPlayer::setPlayerScore(int addToPlayerScore) {
    this->playerScore += addToPlayerScore;
}

Point AIPlayer::miniMaxAlgorithm(vector<Point> possibleMovesVector, AbstractGameLogic *currentGameLogicState, Player *enemy){
    /*will hold the cell chosen by the AI player- the cell that
    will minimize the enemy's score in his next move*/
    Point chosenCell(1,1);
    //will get the score of the enemy for each move he does
    int enemyTempScore;
    //will get the score of the enemy's best move (the maximal score)
    int enemyMaxScore = -64;
    /*will hold the grade of the cell (chosen by the AI player)
    that leads to the minimal enemy's profit*/
    int chosenCellGrade = 64;
    //create a vector that will get the possible moves of the enemy
    vector<Point> enemyPossibleMovesVector;
    //iterating over the possible moves of the AI player
    for(int i = 0; i < possibleMovesVector.size(); i++){
        /*create copies of three objects in order to examine possible
        evolutions of the game and restore the original state*/
        AbstractGameLogic *gameLogic = new GameLogic(static_cast<GameLogic *>(currentGameLogicState));
        Player *thisCopy = new AIPlayer(this);
        Player *enemyCopy = new HumanPlayer(static_cast<HumanPlayer *>(enemy));
        //use the object's copies in order to examine the current move possibility
        gameLogic->moveMaker(possibleMovesVector[i], thisCopy, enemyCopy);
        //check for the enemy's possible moves
        enemyPossibleMovesVector = gameLogic->possibleMoves(enemyCopy, thisCopy);
        //if there are no possible moves for the enemy- return the cell that causes this
        if(enemyPossibleMovesVector.size() == 0){
            chosenCell.setX(possibleMovesVector[i].getX());
            chosenCell.setY(possibleMovesVector[i].getY());
            //deleting the copied objects
            delete gameLogic;
            delete thisCopy;
            delete enemyCopy;
            return chosenCell;
        }
        //iterating over the possible moves of the enemy player
        for(int j = 0; j < enemyPossibleMovesVector.size(); j++){
            /*create copies of three objects in order to examine possible
            evolutions of the game and restore the original state*/
            AbstractGameLogic *copyOfGameLogic = new GameLogic(static_cast<GameLogic *>(gameLogic));
            Player *copyOfthisCopy = new AIPlayer(static_cast<AIPlayer *>(thisCopy));
            Player *copyOfenemyCopy = new HumanPlayer(static_cast<HumanPlayer *>(enemyCopy));
            //use the object's copies in order to examine the current move possibility
            gameLogic->moveMaker(enemyPossibleMovesVector[j], copyOfenemyCopy, copyOfthisCopy);
            //calculate the enemy's score for his current move
            enemyTempScore = copyOfenemyCopy->getPlayerScore() - copyOfthisCopy->getPlayerScore();
            //if the score of the current move is higher than the current maximal score update it
            if(enemyTempScore > enemyMaxScore){
                enemyMaxScore = enemyTempScore;
            }
            //deleting the copies of the copied objects
            delete copyOfGameLogic;
            delete copyOfthisCopy;
            delete copyOfenemyCopy;
        }
        //keep the cell that will minimize the enemy's profit
        if(chosenCellGrade >= enemyMaxScore){
            chosenCellGrade = enemyMaxScore;
            chosenCell.setX(possibleMovesVector[i].getX());
            chosenCell.setY(possibleMovesVector[i].getY());
        }
        //deleting the copied objects
        delete gameLogic;
        delete thisCopy;
        delete enemyCopy;
        enemyPossibleMovesVector.clear();
    }
    return chosenCell;
}

AIPlayer::~AIPlayer() {

}
