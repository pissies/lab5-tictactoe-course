#include "line_utils.hpp"

namespace ttt::my_player {

namespace {

// смещение (dx, dy), задающее положительную сторону направления dir
struct Offset {
  int dx;
  int dy;
};

Offset direction_offset(Direction dir) {
  switch (dir) {
  case Direction::HORIZONTAL:
    return Offset{1, 0};
  case Direction::VERTICAL:
    return Offset{0, 1};
  case Direction::DIAG_MAIN:
    return Offset{1, 1};
  case Direction::DIAG_ANTI:
    return Offset{1, -1};
  }
  return Offset{0, 0};
}

} // namespace

LineInfo get_line_info(const State &state, int x, int y, Direction dir,
                        Sign sign) {
  const Offset off = direction_offset(dir);

  // клетка (x, y) считается занятой символом sign гипотетически: реальное
  // значение в ней не читается (обычно она пустая, т.к. кандидат), поле не
  // изменяется — просто читаем реальные значения соседних клеток.
  int length = 1;

  // положительная сторона направления: идём, пока встречаем sign;
  // get_value за пределами поля возвращает Sign::WALL, поэтому цикл сам
  // останавливается на краю поля, как и на препятствии или символе соперника
  int px = x + off.dx;
  int py = y + off.dy;
  while (state.get_value(px, py) == sign) {
    ++length;
    px += off.dx;
    py += off.dy;
  }

  // отрицательная сторона направления
  int nx = x - off.dx;
  int ny = y - off.dy;
  while (state.get_value(nx, ny) == sign) {
    ++length;
    nx -= off.dx;
    ny -= off.dy;
  }

  // open_ends: TODO, потребуется для шага 6
  return LineInfo{length, 0};
}

} // namespace ttt::my_player
