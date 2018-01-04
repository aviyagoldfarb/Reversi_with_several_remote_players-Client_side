//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "Board.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "DisplayGameOnConsole.h"
#include "HumanEnemyGameFlow.h"
#include "AIEnemyGameFlow.h"
#include "RemotePlayer.h"
#include "RemoteEnemyGameFlow.h"
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <string>
#include <list>

#define  MAX_LIST_OF_GAMES_BUFFER 250
#define  MAX_COMMAND_BUFFER 50

using namespace std;

int serverResponse(int clientSocket){
    int successOrFailure;

    int n;
    try {
        n = read(clientSocket, &successOrFailure, sizeof(successOrFailure));
        if (n == -1) {
            throw "Error- failed on reading from socket";
        }
    } catch(const char *msg) {
        cout << "Reason: " << msg << endl;
    }
    if (n == 0) {
        cout << "Server disconnected, the game forces to end" << endl;
        return -1;
    }
    //check if the game was created
    if (successOrFailure == 1){
        cout << "The command was executed successfully" << endl;
        return 1;
    }
    else if (successOrFailure == -1){
        cout << "Failed on executing command" << endl;
        return 0;
    }
}

int serverResponseToListGamesCommand(int clientSocket){
    int n;
    char listOfGames[MAX_LIST_OF_GAMES_BUFFER];
    memset(listOfGames, '\0', MAX_LIST_OF_GAMES_BUFFER);
    list<string> listOfStrGames;
    try {
        n = read(clientSocket, listOfGames, MAX_LIST_OF_GAMES_BUFFER);
        if (n == -1) {
            throw "Error- failed on reading from socket";
        }
    } catch(const char *msg) {
        cout << "Reason: " << msg << endl;
    }
    if (n == 0) {
        cout << "Server disconnected, the game forces to end" << endl;
        return -1;
    }
    char *temp;
    temp = strtok (listOfGames," ");
    while (temp != NULL)
    {
        string tempStr(temp);
        listOfStrGames.push_back(tempStr);
        temp = strtok (NULL, " ");
    }
    if(listOfStrGames.size() == 0){
        cout << "There are no optional games" << endl;
        cout << endl;
    }
    else{
        list<string>::iterator it;
        cout << "The current optional games are:" << endl;
        for (it = listOfStrGames.begin(); it != listOfStrGames.end(); it++){
            cout << *it << endl;
        }
        cout << endl;
    }
    return 1;
}

//in case that the player sent the command 'join'?
int joinAndPlay(Player **blackPlayer, Player **whitePlayer, AbstractGameLogic *gameLogic,
                 DisplayGame *displayGameOnConsole, GameFlow **gameFlow, RemotePlayer **client, int clientSocket){
    int n;
    int myNumberColor = 0;

    try {
        n = read(clientSocket, &myNumberColor, sizeof(myNumberColor));
        if (n == -1) {
            throw "Error- failed on reading number of player from socket";
        }
    } catch (const char *msg) {
        cout << "Reason: " << msg << endl;
    }
    if (n == 0) {
        cout << "Server disconnected, the game forces to end" << endl;
        return -1;
    }
    //check the 'color' (sign) of the player who plays in this computer
    if (myNumberColor == 1) {
        cout << endl;
        cout << "You are the black player X." << endl;
        cout << endl;
        *blackPlayer = new HumanPlayer(BLACK);
        (*client)->setPlayerSign(WHITE);
        *whitePlayer = *client;
        *gameFlow = new RemoteEnemyGameFlow(*blackPlayer, *whitePlayer, gameLogic, displayGameOnConsole);
        return 1;
    }
    if (myNumberColor == 2) {
        cout << endl;
        cout << "You are the white player O." << endl;
        cout << endl;
        *whitePlayer = new HumanPlayer(WHITE);
        (*client)->setPlayerSign(BLACK);
        *blackPlayer = *client;
        *gameFlow = new RemoteEnemyGameFlow(*whitePlayer, *blackPlayer, gameLogic, displayGameOnConsole);
        return 1;
    }
}

void commandsSender(int clientSocket, char* command){
    int n;
    // write the command argument to the socket
    n = write(clientSocket, command, strlen(command));
    if (n == -1) {
        throw "Error in writing command to socket";
    }
}

