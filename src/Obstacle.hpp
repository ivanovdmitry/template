#pragma once

#include "IGameObject.hpp"

class Obstacle : public IGameObject
{
public:
  Obstacle() = default;
  Obstacle(Box2D const & object) : m_object(object) {}
  Obstacle(Box2D && object) : m_object(std::move(object)) {}

  void SetObject(Box2D const & object)  { m_object = object; }
  void SetObject(Box2D && object)  { m_object = std::move(object); }
  void SetIsEnabled(bool v) {m_is_enabled = v;}
  void SetHealth(float const & health) { m_health = health; }

  bool const & GetIsEnabled() const override { return m_is_enabled; }
  Box2D const & GetObject() const { return m_object; }

  void Draw() {}
  void UpDate() override 
  {
    if (!m_is_enabled) return;
    Draw();
  }

  void Damage(float const & damage)
  {
    m_health -= damage;
    if (m_health <= 0)
      m_is_enabled = false;
  }

  friend std::ostream & operator << (std::ostream & os, Obstacle const & obj)
  {
    os << "Unit: Obstacle object: " << obj.m_object << "; is enabled = " << obj.m_is_enabled;
    return os;
  }


protected:
  Box2D m_object = { 0.0f, 0.0f, 1.0f, 1.0f };
  bool m_is_enabled = true;
  float m_health = 1.0f;
};