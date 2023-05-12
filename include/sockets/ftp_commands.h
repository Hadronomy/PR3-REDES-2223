
#pragma once

#include <cstdio>
#include <cstring>
#include <iostream>
#include <sys/types.h>

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

class TypeICommand : public FTPCommand {
 public:
  inline std::string Keyword() const override { return "TYPE"; }

  inline void Run(ClientConnection& client) const override {
    auto file_descriptor = client.GetFileDescriptor();
    fscanf(file_descriptor, "%s", client.GetArgBuffer());
    fprintf(file_descriptor, "200 OK.\n");
  }
};

class PortCommand : public FTPCommand {
 public:
  inline std::string Keyword() const override { return "PORT"; }

  inline void Run(ClientConnection& client) const override {
    auto file_descriptor = client.GetFileDescriptor();
    uint8_t addr1, addr2, addr3, addr4;
    uint8_t port1, port2;
    fscanf(file_descriptor, "%d,%d,%d,%d,%d,%d", &addr1, &addr2, &addr3, &addr4, &port1, &port2);
    uint32_t address = (addr1 << 24) | (addr2 << 16) | (addr3 << 8) | addr4;
    uint16_t port = (port1 << 8) | port2;
    client.ConnectTCP(address, port);
    fprintf(file_descriptor, "200 OK.\n");
  }
};

class PassiveCommand : public FTPCommand {
 public:
  inline std::string Keyword() const override { return "PASV"; }

  inline void Run(ClientConnection& client) const override {
    auto file_descriptor = client.GetFileDescriptor();
    fprintf(file_descriptor, "227 Entering Passive Mode (127,0,0,1,190,81)\n");
  }
};

class StorCommand : public FTPCommand {
 public:
  inline std::string Keyword() const override { return "STOR"; }

  inline void Run(ClientConnection& client) const override {
    auto file_descriptor = client.GetFileDescriptor();
    fscanf(file_descriptor, "%s", client.GetArgBuffer());
    fprintf(file_descriptor, "150 File creation ok\n");
  }
};

class RetrCommand : public FTPCommand {
 public:
  inline std::string Keyword() const override { return "RETR"; }

  inline void Run(ClientConnection& client) const override {
    auto file_descriptor = client.GetFileDescriptor();
    fprintf(file_descriptor, "150 File status ok; about to open data connection\n");
    fprintf(file_descriptor, "226 Closing data connection.\n");
    fprintf(file_descriptor, "2480 bytes received in 0.00 secs (33176.4 kB/s)\n");
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
