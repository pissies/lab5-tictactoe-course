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
  // TODO: реализовать
  (void)p;
  (void)sign;
  const int max_threats = state.get_opts().rows * state.get_opts().cols;
  return PointBuffer(max_threats);
}

bool find_fork_move(const State &state, const PointBuffer &candidates,
                     Sign sign, Point &out) {
  // TODO: реализовать
  (void)state;
  (void)candidates;
  (void)sign;
  (void)out;
  return false;
}

} // namespace ttt::my_player
