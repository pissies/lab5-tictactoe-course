#include "lookahead.hpp"

namespace ttt::my_player {

ScoredCandidateBuffer
apply_lookahead(const game::State &state,
                 const ScoredCandidateBuffer &top_candidates,
                 game::Sign own_sign, game::Sign opp_sign) {
  // TODO: реализовать
  (void)state;
  (void)own_sign;
  (void)opp_sign;
  return top_candidates;
}

} // namespace ttt::my_player
