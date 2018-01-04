//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "RemotePlayer.h"
#include "RemoteEnemyGameFlow.h"

RemoteEnemyGameFlow::RemoteEnemyGameFlow(Player *mySelfPlayer, Player *remoteEnemyPlayer, AbstractGameLogic *gameLogic, DisplayGame *displayGameOnConsole) :
        GameFlow(mySelfPlayer, remoteEnemyPlayer, gameLogic, displayGameOnConsole), mySelfPlayer(mySelfPlayer), remoteEnemyPlayer(remoteEnemyPlayer){
    if (mySelfPlayer->getPlayerSign() == BLACK){
        blackPlayer = mySelfPlayer;
        whitePlayer = remoteEnemyPlayer;
    }
    else{
        blackPlayer = remoteEnemyPlayer;
        whitePlayer = mySelfPlayer;
    }
}

bool RemoteEnemyGameFlow::chosenCellValidity(vector<Point> possibleMovesVector, Point chosenCell){
    for(int i = 0; i < possibleMovesVector.size(); i++){
        if(possibleMovesVector[i].isEqual(chosenCell)){
            return true;
        }
    }
    return false;
}

void RemoteEnemyGameFlow::setNextTurn(){
    if(this->turn == blackPlayer){
        this->turn = whitePlayer;
        this->nextTurn = blackPlayer;
    }
    else{
        this->turn = blackPlayer;
        this->nextTurn = whitePlayer;
    }
}

void RemoteEnemyGameFlow::playTheGame() {

    //create a vector that will get the return value of possibleMoves function
    vector<Point> possibleMovesVector;
    int x, y;

    Point receivedCell(0, 0);

    //initialize the turns
    this->turn = blackPlayer;
    this->nextTurn = whitePlayer;

    //running until the end of the game criteria
    do{
        cout << "Current board:" << endl;
        cout << endl;
        //printing the board using printGameBoard function from DisplayGameOnConsole class
        this->displayGameOnConsole->printGameBoard();

        //check if the current player is the player who plays in this computer
        if(this->turn->getPlayerSign() == mySelfPlayer->getPlayerSign()){

            cout << string(1, this->turn->getPlayerSign()) << ":" << " It's your move." << endl;
            //check for the possible moves
            possibleMovesVector = gameLogic->possibleMoves(this->turn, this->nextTurn);
            //check if the vector is empty
            if(possibleMovesVector.size() == 0){
                cout << "No possible moves. Play passes back to other player." << endl;
                cout << endl;
                //send to the other player the cell (0, 0) to let him know that there was no move
                try {
                    //down cast
                    RemotePlayer *demoRemotePlayer = static_cast<RemotePlayer *>(this->nextTurn);
                    demoRemotePlayer->sendCell(0, 0);
                } catch (const char *msg) {
                    cout << "Failed to send the new cell to server. Reason: " << msg << endl;
                }

                this->setNextTurn();
                continue;
            }
            cout << "Your possible moves: ";
            //display the optional cells
            for(int i = 0; i < possibleMovesVector.size(); i++){
                possibleMovesVector[i].pointToPrint();
                if(i < possibleMovesVector.size() - 1){
                    cout << ",";
                }
            }
            cout << endl;
            cout << endl;

            //loop until the player enters appropriate cell
            do {
                cout << "Please enter your move row col: ";
                cin >> x >> y;
                if (cin.fail()) {
                    cout << "This is not a number. Try again." << endl;
                    cout << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                //create a point from the player's input
                Point chosenCell(x, y);
                //check if the player's input is valid
                if (this->chosenCellValidity(possibleMovesVector, chosenCell)) {
                    gameLogic->moveMaker(chosenCell, this->turn, this->nextTurn);
                    break;
                } else {
                    //keep looping
                    cout << "The chosen cell is not valid. Try again." << endl;
                    cout << endl;
                }
            } while (1);

            try {
                //down cast
                RemotePlayer *demoRemotePlayer = static_cast<RemotePlayer *>(this->nextTurn);
                demoRemotePlayer->sendCell(x, y);
            } catch (const char *msg) {
                cout << "Failed to send the new cell to server. Reason: " << msg << endl;
            }

        }
        else{//the current player is the remote player
            cout << "Waiting for other player to make his move..." << endl;
            try {
                //down cast
                RemotePlayer *demoRemotePlayer = static_cast<RemotePlayer *>(this->turn);
                Point chosenCell = demoRemotePlayer->receiveCell();
                receivedCell.setX(chosenCell.getX());
                receivedCell.setY(chosenCell.getY());
            } catch (const char *msg) {
                cout << "Failed to receive the new cell from server. Reason: " << msg << endl;
            }
            //if the received cell is (-2, -2) it means that the server disconnected
            if (receivedCell.getX() == -2 && receivedCell.getY() == -2){
                cout << "Server disconnected, the game forces to end" << endl;
                cout << endl;
                return;
            }
            //if the received cell is (0, 0) do nothing
            if (receivedCell.getX() != 0 && receivedCell.getY() != 0){
                gameLogic->moveMaker(receivedCell, this->turn, this->nextTurn);
                cout << "Remote player choose ";
                receivedCell.pointToPrint();
                cout << endl;
                cout << endl;
            }

        }

        possibleMovesVector.clear();
        this->setNextTurn();
        //end of the game criteria
    }while(!(gameLogic->fullBoard()) && (gameLogic->possibleMoves(this->turn, this->nextTurn).size() != 0 ||
                                         gameLogic->possibleMoves(this->nextTurn, this->turn).size() != 0));

    //in case that the player of this computer is the one who finished the game
    if(this->turn == this->remoteEnemyPlayer){
        try {
            //down cast
            RemotePlayer *demoRemotePlayer = static_cast<RemotePlayer *>(this->turn);
            demoRemotePlayer->sendCell(-1, -1);
        } catch (const char *msg) {
            cout << "Failed to send the message about the end of the game. Reason: " << msg << endl;
        }
    }
    //printing the board using printGameBoard function from DisplayGameOnConsole class
    this->displayGameOnConsole->printGameBoard();
    cout << endl;
    cout << endl;
    //display the results of the game
    cout << "The winner is: ";
    if(blackPlayer->getPlayerScore() > whitePlayer->getPlayerScore()){
        cout << "The black player with " << blackPlayer->getPlayerScore() << " cells.";
    }
    if(blackPlayer->getPlayerScore() < whitePlayer->getPlayerScore()){
        cout << "The white player with " << whitePlayer->getPlayerScore() << " cells.";
    }
    if(blackPlayer->getPlayerScore() == whitePlayer->getPlayerScore()){
        cout << "No winner, both players are even with " << blackPlayer->getPlayerScore() << " cells each.";
    }
    cout << endl;
}

RemoteEnemyGameFlow::~RemoteEnemyGameFlow() {
}