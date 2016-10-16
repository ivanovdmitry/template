#pragma once

#include "IGameObject.hpp"
#include "Obstacle.hpp"
#include "Alien.hpp"

enum class Owner {GameUnit, Player};

class Bullet : public IGameObject
{
public:
  Bullet() = default;
  Bullet(Box2D && object) : m_object(std::move(object)) {}
  Bullet(Ray2D && direction) : m_direction(std::move(direction)) {}
  Bullet(Box2D && object, Ray2D &&direction) : m_object(std::move(object)), m_direction(std::move(direction)) {}

  void SetObject(Box2D && object)  { m_object = std::move(object); }
  void SetDirection(Ray2D && direction) { m_direction = std::move(direction); }
  void SetVelocity(float const & velocity) { m_velocity = velocity; }
  void SetEnergy(float const & energy) { m_energy = energy; }

  Box2D const & GetObject() const { return m_object; }
  Ray2D const & GetDirection() const { return m_direction; }
  float const & GetVelocity() const { return m_velocity; }
  float const & GetEnergy() const { return m_energy; }
  bool const & GetIsEnabled() const override {return m_is_enabled; }

// TODO: intersection
  void Move()
  {
    m_object.Move(m_object.Centre() + m_direction.GetDirectionNormal() * m_velocity);
  }

  void Draw() {}

  void UpDate() override 
  {
    if (!m_is_enabled) return;
    Move();
    Draw();
  } 

  /*Решить проблему говнокода шаблонами*/
  template <typename T>
  friend void Contact(Bullet & bullet, T & obj) 
  {
    if (Intsec(bullet.GetObject(), obj.GetObject())) 
    {
      bullet.m_is_enabled = false;
      obj.Damage(bullet.m_energy);
    }
  }

  template <typename T>
  friend void Contact(T & obj, Bullet & bullet) 
  {
    Contact(bullet, obj);
  }

  friend void Contact(Bullet & bullet, Alien & obj) 
  {
    if (Intsec(bullet.GetObject(), obj.GetObject()) && (Owner::Player == bullet.m_owner)) 
    {
      bullet.m_is_enabled = false;
      obj.Damage(bullet.m_energy);
    }
  }

  friend std::ostream & operator << (std::ostream & os, Bullet const & obj)
  {
    os << "Unit: Bullet object: " << obj.m_object << "; Direction " << obj.m_direction 
      << "; Velocity = " << obj.m_velocity << "; Energy = " << obj.m_energy << "; is enabled = " << obj.m_is_enabled;
    return os;
  }
protected:
  Owner m_owner = Owner::Player;
  Box2D m_object = { 0.0f, 0.0f, 1.0f, 1.0f };
  Ray2D m_direction = { 0.0f, 0.0f, 1.0f, 0.5f };
  float m_velocity = 1.0;
  float m_energy = 1.0;
  bool m_is_enabled = true;
};