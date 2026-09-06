#include "candidates.hpp"

namespace ttt::my_player {

namespace {

// Ищет ближайшую к центру поля клетку без препятствия, используется для
// самого первого хода партии, когда на поле ещё нет ни одного X/O 
// центр может быть занят препятствием, поэтому
// нужен fallback, а не жёстко зашитая центральная клетка

PointBuffer find_first_move(const State &state) {
  const int cols = state.get_opts().cols;
  const int rows = state.get_opts().rows;
  const int cx = cols / 2;
  const int cy = rows / 2;

  int best_x = -1;
  int best_y = -1;
  long long best_dist = -1;

  for (int y = 0; y < rows; ++y) {
    for (int x = 0; x < cols; ++x) {
      if (state.get_value(x, y) == Sign::WALL) {
        continue;
      }
      const long long dx = x - cx;
      const long long dy = y - cy;
      const long long dist = dx * dx + dy * dy;
      if (best_dist < 0 || dist < best_dist) {
        best_dist = dist;
        best_x = x;
        best_y = y;
      }
    }
  }

  PointBuffer result(1);
  if (best_x != -1) {
    result.add(Point{best_x, best_y});
  }
  return result;
}

} // namespace

PointBuffer get_candidates(const State &state, const int radius) {
  const int cols = state.get_opts().cols;
  const int rows = state.get_opts().rows;
  const int cell_count = rows * cols;

  PointBuffer candidates(cell_count);

  // Отмечаем уже добавленные клетки, чтобы не продублировать кандидата,
  // если он попадает в радиус сразу нескольких занятых клеток. 
  // размер известен заранее (cell_count)
  bool *added = new bool[cell_count];
  for (int i = 0; i < cell_count; ++i) {
    added[i] = false;
  }

  bool board_has_moves = false;

  for (int y = 0; y < rows; ++y) {
    for (int x = 0; x < cols; ++x) {
      const Sign occupant = state.get_value(x, y);
      if (occupant != Sign::X && occupant != Sign::O) {
        continue;
      }
      board_has_moves = true;

      for (int dy = -radius; dy <= radius; ++dy) {
        for (int dx = -radius; dx <= radius; ++dx) {
          if (dx == 0 && dy == 0) {
            continue;
          }
          const int nx = x + dx;
          const int ny = y + dy;
          if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) {
            continue;
          }
          if (state.get_value(nx, ny) != Sign::NONE) {
            continue;
          }
          const int idx = ny * cols + nx;
          if (added[idx]) {
            continue;
          }
          added[idx] = true;
          candidates.add(Point{nx, ny});
        }
      }
    }
  }

  delete[] added;

  if (board_has_moves) {
    return candidates;
  }

  // На поле нет ни одного X/O — это первый ход всей партии.
  return find_first_move(state);
}

} // namespace ttt::my_player
