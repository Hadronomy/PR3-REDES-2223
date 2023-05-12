
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
  ClientConnection(int control_socket, int data_socket);
  ~ClientConnection();
  
  void WaitForRequests(const FTPServer& server);
  void Stop();

private:
  bool is_ok_;
  FILE* file_descriptor_;
  char command_[MAX_BUFFER];
  char arg_[MAX_BUFFER];
  int data_socket_;
  int control_socket_;
};

}
