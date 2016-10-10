#pragma once

#include "Box2D.hpp"
#include "Ray2D.hpp"

class IGameObject 
{
public:
  virtual ~IGameObject() = default;
  virtual void UpDate() = 0;
  virtual bool const & GetIsEnabled() const = 0;
};