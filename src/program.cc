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

#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "sockets/ftp_server.h"
#include "sockets/hourglass.h"
#include "sockets/program.h"
#include "sockets/utils.h"

namespace sockets {

Program::Program() : command_("ftp-server") {
  command_.SetPositionalArgumentsRange(0, 0);
  command_.GetArgs();
  std::stringstream description;
  description << R"()";
  command_.SetLong(description.str());
}

/**
 * @brief Executes the program
 * @param argc
 * @param argv
 */
void Program::Run(const int argc, const char *argv[]) {
  auto &cli = GetCli();
  cli.Parse(argc, argv);
  FTPServer server(2121);
  server.Run();
}

} // namespace sockets
