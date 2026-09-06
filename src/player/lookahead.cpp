#include "lookahead.hpp"
#include "candidates.hpp"
#include "threats.hpp"

#include <cstdlib>

namespace ttt::my_player {

namespace {

// величина, которой штрафуется кандидат, подставляющий соперника под
// немедленную победу или двойную угрозу на следующем ходу. Заведомо меньше
// любой реальной оценки шага 6 (та всегда неотрицательна по построению
// weight-функции), поэтому такой кандидат никогда не будет выбран шагом 8,
// пока есть хоть один безопасный вариант.
const double kPenaltyScore = -1e9;

} // namespace

ScoredCandidateBuffer
apply_lookahead(const State &state,
                 const ScoredCandidateBuffer &top_candidates,
                 Sign own_sign, Sign opp_sign) {
  ScoredCandidateBuffer result(top_candidates.capacity());

  for (int i = 0; i < top_candidates.size(); ++i) {
    const ScoredCandidate &candidate = top_candidates[i];

    // временно ставим свой символ в клетку-кандидат — на КОПИИ состояния,
    // исходный state не трогаем. Это законный ход с точки зрения
    // process_move (проверка очерёдности пройдёт), так как apply_lookahead
    // вызывается для собственного следующего хода игрока own_sign, то есть
    // own_sign и есть текущий игрок state.
    State next_state(state);
    next_state.process_move(own_sign, candidate.point.x, candidate.point.y);

    // шаги 2 и 4 с точки зрения соперника в получившейся позиции
    const PointBuffer opp_candidates = get_candidates(next_state);

    Point unused{0, 0};
    const bool gives_opponent_win =
        find_winning_move(next_state, opp_candidates, opp_sign, unused);
    const bool gives_opponent_fork =
        !gives_opponent_win &&
        find_fork_move(next_state, opp_candidates, opp_sign, unused);

    ScoredCandidate adjusted = candidate;
    if (gives_opponent_win || gives_opponent_fork) {
      adjusted.score = kPenaltyScore;
    }
    result.add(adjusted);
  }

  return result;
}

Point select_best_move(const ScoredCandidateBuffer &candidates) {
  // максимальная итоговая оценка среди всех кандидатов
  double best_score = candidates[0].score;
  for (int i = 1; i < candidates.size(); ++i) {
    if (candidates[i].score > best_score) {
      best_score = candidates[i].score;
    }
  }

  // все клетки с максимальной оценкой (может быть несколько при равенстве)
  PointBuffer best_points(candidates.size());
  for (int i = 0; i < candidates.size(); ++i) {
    if (candidates[i].score == best_score) {
      best_points.add(candidates[i].point);
    }
  }

  // если клетка с максимальной оценкой одна - вернётся именно она;
  // если несколько - выбираем случайно, равновероятно
  const int idx = std::rand() % best_points.size();
  return best_points[idx];
}

} // namespace ttt::my_player
