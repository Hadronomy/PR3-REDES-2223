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

void FTPServer::CreateSocketsTCP() {
  try {
    std::cout << "Creating sockets..." << std::endl;
    int opt = 1;

    struct sockaddr_in control_address;
    control_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (control_socket_ < 0) {
      throw std::system_error(errno, std::system_category());
    }
    if (setsockopt(control_socket_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
      throw std::system_error(errno, std::system_category());
    }
    control_address.sin_family = AF_INET;
    control_address.sin_addr.s_addr = INADDR_ANY;
    control_address.sin_port = htons(port_);
    if (bind(control_socket_, (struct sockaddr*)&control_address, sizeof(control_address)) < 0) {
      throw std::system_error(errno, std::system_category());
    }
    if (listen(control_socket_, 3)) {
      throw std::system_error(errno, std::system_category());
    }
  } catch (...) {
    std::throw_with_nested(std::runtime_error("While configuring TCP Socket"));
  }
}

void RunClientConnection(const FTPServer& server, const std::shared_ptr<ClientConnection> client_connection) {
  client_connection->WaitForRequests(server);
}

void FTPServer::Run() {
  try {
    std::cout << "Running server..." << std::endl;
    struct sockaddr_in control_address;
    struct sockaddr_in data_address;
    socklen_t control_address_lenght = sizeof(control_address);
    socklen_t data_address_lenght = sizeof(data_address);
    CreateSocketsTCP();
    std::vector<std::thread> threads;
    while (true) {
      std::cout << "Accepting new connections..." << std::endl;
      std::cout << "Awaiting for control socket..." << std::endl;
      int new_control_socket = accept(control_socket_, (struct sockaddr*)&control_address, &control_address_lenght);
      if (new_control_socket < 0) {
        throw std::system_error(errno, std::system_category());
      }
      std::cout << "New connection for command socket, socket fd is " << new_control_socket
        << ", ip is: " << inet_ntoa(control_address.sin_addr) << ", port : "
        << ntohs(control_address.sin_port) << std::endl;

      auto connection = std::make_shared<ClientConnection>(new_control_socket);
      threads.emplace_back(RunClientConnection, *this, connection);
    }
  } catch (...) {
    std::throw_with_nested(std::runtime_error("While running the FTPServer"));
  }
}

void FTPServer::Stop() {
  close(control_socket_);
  shutdown(control_socket_, SHUT_RDWR);
}

}
