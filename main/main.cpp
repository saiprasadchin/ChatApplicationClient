#include "../ClientSocket/ClientSocket.h"
#include "../View/View.h"

int main() {

    const char *ip = "127.0.0.1";
	int port = 54000;

    View view;
    view.DisplayWelcomeMessage();

    ClientSocket client_socket;
    SOCKET sockfd = client_socket.ConnectToServer(ip, port);
    
    return 0;
}