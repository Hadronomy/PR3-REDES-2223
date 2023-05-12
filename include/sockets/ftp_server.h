#pragma once

#include <list>
#include <memory>

#include <netinet/in.h>

#include "ftp_command_registry.h"
#include "ftp_commands.h"
#include "ftp_command.h"
#include "client_connection.h"

namespace sockets {

const FTPCommandRegistry DEFAULT_FTP_REGISTRY = FTPCommandRegistry()
  .Register(std::shared_ptr<FTPCommand>(new UserCommand()))
  .Register(std::shared_ptr<FTPCommand>(new PassCommand()))
  .Register(std::shared_ptr<FTPCommand>(new SystCommand()))
  .Register(std::shared_ptr<FTPCommand>(new TypeICommand()))
  .Register(std::shared_ptr<FTPCommand>(new PortCommand()))
  .Register(std::shared_ptr<FTPCommand>(new PassiveCommand()))
  .Register(std::shared_ptr<FTPCommand>(new StorCommand()))
  .Register(std::shared_ptr<FTPCommand>(new RetrCommand()))
  .Register(std::shared_ptr<FTPCommand>(new QuitCommand()));

class FTPServer {
 public:
  FTPServer(const FTPCommandRegistry& cmd_registry = DEFAULT_FTP_REGISTRY, const int port = 21) 
    : cmd_registry_(cmd_registry), port_(port), control_socket_(-1), data_socket_(-1), connections_() {}
  FTPServer(const int port) 
    : FTPServer(DEFAULT_FTP_REGISTRY, port) {}
  
  inline const FTPCommandRegistry& GetCommandRegistry() const { return cmd_registry_; }

  void Run();
  void Stop();
  void CreateSocketsTCP();

 private:
  FTPCommandRegistry cmd_registry_;
  int port_;
  int control_socket_;
  int data_socket_;
  std::list<ClientConnection> connections_;
};

}
