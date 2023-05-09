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

#include <chrono>
#include <stack>
#include <iostream>
#include <optional>

#include "colors.h"

namespace sockets {

/**
 * @brief A utility class for managing time
 * 
 */
class Hourglass {
 public:
  static void Start();
  static Hourglass Stop();
  double Elapsed() const;

  friend std::ostream& operator <<(std::ostream& out, const Hourglass& hourglass);
 private:
  Hourglass() : start_(clock_t::now()) { }

  static std::stack<Hourglass>& GetTimers();

  static std::optional<std::stack<Hourglass>> timers_;

  using clock_t = std::chrono::high_resolution_clock;
  using milli_t = std::chrono::duration<double, std::milli>;

  std::chrono::time_point<clock_t> start_;
  std::chrono::time_point<clock_t> end_;
};

inline std::optional<std::stack<Hourglass>> Hourglass::timers_;

inline std::stack<Hourglass>& Hourglass::GetTimers() {
  if (!timers_.has_value())
    timers_ = std::stack<Hourglass>();
  return timers_.value();
}

inline void Hourglass::Start() {
  GetTimers().push(Hourglass());
}

inline Hourglass Hourglass::Stop() {
  Hourglass ending_timer = GetTimers().top();
  ending_timer.end_ = clock_t::now();
  GetTimers().pop();
  return ending_timer;
}

inline double Hourglass::Elapsed() const {
  return std::chrono::duration_cast<milli_t>(end_ - start_).count();
}

inline std::ostream& operator <<(std::ostream& out, const Hourglass& hourglass) {
  out << "Elapsed " << hourglass.Elapsed() << " ms";
  return out;
}

}
