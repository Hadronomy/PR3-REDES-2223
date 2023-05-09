
#pragma once

#include "sockets/ftp_command.h"

namespace sockets {

class UserCommand : public FTPCommand {
 public:
  inline std::string Keyword() const override { return "USER"; }

  inline void Run() const override {
    
  }
};

}