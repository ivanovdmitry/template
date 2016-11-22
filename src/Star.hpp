#pragma once

#include <QCoreApplication>

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
class Star
{
public:
  Star() { GeneratePositionAndSize(); }

  void GeneratePositionAndSize()
  {
    std::srand(unsigned(std::clock()));
    unsigned char size = std::rand() % 8;
    m_size = QSize(size, size);
    m_sizeTmp = size;
    
    m_position = QVector2D(std::rand() % 800, std::rand() % 600);
  }

  void Update()
  {
    unsigned char size = m_size.width();
    // then change the size
    if (size == 0)
      size = m_sizeTmp;
    else
      size = 0;

    m_size = QSize(size, size);
  }

  QVector2D const & GetPosition() const { return m_position; }

  QSize const & GetSize() const { return m_size; }
private:
  QVector2D m_position;
  QSize m_size;
  unsigned char m_sizeTmp;
};