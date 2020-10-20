#include "ClientSocket.h"
#include "../Utils/Utils.h"

ClientSocket::~ClientSocket() {
    close(client_socket);
}

SOCKET ClientSocket::ConnectToServer(const char* server_ip,int server_port) {
  struct sockaddr_in servAddr;

  ErrorCheck((client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)),
            "Error: socket() failed");

  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = inet_addr(server_ip);
  servAddr.sin_port = htons(server_port);

  ErrorCheck(connect(client_socket, (struct sockaddr *) &servAddr, sizeof(servAddr)),
            "Connection to server failed");

  return client_socket;
}