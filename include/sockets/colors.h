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

#include <iostream>
#include <string>

namespace sockets {

/**
 * @brief Font colors identifiers for console logging
 *
 */
enum class ColorTint {
  kReset = 0,
  kBlack = 30,
  kRed = 31,
  kGreen = 32,
  kYellow = 33,
  kBlue = 34,
  kMagenta = 35,
  kAyedan = 36,
  kWhite = 37
};

/**
 * @brief Font styles identifiers for console logging
 *
 */
enum class FontStyle {
  kBold = 1,
  kUnderline = 4,
  kReversed = 7
};

/**
 * @brief Utility class that manages the styling of the output stream
 *
 */
class Colorize {
 public:
  Colorize(ColorTint color) : value_(static_cast<int>(color)) { }
  Colorize(FontStyle style) : value_(static_cast<int>(style)) { }
  Colorize(unsigned char code) : value_(static_cast<int>(code)) { }
  Colorize(const std::string& comple_code) : complete_code_(comple_code) { }

  static std::ostream &Reset(std::ostream &out) {
    return out << "\u001b[0m";
  }

  /**
   * @brief Colorizes the output stream
   * @return std::ostream&
   */
  std::ostream &operator()(std::ostream &out) const;
 private:
  int value_;
  std::string complete_code_;
};

std::ostream &operator <<(std::ostream &out, Colorize colorize);

}
