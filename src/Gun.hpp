#pragma once

#include "IGameObject.hpp"
#include "Bullet.hpp"

class Gun : public IGameObject
{
public:
  Gun() = default;
  Gun (Box2D && object) : m_object(std::move(object)) {}

  void SetObject(Box2D && object)  { m_object = std::move(object); }
  void SetDirection(Ray2D && direction) { m_direction = std::move(direction); }
  void SetCage(float cage) { m_cage = cage; }

  Box2D const & GetObject() const { return m_object; }
  Ray2D const & GetDirection() const { return m_direction; }
  int const & GetCage() const { return m_cage; }
  bool const & GetIsEnabled() const { return m_is_enabled; }

  Bullet Shot() 
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
      m_is_enabled = false;
  }

  void Draw() 
  {
    if (!m_is_enabled) 
    {
      // img inaccessible weapons
      return;
    }
    // img normal
  }

  void UpDate () override 
  {
    Draw();
  }

  friend std::ostream & operator << (std::ostream & os, Gun const & obj)
  {
    os << "Unit: Gun object: " << obj.m_object << "; Direction " << obj.m_direction 
      << "; Cage = " << obj.m_cage << "; is enabled = " << obj.m_is_enabled;
    return os;
  }


protected: // can make a choice weapon by inheritance
  // It's defines the position and dimensions of weapons
  Box2D m_object = { 0.0f, 0.0f, 1.0f, 1.0f };
  // which direction
  Ray2D m_direction = { 0.5f, 0.5f, 1.0f, 0.5f };
  int m_cage = 5;
  bool m_is_enabled = true;
};