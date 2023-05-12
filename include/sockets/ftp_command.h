
#pragma once

#include <string>

namespace sockets {

class ClientConnection;

/**
 * @brief Utility class 
 * 
 */
class FTPCommand {
 public:
  virtual std::string Keyword() const = 0;
  virtual void Run(ClientConnection& client) const = 0;
};

}
