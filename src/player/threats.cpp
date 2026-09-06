#include "threats.hpp"
#include "line_utils.hpp"

namespace ttt::my_player {

namespace {

const Direction kAllDirections[] = {Direction::HORIZONTAL, Direction::VERTICAL,
                                     Direction::DIAG_MAIN, Direction::DIAG_ANTI};

} // namespace

// Реализует шаг 2 алгоритма (поиск немедленной победы) для символа sign.
// Та же функция используется и для шага 3 (блокировка): вызывающий код
// передаёт sign = символ соперника T, чтобы найти клетку, которая дала бы
// сопернику победу, а затем сам решает поставить туда свой символ S.
bool find_winning_move(const State &state, const PointBuffer &candidates,
                        Sign sign, Point &out) {
  const int win_len = state.get_opts().win_len;

  for (int i = 0; i < candidates.size(); ++i) {
    const Point &p = candidates[i];
    for (const Direction dir : kAllDirections) {
      const LineInfo info = get_line_info(state, p.x, p.y, dir, sign);
      if (info.length >= win_len) {
        out = p;
        return true;
      }
    }
  }
  return false;
}

PointBuffer find_threats_after_move(const State &state, Point p, Sign sign) {
  const int rows = state.get_opts().rows;
  const int cols = state.get_opts().cols;
  const int win_len = state.get_opts().win_len;
  const int max_threats = rows * cols;

  PointBuffer threats(max_threats);

  for (int y = 0; y < rows; ++y) {
    for (int x = 0; x < cols; ++x) {
      // p в результирующей позиции больше не пустая клетка, угрозой быть
      // не может
      if (x == p.x && y == p.y) {
        continue;
      }
      if (state.get_value(x, y) != Sign::NONE) {
        continue;
      }

      bool is_threat = false;
      for (const Direction dir : kAllDirections) {
        // (x, y) — гипотетическая клетка-угроза (sign), p — уже занятая
        // sign клетка с предыдущего гипотетического хода
        const LineInfo info =
            get_line_info_virtual(state, x, y, dir, sign, p);
        if (info.length >= win_len) {
          is_threat = true;
          break;
        }
      }
      if (is_threat) {
        threats.add(Point{x, y});
      }
    }
  }

  return threats;
}

// Реализует шаг 4 алгоритма (поиск двойной угрозы) для символа sign.
// Та же функция используется и для шага 5.1 (защита): вызывающий код
// передаёт sign = символ соперника T, чтобы найти клетку, которая дала бы
// сопернику двойную угрозу, а затем сам решает, как её заблокировать —
// симметрично find_winning_move для шагов 2-3.
bool find_fork_move(const State &state, const PointBuffer &candidates,
                     Sign sign, Point &out) {
  int best_count = 0;
  Point best_point{0, 0};
  bool found = false;

  for (int i = 0; i < candidates.size(); ++i) {
    const Point &p = candidates[i];
    const PointBuffer threats = find_threats_after_move(state, p, sign);
    if (threats.size() >= 2 && threats.size() > best_count) {
      best_count = threats.size();
      best_point = p;
      found = true;
    }
  }

  if (found) {
    out = best_point;
  }
  return found;
}

} // namespace ttt::my_player
