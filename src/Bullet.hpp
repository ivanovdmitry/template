#pragma once

#include "IGameObject.hpp"

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
  bool const & GetIsEnabled() const {return m_is_enabled; }

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

protected:
  Box2D m_object = { 0.0f, 0.0f, 1.0f, 1.0f };
  Ray2D m_direction = { 0.0f, 0.0f, 1.0f, 0.5f };
  float m_velocity = 1.0;
  float m_energy = 1.0;
  bool m_is_enabled = true;
};