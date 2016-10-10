#pragma once

#include "IGameObject.hpp"
#include "Box2D.hpp"
#include "Ray2D.hpp"

class Gun : public IGameObject
{
public:
  Gun() = default;
  Gun (Box2D && object) : m_object(std::move(object)) {}

  void SetObject(Box2D && object)  { m_object = std::move(object); }
  void SetDirection(Ray2D && direction) { m_direction = std::move(direction); }
  void SetVelocity(float velocity) { m_velocity = velocity; }
  void SetPower(float power) { m_power = power; }

  Box2D const & GetObject() const { return m_object; }
  Ray2D const & GetDirection() const { return m_direction; }
  float const & GetVelocity() { return m_velocity; }
  float const & GetPower() { return m_power; }

  void Draw() {}

  void UpDate () override 
  {
    Draw();
  }

protected: // can make a choice weapon by inheritance
  // It's defines the position and dimensions of weapons
  Box2D m_object = { 0.0f, 0.0f, 1.0f, 1.0f };
  // which direction
  Ray2D m_direction = { 0.5f, 0.5f, 1.0f, 0.5f };
  // flight speed
  float m_velocity = 1.0f;
  float m_power = 1.0f;
};