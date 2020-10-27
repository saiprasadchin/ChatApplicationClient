#include "../ClientSocket/ClientSocket.h"
#include "../View/View.h"

SOCKET sockfd = 0;
int help_exit_flag = 1;
volatile sig_atomic_t flag;

void CatchCtrlCAndExit(int sig);
void* SendMessageHandler(void* arg);
void* ReceiveMessageHandler(void* arg);
void* GetOnLineClients(void* arg);
View view;

int main() {

	const char *ip = "127.0.0.1";
	int port = 54000;

	signal(SIGINT, CatchCtrlCAndExit);

	view.DisplayWelcomeMessage();

	ClientSocket client_socket;
	sockfd = client_socket.ConnectToServer(ip, port);

	if(!view.RegistrationAndLogin( sockfd ))
		exit(0);

	pthread_t send_msg_thread;
	PthreadErrorCheck(pthread_create(&send_msg_thread, NULL, &SendMessageHandler, NULL),
		"ERROR: pthread\n");

	pthread_t recv_msg_thread;
	PthreadErrorCheck(pthread_create(&recv_msg_thread, NULL, &ReceiveMessageHandler, NULL),
		"ERROR: pthread\n");

	pthread_t get_online_clients_list;
  	PthreadErrorCheck(pthread_create(&get_online_clients_list, NULL, &GetOnLineClients, NULL),
        "ERROR: pthread\n");
		
	while (1){
		if(flag){
			printf("\nBye\n");
			break;
		}
	}

	return 0;
}

void CatchCtrlCAndExit(int sig) {
	flag = 1;
}

void* GetOnLineClients(void* arg) {
	char online[] = {"ONLINE"};
	while(1) {
    	if(help_exit_flag) {
      		send(sockfd, online, strlen(online), 0);
      		sleep(100);
    	}
  	}
	bzero(online, strlen(online));
	return NULL;
}

void* SendMessageHandler(void* arg) {
	char message[LENGTH] = {};
  	string buffer = ""; 
  	while(1) {
  		StringOverwriteStdout();
    	fgets(message, LENGTH, stdin);
    	message[strlen(message) - 1] = '\0';
    	if (strcmp(message, "exit") == 0) {
			break;
    	}
    	if(strcmp(message, "--help") == 0) {
      		help_exit_flag = 0;
      		send(sockfd, message, strlen(message), 0);
      		view.DisplayHelpCommands(message, sockfd);
      		help_exit_flag = 1;
      		view.display();
    	} else {
      		send(sockfd, message, strlen(message), 0);
		    view.addMessage(message);
		  	view.display();
    	}
		bzero(message, LENGTH);;
  	}
  	CatchCtrlCAndExit(2);
  	return NULL;
}

void* ReceiveMessageHandler(void* arg) {
	char message[LENGTH] = {};
	while (1) {
    	if(help_exit_flag) {
      		int receive = recv(sockfd, message, LENGTH, 0);
      		if (receive > 0) {
        		if(strcmp(message, "$") == 0) {
          			cout << message << endl;
        		} else if(strstr(message, "ONLINE") == 0) {
          			view.addMessage(message);
          			view.display();
          			StringOverwriteStdout();
        		} else {
          			view.UpdateOnLineClinetsList(message);
        		}
      		} else if (receive == 0) {
        	break;
     		} else {
				cout << "ERROR " << endl;
      		}
    	}  
		memset(message, 0, sizeof(message));
  	}
  return NULL;
}
