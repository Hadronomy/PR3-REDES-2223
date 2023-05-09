
#pragma once

#include <cstdio>
#include <cstdint>
#include <memory>

#include <pthread.h>

namespace sockets {

const int MAX_BUFFER = 1000;

class FTPServer;

class ClientConnection {
 public:
  ClientConnection(const int socket);
  ~ClientConnection();
  
  void WaitForRequests(const FTPServer& server);
  void Stop();

private:
  bool is_ok_;
  std::unique_ptr<FILE> file_descriptor_;
  char arg_[MAX_BUFFER];
  int data_socket_;
  int control_socket_;
};

}
