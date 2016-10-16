#pragma once

#include "Box2D.hpp"
#include "Ray2D.hpp"

class IGameObject 
{
public:
  virtual ~IGameObject() = default;
  virtual void Draw() = 0;
  virtual void Move() = 0;
  virtual bool const & GetIsEnabled() const = 0;
  virtual Box2D const & GetObject() const = 0;
  virtual void Damage (float const & ) = 0;
};