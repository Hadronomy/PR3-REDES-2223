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

#include "sockets/program.h"
#include "sockets/utils.h"

int main(const int argc, const char* argv[]) {
  try {
    sockets::Program program;
    program.Run(argc, argv);
  } catch (const std::exception& e) {
    sockets::PrintException(e);
  }
  return 0;
}
