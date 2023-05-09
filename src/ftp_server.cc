#include <cerrno>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <exception>
#include <memory>
#include <list>
#include <thread>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <system_error>
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>

#include "sockets/client_connection.h"
#include "sockets/ftp_server.h"

namespace sockets {

int DefineSocketTCP(const int port) {
  return -1;
}

void RunClientConnection(const FTPServer& server, const std::shared_ptr<ClientConnection> client_connection) {
  client_connection->WaitForRequests(server);
}

void FTPServer::Run() {
  try {
    struct sockaddr_in input;
    int server_socket;
    socklen_t lenght = sizeof(input);
    tcp_socket_ = DefineSocketTCP(port_);
    while (true) {
      server_socket = accept(tcp_socket_, (struct sockaddr*)&input, &lenght);
      if (server_socket < 0) {
        throw std::system_error(errno, std::system_category());
      }
      auto connection = std::make_shared<ClientConnection>(server_socket);
      std::thread thread(RunClientConnection, *this, connection);
    }
  } catch (...) {
    std::throw_with_nested(std::runtime_error("while running the FTPServer"));
  }
}

void FTPServer::Stop() {
  close(tcp_socket_);
  shutdown(tcp_socket_, SHUT_RDWR);
}

}
