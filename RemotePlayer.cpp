//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "RemotePlayer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

using namespace std;

RemotePlayer::RemotePlayer(Sign playerSign, const char *serverIP, int serverPort):
        Player(playerSign), serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
}

RemotePlayer::RemotePlayer(RemotePlayer *otherPlayer) : Player(otherPlayer){

}

Sign RemotePlayer::getPlayerSign() const {
    return playerSign;
}

void RemotePlayer::setPlayerSign(Sign playerSign) {
    this->playerSign = playerSign;
}

int RemotePlayer::getPlayerScore() const {
    return playerScore;
}

void RemotePlayer::setPlayerScore(int addToPlayerScore) {
    this->playerScore += addToPlayerScore;
}

RemotePlayer::~RemotePlayer() {

}

int RemotePlayer::connectToServer() {
    // Create a socket point
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }
    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIP, &address)) {
        throw "Can't parse IP address";
    }
    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *)&address, sizeof
            address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }
    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *)&address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *)&serverAddress.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    // htons converts values between host and network byte orders
    serverAddress.sin_port = htons(serverPort);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
    cout << "Connected to server" << endl;
    return this->clientSocket;
}

void RemotePlayer::sendCell(int x, int y) {
    int n;
    // write the x coordinate argument to the socket
    n = write(clientSocket, &x, sizeof(x));
    if (n == -1) {
        throw "Error in writing the cell to socket";
    }
    // write the y coordinate argument to the socket
    n = write(clientSocket, &y, sizeof(y));
    if (n == -1) {
        throw "Error in writing the cell to socket";
    }
}

Point RemotePlayer::receiveCell() {
    int x, y;
    int n;
    // read the x coordinate argument from the socket
    n = read(clientSocket, &x, sizeof(x));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    // read the y coordinate argument from the socket
    n = read(clientSocket, &y, sizeof(y));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    Point receivedCell(x, y);
    return receivedCell;
}



