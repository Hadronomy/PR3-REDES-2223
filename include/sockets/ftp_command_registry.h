
#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "ftp_command.h"

namespace sockets {

/**
 * @brief Utility class for storing FTP Commands
 * 
 */
class FTPCommandRegistry {
 public:
  FTPCommandRegistry() {}

  /**
   * @brief Adds a new command into the registry
   * 
   * @param command 
   * @return FTPCommandRegistry& 
   */
  inline FTPCommandRegistry& Register(const std::unique_ptr<FTPCommand> command) {
    commands_.emplace(command->Keyword(), command);
    return *this;
  }

  /**
   * @brief Tries to execute the passed command
   * 
   * @param input 
   * @return true
   * @return false
   */
  inline bool TryExecute(const std::string& input) const {
    if (Exists(input)) {
      commands_.at(input)->Run();
      return true;
    }
    return false;
  }
  
  /**
   * @brief Returns whether the passed commands exists
   * within the registry 
   *
   * @param cmd 
   * @return true 
   * @return false 
   */
  inline bool Exists(const std::string& cmd) const {
    return commands_.count(cmd);
  }

 private:
  std::map<std::string, std::unique_ptr<FTPCommand>> commands_; 
};

}
