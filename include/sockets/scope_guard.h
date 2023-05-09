
#include <functional>

class ScopeGuard {
 public:
  ScopeGuard(const std::function<void()>& exit_fn) : exit_fn_(exit_fn) {}
  ~ScopeGuard() { exit_fn_(); }

 private:
  std::function<void()> exit_fn_;
};
