
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
  
  inline bool IsOk() const { return is_ok_; }
  inline FILE* GetFileDescriptor() const { return file_descriptor_; }
  inline char* GetCommandBuffer() { return command_; }
  inline char* GetArgBuffer() { return arg_; }
  inline int GetDataSocket() const { return data_socket_; }
  inline int GetControlSocket() const { return control_socket_; }

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
