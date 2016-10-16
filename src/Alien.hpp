#pragma once

#include "IGameObject.hpp"

class Alien : public IGameObject
{
public:
  Alien() = default;
  Alien(Point2D const & centre) 
  {
    m_object.Move(centre);
  }

  void Draw() {}

  void UpDate () override
  {
    if (m_is_enabled) 
    {
      m_object.Move(m_object.Centre() + m_direction.GetDirectionNormal() * m_velocity);
      Draw();
    }
  }

  void Damage (float const & health) 
  {
    m_health -= health; 
    if (m_health <= 0)
      m_is_enabled = false;
  }
 
  void SetObject(Box2D && object)  { m_object = std::move(object); }
  void SetDirection(Ray2D && direction) { m_direction = std::move(direction); }
  void SetVelocity(float velocity) { m_velocity = velocity; }
  void SetHealth(float health) { m_health = health; }

  Box2D const & GetObject() const { return m_object; }
  Ray2D const & GetDirection() const { return m_direction; }
  float const & GetVelocity() const { return m_velocity; }
  float const & GetHealth() const { return m_health; }
  bool const & GetIsEnabled() const override {return m_is_enabled; }

  friend std::ostream & operator << (std::ostream & os, Alien const & obj)
  {
    os << "Unit: Alien object: " << obj.m_object << "; Direction " << obj.m_direction 
      << "; Velocity = " << obj.m_velocity << "; Health = " << obj.m_health << "; is enabled = " << obj.m_is_enabled;
    return os;
  }

protected:
// It's defines the position and dimensions
  Box2D m_object = { 0.0f, 0.0f, 1.0f, 1.0f };
  // which direction
  Ray2D m_direction = { 0.0f, 0.0f, 1.0f, 0.0f };
  // flight speed
  float m_velocity = 1.0f;
  float m_health = 100.0f;
  bool m_is_enabled = true;
};