#pragma once

#include "IGameObject.hpp"
#include "Bullet.hpp"

class Gun : public IGameObject
{
public:
  Gun() = default;

  Gun(Box2D const & object) noexcept  : m_object(object) {}
  Gun(Box2D && object) noexcept : m_object(std::move(object)) {}
  Gun(Point2D const & centre) noexcept { m_object.Move(centre); }

  void SetObject(Box2D && object) noexcept { m_object = std::move(object); }
  void SetObject(Box2D const & object) noexcept { m_object = object; }
  void SetDirection(Ray2D && direction) noexcept { m_direction = std::move(direction); }
  void SetDirection(Ray2D const & direction) noexcept { m_direction = direction; }
  void SetCage(float const & cage) noexcept { m_cage = cage; }
  void SetEnergy(float const & energy) noexcept { m_energy = energy; }
  void SetHealth(float const & health) noexcept { m_health = health; }

  Box2D const & GetObject() const noexcept override { return m_object; }
  Ray2D const & GetDirection() const { return m_direction; }
  int const & GetCage() const noexcept { return m_cage; }
  bool const & GetIsEnabled() const noexcept { return m_isEnabled; }
  float const & GetHealth() const noexcept { return m_health; }
  float const & GetEnergy() const noexcept { return m_energy; }

  void Damage(float const & damage) noexcept override
  {
    m_health -= damage;
    if (m_health <= 0)
      m_isEnabled = false;
  }

  using pair = std::pair<std::shared_ptr<IGameObject>, UnitType>;
  void Shot(std::list<pair> const & lst) noexcept
  {
    if (m_cage > 0)
    {
      m_cage--;
      Bullet bullet;
      bullet.SetOwner(m_owner);
      bullet.SetPosition(m_object.Centre());
      bullet.SetDirection(m_direction);
      bullet.SetEnergy(m_energy);
      lst.push_back(std::make_pair(std::make_shared<Bullet>(bullet), UnitType::Bullet));
    }
  }

  void Draw() override {}
  void Move() override {}

  friend std::ostream & operator <<(std::ostream & os, Gun const & obj)
  {
    os << "Unit: Gun object: " << obj.m_object << "; Direction " << obj.m_direction
       << "; Cage = " << obj.m_cage << "; is enabled = " << obj.m_isEnabled;
    return os;
  }

protected:
  Owner m_owner = Owner::Player;
  Box2D m_object = {0.0f, 0.0f, 1.0f, 1.0f};
  Ray2D m_direction = {0.5f, 0.5f, 1.0f, 0.5f};
  float m_energy = 1.0f;
  int m_cage = 5;
  float m_health = 100.0f;
  bool m_isEnabled = true;
};