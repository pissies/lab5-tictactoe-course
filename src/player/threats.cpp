#include "threats.hpp"

namespace ttt::my_player {

bool find_winning_move(const State &state, const PointBuffer &candidates,
                        Sign sign, Point &out) {
  // TODO: реализовать
  (void)state;
  (void)candidates;
  (void)sign;
  (void)out;
  return false;
}

PointBuffer find_threats_after_move(const State &state, Point p, Sign sign) {
  // TODO: реализовать
  (void)p;
  (void)sign;
  const int max_threats = state.get_opts().rows * state.get_opts().cols;
  return PointBuffer(max_threats);
}

bool find_fork_move(const State &state, const PointBuffer &candidates,
                     Sign sign, Point &out) {
  // TODO: реализовать
  (void)state;
  (void)candidates;
  (void)sign;
  (void)out;
  return false;
}

} // namespace ttt::my_player
