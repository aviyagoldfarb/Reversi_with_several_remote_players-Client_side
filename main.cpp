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

using namespace std;

void serverResponseToStartCommand(int clientSocket){
    int n, successOrFailure ;
    try {
        n = read(clientSocket, &successOrFailure, sizeof(successOrFailure));
        if (n == -1) {
            throw "Error- failed on reading from socket";
        }
    } catch(const char *msg) {
        cout << "Reason: " << msg << endl;
    }
    //check if the game was created
    if (successOrFailure == 1){
        cout << "A new game was added" << endl;
    }
    else if (successOrFailure == -1){
        cout << "A game with this name is already exist, please try again" << endl;
    }
}

void serverResponseToListGamesCommand(int clientSocket){
    int n;
    char listOfGames[250];
    memset(listOfGames, '\0', 250);
    list<string> listOfStrGames;
    try {
        n = read(clientSocket, &listOfGames, sizeof(listOfGames));
        if (n == -1) {
            throw "Error- failed on reading from socket";
        }
    } catch(const char *msg) {
        cout << "Reason: " << msg << endl;
    }

    char *temp;
    temp = strtok (listOfGames," ");
    while (temp != NULL)
    {
        string tempStr(temp);
        listOfStrGames.push_back(temp);
        temp = strtok (NULL, " ");
    }
    list<string>::iterator it;
    cout << "The current optional games are:" << endl;
    for (it = listOfStrGames.begin(); it != listOfStrGames.end(); it++){
        cout << *it << endl;
    }

}

//in case that the player sent the command 'join'?
void joinAndPlay(Player **blackPlayer, Player **whitePlayer, AbstractGameLogic *gameLogic,
                 DisplayGame *displayGameOnConsole, GameFlow **gameFlow, RemotePlayer **client, int clientSocket){
    int n, myNumberColor;
    try {
        n = read(clientSocket, &myNumberColor, sizeof(myNumberColor));
        if (n == -1) {
            throw "Error- failed on reading number of player from socket";
        }
    } catch(const char *msg) {
        cout << "Reason: " << msg << endl;
    }
    //check the 'color' (sign) of the player who plays in this computer
    if (myNumberColor == 1) {
        cout << "Waiting for the other player to join..." << endl;
        cout << endl;
        cout << "You are the black player X." << endl;
        cout << endl;
        *blackPlayer = new HumanPlayer(BLACK);
        (*client)->setPlayerSign(WHITE);
        *whitePlayer = *client;
        *gameFlow = new RemoteEnemyGameFlow(*blackPlayer, *whitePlayer, gameLogic, displayGameOnConsole);
        return;
    }
    if (myNumberColor == 2) {
        cout << endl;
        cout << "You are the white player O." << endl;
        cout << endl;
        *whitePlayer = new HumanPlayer(WHITE);
        (*client)->setPlayerSign(BLACK);
        *blackPlayer = *client;
        *gameFlow = new RemoteEnemyGameFlow(*whitePlayer, *blackPlayer, gameLogic, displayGameOnConsole);
        return;
    }
}

void commandsSender(int clientSocket, string command){
    int n;
    // write the command argument to the socket
    n = write(clientSocket, &command, sizeof(command));
    if (n == -1) {
        throw "Error in writing command to socket";
    }
}

void typeAndSendCommandsToServer(Player **blackPlayer, Player **whitePlayer, AbstractGameLogic *gameLogic,
                          DisplayGame *displayGameOnConsole, GameFlow **gameFlow, RemotePlayer **client, int clientSocket){
    do {
        string commandStr;
        char command[50];
        memset(command, '\0', 50);
        cout << "Please type one of the following commands:" << endl;
        cout << "1. start <name>" << endl;
        cout << "2. list_games" << endl;
        cout << "3. join <name>" << endl;
        cout << "4. play <X> <Y>" << endl;
        cout << "5. close <name>" << endl;

        //wait for the client to type one of the commands
        getline(cin, commandStr);
        memcpy(command, commandStr.c_str(), commandStr.size());
        if (commandStr.find("start") != -1){
            commandsSender(clientSocket, command);
            serverResponseToStartCommand(clientSocket);

        }
        else if (commandStr.find("list_games") != -1){
            commandsSender(clientSocket, command);
            serverResponseToListGamesCommand(clientSocket);
        }
        else if (commandStr.find("join") != -1){
            commandsSender(clientSocket, command);
            joinAndPlay(blackPlayer, whitePlayer, gameLogic, displayGameOnConsole, gameFlow, client, clientSocket);
            break;
        }
        else if (commandStr.find("play") != -1){
            commandsSender(clientSocket, command);
        }
        else if (commandStr.find("close") != -1){
            commandsSender(clientSocket, command);
        }
    } while(true);
    return;
}

void createRemoteEnemyGameFlow(Player **blackPlayer, Player **whitePlayer, AbstractGameLogic *gameLogic,
                               DisplayGame *displayGameOnConsole, GameFlow **gameFlow) {
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

    typeAndSendCommandsToServer(blackPlayer, whitePlayer, gameLogic, displayGameOnConsole, gameFlow, &client, clientSocket);
}

void gameMenu(Player **blackPlayer, Player **whitePlayer, AbstractGameLogic *gameLogic, DisplayGame *displayGameOnConsole, GameFlow **gameFlow){
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
                createRemoteEnemyGameFlow(blackPlayer, whitePlayer, gameLogic, displayGameOnConsole, gameFlow);
                break;
            }
    }
}

int main() {

    //creating an instance of Board object
    Board *board = new Board();
    // Player *blackPlayer = new HumanPlayer(BLACK);
    Player *blackPlayer;
    Player *whitePlayer;
    AbstractGameLogic *gameLogic = new GameLogic(board);
    DisplayGame *displayGameOnConsole = new DisplayGameOnConsole(board);
    GameFlow *gameFlow;

    gameMenu(&blackPlayer, &whitePlayer, gameLogic, displayGameOnConsole, &gameFlow);

    gameFlow->playTheGame();

    //delete created objects

    /*we put 'delete board' in comment because in the current implementation the board is
    deleted within the 'GameLogic' destructor*/
    //delete board;
    delete blackPlayer;
    delete whitePlayer;
    //deletes the board as well
    delete gameLogic;
    delete displayGameOnConsole;
    delete gameFlow;
    return 0;
}


