#pragma once

#include "IGameObject.hpp"
#include "Bullet.hpp"

class Alien : public IGameObject
{
public:
  Alien() = default;

  Alien(Point2D const & centre) noexcept { m_object.Move(centre); }

  void Draw() override {}

  void Move() override
  {
    if (m_isEnabled)
      try
      {
        m_object.Move(m_object.Centre() + m_direction.GetDirectionNormal() * m_velocity);
      }
      catch (std::invalid_argument const & e)
      {
        // 2 log file
      }
  }

  void Damage(float const & damage) noexcept override
  {
    m_health -= damage;
    if (m_health <= 0)
      m_isEnabled = false;
  }

  void Shot() 
  {
    if (m_cage > 0)
    {
      m_cage--;
      Bullet bullet;
      bullet.SetOwner(Owner::Alien);
      bullet.SetPosition(m_object.Centre());
      bullet.SetDirection(m_direction);
      bullet.SetEnergy(m_energy);
    }
    throw ExceptionEmptyChamber();
  }

  void SetObject(Box2D && object) noexcept { m_object = std::move(object); }
  void SetObject(Box2D const & object) noexcept { m_object = object; }
  void SetDirection(Ray2D && direction) noexcept { m_direction = std::move(direction); }
  void SetDirection(Ray2D const & direction) noexcept { m_direction = direction; }
  void SetVelocity(float const & velocity) noexcept { m_velocity = velocity; }
  void SetHealth(float const & health) noexcept { m_health = health; }

  Box2D const & GetObject() const noexcept override { return m_object; }
  Ray2D const & GetDirection() const noexcept { return m_direction; }
  float const & GetVelocity() const noexcept { return m_velocity; }
  float const & GetHealth() const noexcept { return m_health; }
  bool const & GetIsEnabled() const noexcept override { return m_isEnabled; }

  friend std::ostream & operator <<(std::ostream & os, Alien const & obj)
  {
    os << "Unit: Alien object: " << obj.m_object << "; Direction " << obj.m_direction
       << "; Velocity = " << obj.m_velocity << "; Health = " << obj.m_health << "; is enabled = " << obj.m_isEnabled;
    return os;
  }

protected:
  Box2D m_object = {0.0f, 0.0f, 1.0f, 1.0f};
  Ray2D m_direction = {0.0f, 0.0f, 0.0f, 1.0f};
  int m_cage = 100;
  float m_energy = 1.0f;
  float m_velocity = 1.0f;
  float m_health = 100.0f;
  bool m_isEnabled = true;
};