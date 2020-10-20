#pragma once
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <iostream>
#include "../Utils/Utils.h"

#define SOCKET int

using namespace std;

class ClientSocket
{
private:
    SOCKET client_socket;
public:
    ~ClientSocket();
    SOCKET ConnectToServer(const char* serverIP,int serverPort);
};