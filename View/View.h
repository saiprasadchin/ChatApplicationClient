#pragma once
#include <iostream>
#include "../Utils/Utils.h"

using namespace std;

#define UNSEEN_MESSAGES_FROM "UNSEEN_MESSAGES_FROM "
#define MESSAGES "MESSAGES "
#define REGISTRATION 1
#define LOGIN 2
#define VALID "0"
#define INVALID "1"

class View
{
    int MESSAGE_COUNT = 10;
    vector<string> messageList = { "","","","","","","","","",""};
    vector<string> online_clients_list;
public:
    void DisplayWelcomeMessage();
    bool RegistrationAndLogin(SOCKET);
    string registration(SOCKET);
    string login(SOCKET);
    void display();
    void addMessage(string);
    void UpdateOnLineClinetsList(string);
    void DisplayHelpCommands(string, SOCKET);
};