#include "View.h"

void View::DisplayWelcomeMessage() {
    cout << "Welcome To Client Application" << endl;
}

string View::registration(SOCKET sockfd) {

    string user_name, pass_word, auth;

    print("Enter username: ");
    cin >> user_name;
    print("Enter the password: ");
    cin >> pass_word;
    auth = "REGISTER " + user_name + " " + pass_word;

    SendDataToServer(auth, sockfd);

    return ReadResponseFromServer(sockfd);
}

bool View::RegistrationAndLogin(SOCKET sockfd) {

   bool exit_falg = true;
   int choice;

    while(exit_falg) {
       println("********Select Option********");
       println("1) Registration");
       cin >> choice;

       switch ( choice )
       {
            case REGISTRATION:
                while(VALID == registration(sockfd)) {
                    cout<<"\033[1;31mYour username has already been registered. Please try again\033[0m\n\n";
                }
                cout<<"\033[1;32mUser Registered\033[0m\n\n";
                break;
            default:
                cout << "\033[1;31mINVALID INPUT\033[0m" << endl;
                break;
       }

   }
   return true;
}