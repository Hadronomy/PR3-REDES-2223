#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <cerrno>
#include <exception>
#include <memory>
#include <netdb.h>
#include <thread>

#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <iostream>
#include <dirent.h>

#include "sockets/client_connection.h"
#include "sockets/ftp_server.h"

namespace sockets {

ClientConnection::ClientConnection(int control_socket, int data_socket) {
  char buffer[MAX_BUFFER];
  control_socket_ = control_socket;
  data_socket_ = data_socket;
  file_descriptor_ = fdopen(control_socket_, "a+");
  if (file_descriptor_ == nullptr) {
    std::cout << "Connection closed" << std::endl;
    // FIXME: This is a little weird
    fclose(file_descriptor_);
    close(control_socket_);
    is_ok_ = false;
    return;
  }
  is_ok_ = true;
  control_socket_ = -1;
}

ClientConnection::~ClientConnection() {
  if (is_ok_) {
    fclose(file_descriptor_);
    close(control_socket_);
  }
}

void ClientConnection::Stop() {
  close(data_socket_);
  close(control_socket_);
  control_socket_ = -1;
}
 
int ClientConnection::ConnectTCP(uint32_t address, uint16_t port) {
  try {
    struct sockaddr_in data_address;
    data_address.sin_family = AF_INET;
    data_address.sin_addr.s_addr = address;
    data_address.sin_port = htons(port);
    return connect(data_socket_, (struct sockaddr*)&data_address, sizeof(data_address));
  } catch(...) {
    std::throw_with_nested(std::runtime_error("Failed to bind tcp"));
  }
}

void ClientConnection::WaitForRequests(const FTPServer& server) {
  if (!is_ok_) {
    return;
  }
  if (send(control_socket_, "Welcome to FTP\n", strlen("Welcome FTP\n"), 0) != strlen("Welcome to FTP\n")) {
    std::cout << "Send failed" << std::endl;
  }
  fprintf(file_descriptor_, "220 Service Ready\n");
  while (data_socket_ != -1) {
    std::cout << "Waiting from command in socket..." << std::endl;
    fscanf(file_descriptor_, "%s", command_);
    std::string cmd_str(command_);
    auto& registry = server.GetCommandRegistry();
    registry.TryExecute(cmd_str, *this);
    std::cout << "Executed " << cmd_str << " command from socket" << std::endl;
  }
}

};
