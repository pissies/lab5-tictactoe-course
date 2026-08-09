#pragma once

#include <vector>

#include "core/game.hpp"

namespace ttt::my_player {

using game::Point;
using game::Sign;
using game::State;

// ищет среди candidates клетку, ставящую символом sign линию
// длины >= win_len. Возвращает true и записывает найденную клетку в out,
// если такая клетка найдена.
// TODO: реализовать

bool find_winning_move(const State &state, const std::vector<Point> &candidates,
                        Sign sign, Point &out);

// для клетки p возвращает список всех пустых клеток поля, являющихся угрозами
// для символа sign, если бы в p был временно поставлен sign.
// TODO: реализовать

std::vector<Point> find_threats_after_move(const State &state, Point p,
                                            Sign sign);

// ищет среди candidates клетку, создающую двойную угрозу для
// символа sign (то есть find_threats_after_move возвращает >= 2 клеток).
// если найдено несколько таких кандидатов, выбирается тот, у которого больше
// всего клеток-угроз. Возвращает true и записывает найденную клетку в out,
// если такая клетка найдена.
// TODO: реализовать

bool find_fork_move(const State &state, const std::vector<Point> &candidates,
                     Sign sign, Point &out);

} // namespace ttt::my_player
