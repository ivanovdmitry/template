#pragma once

#include <memory>

#include "Alien.hpp"
#include "Bullet.hpp"
#include "Gun.hpp"
#include "Obstacle.hpp"

#include "UnitType.hpp"

class UnitsFactory 
{
public:
  template<typename... Args>
  static std::shared_ptr<IGameObject> CreateUnitByType(UnitType unittype, Args &&... args) throw (std::invalid_argument)
  {
    switch (unittype)
    {
      case UnitType::Alien: return CreateOneUnit<Alien>(std::forward<Args>(args)...); 
      case UnitType::Bullet: return CreateOneUnit<Bullet>(std::forward<Args>(args)...); 
      case UnitType::Obstacle: return CreateOneUnit<Obstacle>(std::forward<Args>(args)...); 
      default:
        throw std::invalid_argument("oops, the real problem");
    }
  }
  template<typename T, typename... Args>
  static std::shared_ptr<IGameObject> CreateOneUnit(Args &&... args)  { return std::make_shared<T>(std::forward<Args>(args)...); }
};
