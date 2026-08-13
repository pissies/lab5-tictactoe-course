#include "candidates.hpp"

namespace ttt::my_player {

namespace {

// ищет ближайшую к центру поля клетку без препятствия
PointBuffer find_first_move(const State &state) {
    const int cols = state.get_opts().cols;
    const int rows = state.get_opts().rows;
    const int cx = cols / 2;
    const int cy = rows / 2;

    int best_x = -1;
    int best_y = -1;
    int best_dist = -1;

    for (int y = 0; y < rows; ++y) {
      for (int x = 0; x < cols; ++x) {
        if (state.get_value(x, y) == Sign::WALL) {
          continue;
        }
        const int dx = x - cx;
        const int dy = y - cy;
        const int dist = dx * dx + dy * dy;
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

} 

//возвращает список кандидатов на ход
PointBuffer get_candidates(const State &state, const int radius) {
    const int cols = state.get_opts().cols;
    const int rows = state.get_opts().rows;
    const int cell_count = rows * cols;

    PointBuffer candidates(cell_count);

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
            // элементы двумерного массива получают уникальный индекс
            // в одномерном массиве
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

    // на поле нет ни одного X/O, зчначит это первый ход всей партии
    return find_first_move(state);
  }

} // namespace ttt::my_player
