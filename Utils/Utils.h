#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>

#define SCOKETERROR -1
#define SOCKET int
#define LENGTH 2048

int ErrorCheck(int, const char*);
int PthreadErrorCheck(int, const char*);
void StringOverwriteStdout();