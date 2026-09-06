#include "evaluation.hpp"
#include "line_utils.hpp"

namespace ttt::my_player {

namespace {

const Direction kAllDirections[] = {Direction::HORIZONTAL, Direction::VERTICAL,
                                     Direction::DIAG_MAIN, Direction::DIAG_ANTI};

// множитель за открытость линии: закрытая с обоих концов линия (o=0)
// никогда не станет победной, сколько бы символов в ней ни было, поэтому
// её вес — 0. Один открытый конец даёт возможность роста, два открытых —
// заметно больше (линию можно продолжать в обе стороны), поэтому множитель
// для o=2 сильно больше, чем для o=1.
const double kOpenEndsMultiplier[3] = {0.0, 1.0, 3.0};

// основание экспоненты, задающее рост веса с длиной линии k. При base > 2
// вес линии длины k с двумя открытыми концами гарантированно больше суммы
// весов двух линий длины k-1 с двумя открытыми концами (base^k > 2*base^(k-1)
// равносильно base > 2), то есть бот будет стремиться развивать одну длинную
// открытую линию, а не размазывать ходы по нескольким коротким.
//
// Конкретные значения kOpenEndsMultiplier и kBase подобраны экспериментально
// и могут быть скорректированы.
const double kBase = 5.0;

// W(k, o): вес линии длины k (от 1 до L-1) с o открытыми концами (0, 1, 2).
double line_weight(int length, int open_ends) {
  double value = 1.0;
  for (int i = 0; i < length; ++i) {
    value *= kBase;
  }
  return value * kOpenEndsMultiplier[open_ends];
}

} // namespace

double evaluate_candidate(const State &state, Point p, Sign own_sign,
                           Sign opp_sign) {
  double score = 0.0;

  // собственный потенциал атаки: сумма W(k_S, o_S) по всем 4 направлениям
  for (const Direction dir : kAllDirections) {
    const LineInfo own_info = get_line_info(state, p.x, p.y, dir, own_sign);
    score += line_weight(own_info.length, own_info.open_ends);
  }

  // ценность помешать сопернику: сумма W(k_T, o_T) по всем 4 направлениям,
  // с понижающим коэффициентом kDefenseWeight
  for (const Direction dir : kAllDirections) {
    const LineInfo opp_info = get_line_info(state, p.x, p.y, dir, opp_sign);
    score += kDefenseWeight * line_weight(opp_info.length, opp_info.open_ends);
  }

  return score;
}

} // namespace ttt::my_player
