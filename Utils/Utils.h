#pragma once
#include "../ClientSocket/ClientSocket.h"
#include <mutex>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>


#define SCOKETERROR -1
#define SOCKET int
#define LENGTH 2048
#define print(x) std::cout << x
#define println(x) std::cout << x << std::endl

using namespace std;
//std::mutex mutex;

int ErrorCheck(int, const char*);
int PthreadErrorCheck(int, const char*);
void StringOverwriteStdout();
vector<std::string> Split(const std::string &s, char delim);
void SendDataToServer(std::string, SOCKET);
std::string ReadResponseFromServer(SOCKET);