#include "View.h"

string user_id;
std::mutex mtx;
void View::DisplayWelcomeMessage() {
    cout << "Welcome To Client Application" << endl;
}

void View::DisplayHelpCommands(string help, SOCKET socket) {
    vector<string> command_data;
    command_data.push_back(help);
    while(1) {
        if(command_data.size() > 0) {
            if( command_data[0] == "--help") {
                system("clear");
                std::cout<<"You can try the following commands:"<<endl;
                std::cout<<"\033[1;32mchat : \033[1;35mGOTO CHAT WINDOW :\033[0m Start chat with your friend\033[0m"<<endl;
                std::cout<<"\033[1;32munseen :\033[0m See friends with pending messages\033[1;"<<endl;
                std::cout<<"\033[1;32munseen \033[3m[\033[1;35musername\033[1;32m] :\033[0m get pending from message friend\033[1;"<<endl;
                std::cout<<"\033[1;32mallmessages \033[3m[\033[1;35musername\033[1;32m] :\033[0m see all message\033[1;"<<endl;
            } else if( command_data[0] == "chat" ) {
                SendDataToServer("chat ",socket);
                break;
            } else if( command_data[0] == "unseen" ) {
                if(command_data.size() == 1) {
                    SendDataToServer(UNSEEN_MESSAGES_FROM, socket);
                    string unseen_friends = ReadResponseFromServer(socket);
                    vector<string> list = Split(unseen_friends, ' ');
                    for (int i = 0; i < list.size(); i++) {
                        std::cout <<"\033[1;32m"<< list[i] <<"\033[0m\n";
                    }
                } else if(command_data.size() == 2) {
                    SendDataToServer(MESSAGES + command_data[1], socket);
                    string unseen_messages = ReadResponseFromServer(socket);
                    vector<string> list = Split(unseen_messages, ' ');
                    std::cout <<"\033[1;32m"<< list[0] <<"\033[0m\n";
                    for (int i = 1; i < list.size(); i++) {
                        std::cout << list[i] << endl;
                    }
                } else {
                     std::cout<<"Use the command properly!"<<endl<<endl;
                }
            } else if( command_data[0] == "allmessages" ) {
                if(command_data.size() == 2) {
                    SendDataToServer(ALL_MESSAGES + command_data[1], socket);
                    string unseen_messages = ReadResponseFromServer(socket);
                    vector<string> list = Split(unseen_messages, ' ');
                    std::cout <<"\033[1;32m"<< list[0] <<"\033[0m\n";
                    for (int i = 1; i < list.size(); i++) {
                        std::cout << list[i] << endl;
                    }
                } else{
                    std::cout<<"Use the command properly!"<<endl<<endl;
                }
        } else {
                std::cout << "\033[1;31m****INVALID COMMAND****\033[0m" << endl;
            }
        }
        string command = "";
        std::cout << "\n\x1B[36mENTER YOUR COMMAND\033[0m$ ";
        getline(cin, command);
        command_data = Split(command,' ');
    }
}

void View::display() {
    std::lock_guard<std::mutex> lck (mtx);
    system("clear");
    if (messageList.size() > MESSAGE_COUNT) {
        int j = 0;
        cout << "\033[1;35m=== WELCOME TO THE CHATROOM ===\033[0m\n" << "\x1b[1m\x1B[93m"
              << "USER : " << user_id << "\033[0m\x1b[0m\n";
        int count = messageList.size() - MESSAGE_COUNT;
        for (int i = count; i < messageList.size(); i++) {
            printf("%-60s", messageList[i].c_str());
            if (j < online_clients_list.size())
                cout <<"\033[1;32m"<< online_clients_list[j++] <<"\033[0m\n";
            else
                cout << endl;
        }
        printf("%+80s", "\033[1;35mUSE : --help command\033[0m\n");
    }
}

void View::addMessage(string buffer) {
	messageList.push_back(buffer);
}

void View::UpdateOnLineClinetsList(string online_clients) {
      online_clients_list = Split(online_clients,' ');
      display();
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
    user_id = user_name;
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