#pragma once

#include "IGameObject.hpp"

#include "UnitType.hpp"

enum class Owner {Alien, Player};

class Bullet : public IGameObject
{
public:
  Bullet() = default;

  Bullet(Box2D && object) noexcept : m_object(std::move(object)) {}

  Bullet(Ray2D && direction) noexcept : m_direction(std::move(direction)) {}

  Bullet(Box2D && object, Ray2D && direction) noexcept : m_object(std::move(object)), m_direction(std::move(direction)) {}
  
  Bullet(Point2D const & centre) noexcept { m_object.Move(centre); }

  void SetOwner(Owner const & owner) noexcept { m_owner = owner; }

  void SetPosition(Point2D const & position) noexcept { m_object.Move(position); }

  void SetDirection(Ray2D const & direction) noexcept { m_direction = direction; }

  void SetVelocity(float const & velocity) noexcept { m_velocity = velocity; }

  void SetEnergy(float const & energy) noexcept { m_energy = energy; }

  void SetIsEnabled(bool const & is_enabled) noexcept {m_isEnabled = is_enabled; }

  Owner const & GetOwner() const noexcept { return m_owner; }

  Box2D const & GetObject() const noexcept override { return m_object; }

  Ray2D const & GetDirection() const noexcept { return m_direction; }

  float const & GetVelocity() const noexcept { return m_velocity; }

  float const & GetEnergy() const noexcept { return m_energy; }

  bool const & GetIsEnabled() const noexcept override {return m_isEnabled; }

  void Damage (float const & damage) override  {}

  void Move() override 
  {
    if (!m_isEnabled) return;
    try 
    {
      m_object.Move(m_object.Centre() + m_direction.GetDirectionNormal() * m_velocity);
    } 
    catch (std::invalid_argument const & e)
    {
      // write  logfile
    }
  }

  void Draw() override {}

  friend void Contact(Bullet & bullet, IGameObject & obj, UnitType unitType) 
  {
    if (Intsec(bullet.GetObject(), obj.GetObject())) 
    {
      if ((unitType == UnitType::Alien) && (bullet.m_owner == Owner::Player) ||
          (unitType == UnitType::Gun) && (bullet.m_owner != Owner::Player) ||
          (unitType == UnitType::Obstacle))
        obj.Damage(bullet.m_energy);
      bullet.m_isEnabled = false;
    }
  }

  friend void Contact(Bullet & bullet, Bullet & obj, UnitType unitType) 
  {
    if (Intsec(bullet.GetObject(), obj.GetObject())) 
    {
      obj.m_isEnabled = false;
      bullet.m_isEnabled = false;
    }
  }

  friend void Contact(IGameObject & obj, Bullet & bullet,  UnitType unitType) 
  {
    Contact(bullet, obj, unitType);
  }

  friend std::ostream & operator << (std::ostream & os, Bullet const & obj)
  {
    os << "Unit: Bullet object: " << obj.m_object << "; Direction " << obj.m_direction 
      << "; Velocity = " << obj.m_velocity << "; Energy = " << obj.m_energy << "; is enabled = " << obj.m_isEnabled;
    return os;
  }
  
protected:
  Owner m_owner = Owner::Player;
  Box2D m_object = { 0.0f, 0.0f, 0.1f, 0.1f };
  Ray2D m_direction = { 0.0f, 0.0f, 1.0f, 0.5f };
  float m_velocity = 1.0;
  float m_energy = 1.0;
  bool m_isEnabled = true;
};