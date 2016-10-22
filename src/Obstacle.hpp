#pragma once

#include "IGameObject.hpp"

class Obstacle : public IGameObject
{
public:
  Obstacle() = default;
  Obstacle(Box2D const & object) noexcept : m_object(object) {}
  Obstacle(Box2D && object) noexcept : m_object(std::move(object)) {}
  Obstacle(Point2D const & centre) { m_object.Move(centre); }

  void SetObject(Box2D const & object) noexcept { m_object = object; }
  void SetObject(Box2D && object) noexcept { m_object = std::move(object); }
  void SetIsEnabled(bool const & isEnabled) noexcept { m_isEnabled = isEnabled; }
  void SetHealth(float const & health) noexcept { m_health = health; }

  bool const & GetIsEnabled() const noexcept override { return m_isEnabled; }
  Box2D const & GetObject() const noexcept override { return m_object; }
  float const & GetHealth() const noexcept { return m_health; }

  void Draw() override {}
  void Move() override { if (!m_isEnabled) return; }

  void Damage(float const & damage) noexcept override
  {
    m_health -= damage;
    if (m_health <= 0)
      m_isEnabled = false;
  }

  friend std::ostream & operator <<(std::ostream & os, Obstacle const & obj)
  {
    os << "Unit: Obstacle object: " << obj.m_object << "; is enabled = " << obj.m_isEnabled;
    return os;
  }

protected:
  Box2D m_object = {0.0f, 0.0f, 1.0f, 1.0f};
  bool m_isEnabled = true;
  float m_health = 1.0f;
};