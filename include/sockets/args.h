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

#include <map>
#include <string>
#include <typeinfo>
#include <any>
#include <iostream>

namespace sockets {

class Argument { };
template<class TType>
class ArgumentValue : Argument {
 public:
  ArgumentValue() : Argument() { }
  TType GetValue() const { return value_; }
 private:
  TType value_;
};

class Args {
 public:
  Args() { }

  Args& Parse(const std::string& arg, const std::string& next_token);

  template<class TType>
  inline bool IsType(const std::string& name) {
    return expected_arguments_.at(name) == typeid(TType).name();
  }

  inline bool IsBool(const std::string& name) {
    return IsType<bool>(name);
  }

  inline bool IsString(const std::string& name) {
    return IsType<std::string>(name);
  }

  inline bool IsInt(const std::string& name) {
    return IsType<int>(name);
  }

  inline Args& Expect(const std::string& long_name, const std::string& short_name, const std::string& argument_type) {
    expected_arguments_.emplace(long_name, argument_type);
    if (!short_name.empty())
      aliases_.emplace(short_name, long_name);
    return static_cast<Args&>(*this);
  }

  inline Args& ExpectBool(const std::string& long_name, const std::string& short_name = "") {
    return Expect(long_name, short_name, typeid(bool).name());
  }

  inline Args& ExpectString(const std::string& long_name, const std::string& short_name = "") {
    return Expect(long_name, short_name, typeid(std::string).name());
  }

  inline Args& ExpectInt(const std::string& long_name, const std::string& short_name = "") {
    return Expect(long_name, short_name, typeid(int).name());
  }

  template<class TType>
  inline TType GetArg(const std::string& name) {
    if (!arguments_.count(name)) {
      return TType();
    }
    return std::any_cast<TType>(arguments_.at(name));
  }

  inline bool GetBool(const std::string& name) {
    if (!expected_arguments_.count(name))
      return false;
    return GetArg<bool>(name);
  }

  inline std::string GetString(const std::string& name) {
    return GetArg<std::string>(name);
  }

  inline int GetInt(const std::string& name) {
    return GetArg<int>(name);
  }

 private:
  std::map<std::string, std::string> aliases_;
  std::map<std::string, std::string> expected_arguments_;
  std::map<std::string, std::any> arguments_;
};

inline Args& Args::Parse(const std::string& arg, const std::string& next_token) {
  if (!expected_arguments_.count(arg) && !aliases_.count(arg)) {
    std::cerr << "Unexpected argument: " << arg << std::endl;
    std::cerr << "--help for more information" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string unaliased_arg = aliases_.count(arg) ? aliases_.at(arg) : arg;
  if (!IsBool(unaliased_arg)) {
    std::cerr << "Currently I cannot parse anything but booleans :(" << std::endl;
    exit(EXIT_FAILURE);
  }
  arguments_.emplace(unaliased_arg, true);
  return static_cast<Args&>(*this);
}

}
