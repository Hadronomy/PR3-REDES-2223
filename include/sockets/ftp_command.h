
#pragma once

#include <string>

namespace sockets {

/**
 * @brief Utility class 
 * 
 */
class FTPCommand {
 public:
  virtual std::string Keyword() const = 0;
  virtual void Run() const = 0;
};

}
