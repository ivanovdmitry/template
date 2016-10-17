#pragma once

#include "IGameObject.hpp"

#include "UnitType.hpp"

enum class Owner {GameUnit, Player};

class Bullet : public IGameObject
{
public:
  Bullet() = default;

  Bullet(Box2D && object) : m_object(std::move(object)) {}

  Bullet(Ray2D && direction) : m_direction(std::move(direction)) {}

  Bullet(Box2D && object, Ray2D &&direction) : m_object(std::move(object)), m_direction(std::move(direction)) {}
  
  Bullet(Point2D const & centre) { m_object.Move(centre); }

  void SetObject(Box2D && object)  { m_object = std::move(object); }

  void SetDirection(Ray2D && direction) { m_direction = std::move(direction); }

  void SetVelocity(float const & velocity) { m_velocity = velocity; }

  void SetEnergy(float const & energy) { m_energy = energy; }

  void SetIsEnabled(bool const & is_enabled) {m_isEnabled = is_enabled; }

  Box2D const & GetObject() const override { return m_object; }

  Ray2D const & GetDirection() const { return m_direction; }

  float const & GetVelocity() const { return m_velocity; }

  float const & GetEnergy() const { return m_energy; }

  bool const & GetIsEnabled() const override {return m_isEnabled; }

  void Damage (float const & damage) override  {}

  void Move() override
  {
    if (!m_isEnabled) return;
    m_object.Move(m_object.Centre() + m_direction.GetDirectionNormal() * m_velocity);
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
  Box2D m_object = { 0.0f, 0.0f, 1.0f, 1.0f };
  Ray2D m_direction = { 0.0f, 0.0f, 1.0f, 0.5f };
  float m_velocity = 1.0;
  float m_energy = 1.0;
  bool m_isEnabled = true;
};