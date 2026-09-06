#pragma once

#include "core/game.hpp"
#include "point_buffer.hpp"

namespace ttt::my_player {

using game::Point;
using game::Sign;
using game::State;

struct ScoredCandidate {
  game::Point point;
  double score;
};

class ScoredCandidateBuffer {
  ScoredCandidate *m_data;
  int m_count;
  int m_capacity;

public:
  explicit ScoredCandidateBuffer(int capacity)
      : m_data(capacity > 0 ? new ScoredCandidate[capacity] : nullptr),
        m_count(0), m_capacity(capacity) {}

  ScoredCandidateBuffer(const ScoredCandidateBuffer &other)
      : m_data(other.m_capacity > 0 ? new ScoredCandidate[other.m_capacity]
                                     : nullptr),
        m_count(other.m_count), m_capacity(other.m_capacity) {
    for (int i = 0; i < m_count; ++i) {
      m_data[i] = other.m_data[i];
    }
  }

  ScoredCandidateBuffer &operator=(const ScoredCandidateBuffer &other) {
    if (this == &other) {
      return *this;
    }
    delete[] m_data;
    m_capacity = other.m_capacity;
    m_count = other.m_count;
    m_data = m_capacity > 0 ? new ScoredCandidate[m_capacity] : nullptr;
    for (int i = 0; i < m_count; ++i) {
      m_data[i] = other.m_data[i];
    }
    return *this;
  }

  ~ScoredCandidateBuffer() { delete[] m_data; }

  void add(const ScoredCandidate &c) { m_data[m_count++] = c; }

  int size() const { return m_count; }
  int capacity() const { return m_capacity; }

  ScoredCandidate &operator[](int i) { return m_data[i]; }
  const ScoredCandidate &operator[](int i) const { return m_data[i]; }
};

// число лучших кандидатов, для которых выполняется предпросмотр ответа
// соперника
const int kLookaheadTopK = 10;

// для верхних top_candidates (по оценке из шага 6) проверяет, не
// даёт ли наш ход point сопернику немедленную победу или двойную угрозу на
// следующем ходу; если да, то оценка штрафуется.
// Возвращает скорректированный список кандидатов (той же ёмкости, что и
// top_candidates).
ScoredCandidateBuffer
apply_lookahead(const State &state,
                 const ScoredCandidateBuffer &top_candidates,
                 Sign own_sign, Sign opp_sign);

// шаг 8: находит клетку с максимальной итоговой оценкой среди candidates.
// Если таких клеток несколько, выбирает одну из них случайно, равновероятно.
// candidates не должен быть пустым (список кандидатов из шага 1 не пуст,
// пока на поле есть хотя бы одна свободная клетка).
Point select_best_move(const ScoredCandidateBuffer &candidates);

} // namespace ttt::my_player
