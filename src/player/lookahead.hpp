#pragma once

#include "core/game.hpp"

namespace ttt::my_player {

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
//
// TODO: реализовать.
ScoredCandidateBuffer
apply_lookahead(const game::State &state,
                 const ScoredCandidateBuffer &top_candidates,
                 game::Sign own_sign, game::Sign opp_sign);

} // namespace ttt::my_player
