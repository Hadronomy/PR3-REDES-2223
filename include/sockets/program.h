/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingenierıa Informática
 * Asignatura: Redes y Sistemas Distribuidos
 * Curso: 2º
 * Práctica 3
 * Grado en Ingeniería Informática
 * Autor: Pablo Hernández Jiménez
 * Correo: alu0101495934@ull.edu.es
 */

#pragma once

#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <fstream>

#include "command.h"
#include "utils.h"

namespace sockets {

/**
 * @brief Defines main program functionality
 */
class Program {
 public:
  Program();

  /**
   * @brief Returns a modifiable reference of the cli
   * @return
   */
  inline Command& GetCli() { return command_; }

  void Run(const int argc, const char* argv[]);

 private:
  Command command_;
};


} // ayeda
