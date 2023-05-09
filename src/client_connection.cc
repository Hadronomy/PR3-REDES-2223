#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <cerrno>
#include <exception>
#include <memory>
#include <netdb.h>

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

ClientConnection::ClientConnection(int socket) {
  char buffer[MAX_BUFFER];
  control_socket_ = socket;
  file_descriptor_ = std::unique_ptr<FILE>(fdopen(socket, "a+"));
  if (file_descriptor_ == nullptr) {
    std::cout << "Connection closed" << std::endl;
    // FIXME: This is a little weird
    fclose(file_descriptor_.get());
    close(control_socket_);
    is_ok_ = false;
    return;
  }
  is_ok_ = true;
  data_socket_ = -1;
}

ClientConnection::~ClientConnection() {
  if (is_ok_) {
    fclose(file_descriptor_.get());
    close(control_socket_);
  }
}

void ClientConnection::Stop() {
  close(data_socket_);
  close(control_socket_);
}
 
int ConnectTCP(uint32_t address, uint16_t port) {
  try {
    // TODO: Connect TCP
  } catch(...) {
    std::throw_with_nested(std::runtime_error("Failed to bind tcp"));
  }
}

void ClientConnection::WaitForRequests(const FTPServer& server) {
  if (!is_ok_) {
    return;
  }
  while (true) {
    char command[MAX_BUFFER];
    fscanf(file_descriptor_.get(), "%s", command);
    std::string cmd_str(command);
    auto& registry = server.GetCommandRegistry();
    registry.TryExecute(cmd_str);
  }
}

};