int typeAndSendCommandsToServer(Player **blackPlayer, Player **whitePlayer, AbstractGameLogic *gameLogic,
                          DisplayGame *displayGameOnConsole, GameFlow **gameFlow, RemotePlayer **client, int clientSocket){
    int index = 0;
    do {
        string commandStr;
        char command[MAX_COMMAND_BUFFER];
        memset(command, '\0', MAX_COMMAND_BUFFER);
        int retval;
        cout << "Please type one of the following commands:" << endl;
        cout << "1. start <name>" << endl;
        cout << "2. list_games" << endl;
        cout << "3. join <name>" << endl;

        //wait for the client to type one of the commands
        string dummy;
        if (index == 0){
            getline(cin, dummy);
        }

        getline(cin, commandStr);
        memcpy(command, commandStr.c_str(), commandStr.size());
        if (commandStr.find("start") != -1){
            commandsSender(clientSocket, command);
            retval = serverResponse(clientSocket);
            if (retval == 1){
                cout << "Waiting for another player to join" << endl;
                retval = joinAndPlay(blackPlayer, whitePlayer, gameLogic, displayGameOnConsole, gameFlow, client, clientSocket);
                if (retval == -1){
                    return -1;
                }
                break;
            }
            else if (retval == 0){
                cout << "There is already a game with this name, please restart the program" << endl;
                return -1;
            }
            else if (retval == -1){
                return -1;
            }

        }
        else if (commandStr.find("list_games") != -1){
            commandsSender(clientSocket, command);
            retval = serverResponseToListGamesCommand(clientSocket);
            if (retval == -1){
                return -1;
            }
        }
        else if (commandStr.find("join") != -1){
            commandsSender(clientSocket, command);
            retval = serverResponse(clientSocket);
            if (retval == 1){
                retval = joinAndPlay(blackPlayer, whitePlayer, gameLogic, displayGameOnConsole, gameFlow, client, clientSocket);
                if (retval == -1){
                    return -1;
                }
                break;
            }
            else if (retval == 0){
                cout << "There is no such game with this name, please restart the program" << endl;
                return -1;
            }
            else if (retval == -1){
                return -1;
            }
        }
        index++;
    } while(true);
    return 1;
}

int createRemoteEnemyGameFlow(Player **blackPlayer, Player **whitePlayer, AbstractGameLogic *gameLogic,
                               DisplayGame *displayGameOnConsole, GameFlow **gameFlow) {
    int retval;
    //read the ip and the port from the configuration file
    string ip;
    int port;
    ifstream inFile;
    inFile.open("client_configuration_file.txt");

    if (inFile.is_open()) {
        inFile >> ip;
        inFile >> port;
        inFile.close();
    } else cout << "Unable to open file";

    //create a RemotePlayer client
    RemotePlayer *client = new RemotePlayer(EMPTY, ip.c_str(), port);
    int clientSocket;
    try {
        clientSocket = client->connectToServer();
    } catch (const char *msg) {
        cout << "Failed in connect to server. Reason:" << msg << endl;
        exit(-1);
    }

    retval = typeAndSendCommandsToServer(blackPlayer, whitePlayer, gameLogic, displayGameOnConsole, gameFlow, &client, clientSocket);
    if(retval == -1){
        close(clientSocket);
        delete client;
    }
    return retval;
}

int gameMenu(Player **blackPlayer, Player **whitePlayer, AbstractGameLogic *gameLogic, DisplayGame *displayGameOnConsole, GameFlow **gameFlow){
    int retval;
    char playerInput;
    cout << "Please choose your enemy:" << endl;
    cout << "1. Human Player (press H)" << endl;
    cout << "2. AI player (press A)" << endl;
    cout << "3. Remote player (press R)" << endl;
    cin >> playerInput;
    switch (playerInput) {
        case 'H':
        case 'h':
            {
                //the player choose human player as enemy
                *blackPlayer = new HumanPlayer(BLACK);
                *whitePlayer = new HumanPlayer(WHITE);
                *gameFlow = new HumanEnemyGameFlow(*blackPlayer, *whitePlayer, gameLogic, displayGameOnConsole);
                break;
            }
        case 'A':
        case 'a':
            {
                //the player choose AI player as enemy
                *blackPlayer = new HumanPlayer(BLACK);
                *whitePlayer = new AIPlayer(WHITE);
                *gameFlow = new AIEnemyGameFlow(*blackPlayer, *whitePlayer, gameLogic, displayGameOnConsole);
                break;
            }
        case 'R':
        case 'r':
            {
                //the player choose a remote player as enemy
                retval = createRemoteEnemyGameFlow(blackPlayer, whitePlayer, gameLogic, displayGameOnConsole, gameFlow);
                return retval;
            }
    }
    return 1;
}

int main() {
    int retval;
    //creating an instance of Board object
    Board *board = new Board();
    // Player *blackPlayer = new HumanPlayer(BLACK);
    Player *blackPlayer;
    Player *whitePlayer;
    AbstractGameLogic *gameLogic = new GameLogic(board);
    DisplayGame *displayGameOnConsole = new DisplayGameOnConsole(board);
    GameFlow *gameFlow;

    retval = gameMenu(&blackPlayer, &whitePlayer, gameLogic, displayGameOnConsole, &gameFlow);

    if (retval == 1){
        gameFlow->playTheGame();
        delete blackPlayer;
        delete whitePlayer;
        delete gameFlow;
    }

    //delete created objects

    /*we put 'delete board' in comment because in the current implementation the board is
    deleted within the 'GameLogic' destructor*/

    //delete board;
    //delete blackPlayer;
    //delete whitePlayer;
    //deletes the board as well
    delete gameLogic;
    delete displayGameOnConsole;
    //delete gameFlow;
    return 0;
}