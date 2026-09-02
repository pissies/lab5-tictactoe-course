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

// читает значение клетки (x, y), но если она совпадает с виртуальной
// клеткой virtual_cell, считает её занятой virtual_sign, а не тем, что
// реально лежит в state. has_virtual == false отключает подмену (используется
// обычным get_line_info, у которого виртуальной клетки нет).
Sign read_cell(const State &state, int x, int y, bool has_virtual,
               Point virtual_cell, Sign virtual_sign) {
  if (has_virtual && x == virtual_cell.x && y == virtual_cell.y) {
    return virtual_sign;
  }
  return state.get_value(x, y);
}

// общая логика подсчёта: клетка (x, y) считается гипотетически занятой sign,
// дальше идём в обе стороны направления dir, пока встречаем sign (с учётом
// возможной виртуальной клетки), останавливаемся на препятствии, краю поля
// или символе соперника.
LineInfo count_line(const State &state, int x, int y, Direction dir, Sign sign,
                     bool has_virtual, Point virtual_cell, Sign virtual_sign) {
  const Offset off = direction_offset(dir);

  int length = 1;

  int px = x + off.dx;
  int py = y + off.dy;
  while (read_cell(state, px, py, has_virtual, virtual_cell, virtual_sign) ==
         sign) {
    ++length;
    px += off.dx;
    py += off.dy;
  }

  int nx = x - off.dx;
  int ny = y - off.dy;
  while (read_cell(state, nx, ny, has_virtual, virtual_cell, virtual_sign) ==
         sign) {
    ++length;
    nx -= off.dx;
    ny -= off.dy;
  }

  // open_ends: TODO, потребуется для шага 6
  return LineInfo{length, 0};
}

} // namespace

LineInfo get_line_info(const State &state, int x, int y, Direction dir,
                        Sign sign) {
  // клетка (x, y) считается занятой символом sign гипотетически: реальное
  // значение в ней не читается (обычно она пустая, т.к. кандидат), поле не
  // изменяется - просто читаем реальные значения соседних клеток.
  return count_line(state, x, y, dir, sign, /*has_virtual=*/false, Point{0, 0},
                     Sign::NONE);
}

LineInfo get_line_info_virtual(const State &state, int x, int y, Direction dir,
                                Sign sign, Point virtual_cell) {
  // как get_line_info, но дополнительно считает virtual_cell занятой sign,
  // даже если на реальном поле она пустая. Нужно шагам 4-5: там уже одна
  // клетка (p) гипотетически занята, и мы проверяем угрозы для других клеток
  // c, не мутируя state (мутация через process_move потребовала бы соблюдения
  // очерёдности хода, а sign может быть чужим символом).
  return count_line(state, x, y, dir, sign, /*has_virtual=*/true, virtual_cell,
                     sign);
}

} // namespace ttt::my_player
