#include "threats.hpp"

namespace ttt::my_player {

bool find_winning_move(const State &state, const std::vector<Point> &candidates,
                        Sign sign, Point &out) {
  // TODO: реализовать 
  (void)state;
  (void)candidates;
  (void)sign;
  (void)out;
  return false;
}

std::vector<Point> find_threats_after_move(const State &state, Point p,
                                            Sign sign) {
  // TODO: реализовать 
  (void)state;
  (void)p;
  (void)sign;
  return {};
}

bool find_fork_move(const State &state, const std::vector<Point> &candidates,
                     Sign sign, Point &out) {
  // TODO: реализовать 
  (void)state;
  (void)candidates;
  (void)sign;
  (void)out;
  return false;
}

} // namespace ttt::my_player
