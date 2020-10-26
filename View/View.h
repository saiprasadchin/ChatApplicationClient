#pragma once
#include <iostream>
#include "../Utils/Utils.h"

using namespace std;

#define REGISTRATION 1
#define VALID "0"
#define INVALID "1"

class View
{
public:
    void DisplayWelcomeMessage();
    bool RegistrationAndLogin(SOCKET);
    string registration(SOCKET);
};