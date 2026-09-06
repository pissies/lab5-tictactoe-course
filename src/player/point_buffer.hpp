#pragma once

#include "core/game.hpp"

namespace ttt::my_player {

using game::Point;

class PointBuffer {
  Point *m_data;
  int m_count;
  int m_capacity;

public:
  explicit PointBuffer(int capacity)
      : m_data(capacity > 0 ? new Point[capacity] : nullptr), m_count(0),
        m_capacity(capacity) {}

  PointBuffer(const PointBuffer &other)
      : m_data(other.m_capacity > 0 ? new Point[other.m_capacity] : nullptr),
        m_count(other.m_count), m_capacity(other.m_capacity) {
    for (int i = 0; i < m_count; ++i) {
      m_data[i] = other.m_data[i];
    }
  }

  PointBuffer &operator=(const PointBuffer &other) {
    if (this == &other) {
      return *this;
    }
    delete[] m_data;
    m_capacity = other.m_capacity;
    m_count = other.m_count;
    m_data = m_capacity > 0 ? new Point[m_capacity] : nullptr;
    for (int i = 0; i < m_count; ++i) {
      m_data[i] = other.m_data[i];
    }
    return *this;
  }

  ~PointBuffer() { delete[] m_data; }

  void add(const Point &p) { m_data[m_count++] = p; }

  int size() const { return m_count; }
  int capacity() const { return m_capacity; }

  Point &operator[](int i) { return m_data[i]; }
  const Point &operator[](int i) const { return m_data[i]; }
};

} // namespace ttt::my_player
