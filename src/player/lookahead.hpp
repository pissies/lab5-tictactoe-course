#pragma once

#include <vector>

#include "core/game.hpp"

namespace ttt::my_player {

// число лучших кандидатов, для которых выполняется предпросмотр ответа
// соперника 
const int kLookaheadTopK = 10;

struct ScoredCandidate {
  game::Point point;
  double score;
};

// для верхних top_candidates (по оценке из шага 6) проверяет, не
// даёт ли наш ход point сопернику немедленную победу или двойную угрозу на
// следующем ходу; если да, то  оценка штрафуется.
// Возвращает скорректированный список кандидатов.
//
// TODO: реализовать.
std::vector<ScoredCandidate>
apply_lookahead(const game::State &state,
                 const std::vector<ScoredCandidate> &top_candidates,
                 game::Sign own_sign, game::Sign opp_sign);

} // namespace ttt::my_player
