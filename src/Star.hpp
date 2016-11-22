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
    m_sizeTmp = QSize(size, size);
    m_size = size;
    nu = static_cast<float> (std::rand() % 2);
    fi = (static_cast<float> (std::rand() % 1000))/1000.0;
    
    m_position = QVector2D(std::rand() % 800, std::rand() % 600);
  }

  void Update(float elapsedSeconds)
  {
    unsigned char size = 0;

    static float const pi = std::acos(-1);
    static float time = 0.0; 

    time += elapsedSeconds;
    size = m_size*std::abs(std::sin(2.0*pi*nu*time*0.001 + fi));
   
    m_sizeTmp = QSize(size, size);
  }

  QVector2D const & GetPosition() const { return m_position; }

  QSize const & GetSize() const { return m_sizeTmp; }
private:
  QVector2D m_position;
  QSize m_sizeTmp;

  float nu; //Hz
  float fi; 
  unsigned char m_size;
};