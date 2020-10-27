#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include "../ClientSocket/ClientSocket.h"

#define SCOKETERROR -1
#define SOCKET int
#define LENGTH 2048
#define print(x) std::cout << x
#define println(x) std::cout << x << std::endl

int ErrorCheck(int, const char*);
int PthreadErrorCheck(int, const char*);
void StringOverwriteStdout();
vector<string> Split(const string &s, char delim);
void SendDataToServer(std::string, SOCKET);
std::string ReadResponseFromServer(SOCKET);