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

#include <string>
#include <vector>
#include <map>
#include <exception>

namespace sockets {

const char kEmptyStringChar = '&';

std::vector<std::string> Tokenize(const std::string& input_string, const char separator = ' ');
std::vector<std::string> Tokenize(const std::string& input_string, const std::string& separator);
std::string RemoveInstancesOf(const std::string& input_string, const char unwanted_char);
template<class TKey, class TValueContainer, class TValue>
void AddCreate(std::map<TKey, TValueContainer>& map, const TKey& key, const TValue& value) {
  if (!map.count(key)) {
    map.emplace(key, TValueContainer());
  }
  map.at(key).emplace(value);
}
std::string ToUpper(std::string input_string);
std::vector<std::string> ReadFileLines(const std::string& input_file_path);
void PrintException(const std::exception& e);

}
