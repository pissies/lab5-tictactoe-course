#pragma once

#include "core/game.hpp"
#include "point_buffer.hpp"

namespace ttt::my_player {

using game::Point;
using game::State;
using game::Sign;

// радиус поиска кандидатов (шаг 1 в algorithm.md)
const int kCandidateRadius = 2;

// функция возвращает список пустых клеток кандидатов на ход в квадрате
// (2*kCandidateRadius+1) * (2*kCandidateRadius+1) вокруг каждой занятой клетки
// в списке только уникальные значения клеток. Если список получился пустым ->
// -> в игре идет первый ход: выбрать единственного кандидата, ближайшую
// к центру незанятую (нет препятствий) клетку.

PointBuffer get_candidates(const State &state,
                            const int radius = kCandidateRadius);

} // namespace ttt::my_player
