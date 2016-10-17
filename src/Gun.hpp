#pragma once

#include "IGameObject.hpp"
#include "Bullet.hpp"

class Gun : public IGameObject
{
public:
  Gun() = default;

  Gun(Box2D && object) noexcept : m_object(std::move(object)) {}

  Gun(Point2D const & centre) noexcept { m_object.Move(centre); }

  void SetObject(Box2D && object) noexcept { m_object = std::move(object); }

  void SetDirection(Ray2D && direction) noexcept { m_direction = std::move(direction); }

  void SetCage(float cage) noexcept { m_cage = cage; }

  Box2D const & GetObject() const noexcept override { return m_object; }

  Ray2D const & GetDirection() const { return m_direction; }

  int const & GetCage() const noexcept { return m_cage; }

  bool const & GetIsEnabled() const noexcept { return m_isEnabled; }

  float const & GetHealth() const noexcept { return m_health; }

  void Damage (float const & damage) noexcept override 
  {
    m_health -= damage; 
    if (m_health <= 0)
      m_isEnabled = false;
  }
  
  Bullet Shot() noexcept
  {
    if (m_cage > 0) 
    {
      m_cage--;
      Bullet bullet;
      bullet.SetDirection(Ray2D(m_direction));
      // all sets
      return bullet;
    }
    else 
    {
      m_isEnabled = false;
    }
  }

  void Draw() override { }

  void Move () override { }

  friend std::ostream & operator << (std::ostream & os, Gun const & obj)
  {
    os << "Unit: Gun object: " << obj.m_object << "; Direction " << obj.m_direction 
      << "; Cage = " << obj.m_cage << "; is enabled = " << obj.m_isEnabled;
    return os;
  }

protected: 
  Box2D m_object = { 0.0f, 0.0f, 1.0f, 1.0f };
  Ray2D m_direction = { 0.5f, 0.5f, 1.0f, 0.5f };
  int m_cage = 5;
  float m_health = 100.0f;
  bool m_isEnabled = true;
};