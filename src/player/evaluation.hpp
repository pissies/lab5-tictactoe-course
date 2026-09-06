#pragma once

#include "core/game.hpp"

namespace ttt::my_player {

using game::Point;
using game::Sign;
using game::State;

// понижающий коэффициент для оценки вклада защиты относительно вклада атаки 
const double kDefenseWeight = 0.8;

// оценивает клетку кандидата p весовой функцией W(k, o) по всем 4
// направлениям, как для собственной атаки символом own_sign, так и для
// защиты от opp_sign
double evaluate_candidate(const State &state, Point p, Sign own_sign,
                           Sign opp_sign);

} // namespace ttt::my_player
