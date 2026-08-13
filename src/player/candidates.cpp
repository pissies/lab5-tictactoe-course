#include "candidates.hpp"

namespace ttt::my_player {

PointBuffer get_candidates(const State &state, const int radius) {
  // TODO: реализовать.
  (void)radius;
  const int max_candidates = state.get_opts().rows * state.get_opts().cols;
  return PointBuffer(max_candidates);
}

} // namespace ttt::my_player
