#include "lookahead.hpp"

namespace ttt::my_player {

std::vector<ScoredCandidate>
apply_lookahead(const game::State &state,
                 const std::vector<ScoredCandidate> &top_candidates,
                 game::Sign own_sign, game::Sign opp_sign) {
  // TODO: реализовать 
  (void)state;
  (void)own_sign;
  (void)opp_sign;
  return top_candidates;
}

} // namespace ttt::my_player
