#include "Utils.h"

int ErrorCheck(int expression, const char* message) {
    if(expression == SCOKETERROR) {
        perror(message);
        exit(0);
    }
    return expression;
}

int PthreadErrorCheck(int expression, const char* message) {
    if(expression != 0 ) {
        perror(message);
        exit(0);
    }
    return expression;
}

void StringOverwriteStdout() {
    printf("%s", "> ");
    fflush(stdout);
}

vector<std::string> Split(const std::string &s, char delim) {
    stringstream ss(s);
    std::string item;
    vector<std::string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

void SendDataToServer(std::string message, SOCKET sockfd) {
    send(sockfd, message.c_str(), message.size() + 1, 0);
}

std::string ReadResponseFromServer(SOCKET sockfd) {
    char buffer[LENGTH] = {};

    int receive = recv(sockfd, buffer, LENGTH, 0);
    if (receive > 0) {
        return (std::string)buffer;
    } else {
        print("ERROR : Recieve");
    }
    return "";
}