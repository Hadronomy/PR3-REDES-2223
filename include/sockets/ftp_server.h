#pragma once

#include <list>

#include "ftp_command_registry.h"
#include "ftp_commands.h"
#include "ftp_command.h"

namespace sockets {

const FTPCommandRegistry DEFAULT_FTP_REGISTRY = FTPCommandRegistry()
  .Register(std::unique_ptr<FTPCommand>(new UserCommand()));

class ClientConnection;

class FTPServer {
 public:
  FTPServer(const FTPCommandRegistry& cmd_registry, const int port = 21) 
    : cmd_registry_(cmd_registry), port_(port) {}
  FTPServer(const int port) 
    : FTPServer(DEFAULT_FTP_REGISTRY) {}
  
  inline const FTPCommandRegistry& GetCommandRegistry() const { return cmd_registry_; }

  void Run();
  void Stop();

 private:
  FTPCommandRegistry cmd_registry_;
  int port_;
  int tcp_socket_;
  std::list<ClientConnection> connections_;
};

}
