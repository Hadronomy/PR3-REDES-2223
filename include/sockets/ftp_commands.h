
#pragma once

#include <cstdio>
#include <cstring>
#include <iostream>

#include "sockets/ftp_command.h"
#include "sockets/client_connection.h"

namespace sockets {

class UserCommand : public FTPCommand {
 public:
  inline std::string Keyword() const override { return "USER"; }

  inline void Run(ClientConnection& client) const override {
    auto file_descriptor = client.GetFileDescriptor();
    fscanf(file_descriptor, "%s", client.GetArgBuffer());
    fprintf(file_descriptor, "331 User name ok, need password\n");
  }
};

class PassCommand : public FTPCommand {
 public:
  inline std::string Keyword() const override { return "PASS"; }

  inline void Run(ClientConnection& client) const override {
    auto file_descriptor = client.GetFileDescriptor();
    auto arg_buffer = client.GetArgBuffer();
    fscanf(file_descriptor, "%s", arg_buffer);
    if (strcmp(arg_buffer, "1234") == 0) {
      fprintf(file_descriptor, "230 User logged in\n");
    } else {
      fprintf(file_descriptor, "530 Not logged in.\n");
    }
  }
};

class SystCommand : public FTPCommand {
 public:
  inline std::string Keyword() const override { return "SYST"; }

  inline void Run(ClientConnection& client) const override {
    auto file_descriptor = client.GetFileDescriptor();
    fprintf(file_descriptor, "215 UNIX Type: L8.\n");
  }
};

class QuitCommand : public FTPCommand {
 public:
  inline std::string Keyword() const override { return "QUIT"; }

  inline void Run(ClientConnection& client) const override {
    //! FIXME: Closing server on `bye` command
    auto file_descriptor = client.GetFileDescriptor();
    fprintf(file_descriptor, "200 OK.\n");
    client.Stop();
  }
};

}
