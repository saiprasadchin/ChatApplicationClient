#include "../ClientSocket/ClientSocket.h"
#include "../View/View.h"

SOCKET sockfd = 0;
volatile sig_atomic_t flag;

void CatchCtrlCAndExit(int sig);
void* SendMessageHandler(void* arg);
void* ReceiveMessageHandler(void* arg);

int main() {

    const char *ip = "127.0.0.1";
	int port = 54000;

    signal(SIGINT, CatchCtrlCAndExit);

    View view;
    view.DisplayWelcomeMessage();

    ClientSocket client_socket;
    sockfd = client_socket.ConnectToServer(ip, port);

    pthread_t send_msg_thread;
    PthreadErrorCheck(pthread_create(&send_msg_thread, NULL, &SendMessageHandler, NULL),
      "ERROR: pthread\n");

	pthread_t recv_msg_thread;
    PthreadErrorCheck(pthread_create(&recv_msg_thread, NULL, &ReceiveMessageHandler, NULL),
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

void* SendMessageHandler(void* arg) {
  char message[LENGTH] = {};
  while(1) {
  	StringOverwriteStdout();
    fgets(message, LENGTH, stdin);
    message[strlen(message) - 1] = '\0';
    if (strcmp(message, "exit") == 0) {
		break;
    } else {
        if(strlen(message) > 2)
            send(sockfd, message, strlen(message), 0);
    }
	bzero(message, LENGTH);
  }
  CatchCtrlCAndExit(2);
  return NULL;
}

void* ReceiveMessageHandler(void* arg) {
	char message[LENGTH] = {};
  while (1) {
      int receive = recv(sockfd, message, LENGTH, 0);
      if (receive > 0) {
          cout << message << endl;
      } else if (receive == 0) {
        break;
      } else {
        cout << "ERROR " << endl;
      }  
	memset(message, 0, sizeof(message));
  }
  return NULL;
}