#pragma once

#include "core/game.hpp"

namespace ttt::my_player {

using game::Point;
using game::Sign;
using game::State;

// одно из четырёх направлений, вдоль которых считаются линии 
enum class Direction { HORIZONTAL, VERTICAL, DIAG_MAIN, DIAG_ANTI };

// информация о линии символа sign, проходящей через клетку (x, y), если бы
// в неё был поставлен этот символ  
struct LineInfo {
  int length;    // длина линии, включая саму клетку 
  int open_ends; // число открытых концов линии
};

// вычисляет длину и число открытых концов линии символа sign через клетку
// в направлении dir, при условии, что в эту клетку временно
// поставлен символ sign. используется в шагах 2, 3, 6 алгоритма.
//
// TODO: базовая версия (только длина) для шагов 2-3.
// TODO: расширение для расчёта open_ends, для шага 6.
LineInfo get_line_info(const State &state, int x, int y, Direction dir,
                        Sign sign);

} // namespace ttt::my_player
