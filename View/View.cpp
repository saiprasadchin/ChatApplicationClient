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

string View::login(SOCKET sockfd) {
    string user_name, pass_word, auth;

    print("Enter your registered username : ");
    cin >> user_name;
    print("Enter the password : ");
    cin >> pass_word;

    auth = "AUTHENTICATE " + user_name + " " + pass_word;

    SendDataToServer(auth, sockfd);

    return ReadResponseFromServer(sockfd);
}

bool View::RegistrationAndLogin(SOCKET sockfd) {

    bool login_flag = false;
    bool exit_falg = true;
    int choice;

    while(exit_falg) {
       println("********Select Option********");
       println("1) Registration \n2) login");
       cin >> choice;

       switch ( choice )
       {
            case REGISTRATION:
                while(VALID == registration(sockfd)) {
                    cout<<"\033[1;31mYour username has already been registered. Please try again\033[0m\n\n";
                }
                cout<<"\033[1;32mUser Registered\033[0m\n\n";
                break;
            case LOGIN:
		        while( INVALID == login(sockfd) ) {
	    	        cout<<"\033[1;31mWrong Username/Password\033[0m\n\n";
		        }
		        cout<<"\033[1;32mUser Authenticated\033[0m\n\n";
                login_flag = true;
                exit_falg = false;
                break;
            default:
                cout << "\033[1;31mINVALID INPUT\033[0m" << endl;
                break;
       }
   }
   return login_flag;
}