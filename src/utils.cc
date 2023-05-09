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

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <vector>
#include <string>

#include "sockets/utils.h"
#include "sockets/colors.h"

namespace sockets {

/**
 * @brief Divides the input_string into tokens using the given separator
 * @param input_string
 * @param separator
 * @return
 */
std::vector<std::string> Tokenize(const std::string& input_string, const char separator) {
  std::vector<std::string> result;
  std::stringstream current_token;
  for (const auto& current_char : input_string) {
    if (current_char == separator) {
      if (!current_token.str().empty()) {
        result.emplace_back(current_token.str());
        current_token.str(std::string());
      }
      continue;
    }
    current_token << current_char;
  }
  if (!current_token.str().empty()) {
    result.emplace_back(current_token.str());
    current_token.str(std::string());
  }
  return result;
}

/**
 * @brief Divides the input_string into tokens using the given separator
 * @param input_string
 * @param separator
 * @return
 */
std::vector<std::string> Tokenize(const std::string& input_string, const std::string& separator) {
  std::vector<std::string> result;
  std::stringstream buffer;
  for (int i = 0; i < input_string.size(); ++i) {
    const auto& kCurrentChar = input_string.at(i);
    bool found = false;
    for (int j = 0; j < separator.size(); ++j) {
      const auto& kSeparatorChar = separator.at(j);
      const auto& kDisplacedChar = input_string.at(i + j);
      if (kSeparatorChar == kDisplacedChar) {
        found = true;
        continue;
      }
      found = false;
      break;
    }
    if (!found) {
      buffer << kCurrentChar;
      continue;
    }
    if (!buffer.str().empty()) {
      result.emplace_back(buffer.str());
      buffer.str(std::string());
    }
    i += separator.size() - 1;
  }
  if (!buffer.str().empty()) {
    result.emplace_back(buffer.str());
    buffer.str(std::string());
  }
  return result;
}

/**
 * @brief Returns the uppercase version of the provided input_string
 * @param input_string The string to be converted
 * @return
 */
std::string ToUpper(std::string input_string) {
  std::transform(input_string.begin(), input_string.end(), input_string.begin(), ::toupper);
  return input_string;
}

/**
 * @brief Returns a vector with all the lines of the file at the provided input_file_path
 * @param input_file_path
 * @return
 */
std::vector<std::string> ReadFileLines(const std::string& input_file_path) {
  std::ifstream input_file(input_file_path);
  if (!input_file.is_open()) {
    std::cerr << "The file at " << input_file_path << " could not be opened" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::vector<std::string> lines;
  std::string current_line;
  while (!input_file.eof()) {
    std::getline(input_file, current_line);
    lines.emplace_back(current_line);
  }
  return lines;
}

/**
 * @brief Removes instances of the unwanted_char within the given input_string
 * @param input_string
 * @param unwanted_char
 * @return
 */
std::string RemoveInstancesOf(const std::string& input_string, const char unwanted_char) {
  std::stringstream result;
  for (const auto& character : input_string) {
    if (character == unwanted_char) continue;
    result << character;
  }
  return result.str();
}

/**
 * @brief Used to print nested exceptions
 * @param e
 */
void PrintException(const std::exception& e) {
  std::cerr << "\u001b[37;41;1m" << " ERROR " << Colorize::Reset << " " << e.what() << '\n';
  try {
    std::rethrow_if_nested(e);
  } catch(const std::exception& nested_exception) {
    PrintException(nested_exception);
  } catch(...) {}
}

}
