#pragma once 

#include <memory>

#include "Alien.hpp"
#include "Bullet.hpp"
#include "Gun.hpp"
#include "Obstacle.hpp"

enum class UnitType {Alien, Bullet, Obstacle};

class Space
{
public:
  Space() = default;

  void CreateNewUnit(Point2D const & centre, UnitType unittype) throw (std::invalid_argument)
  {
    switch (unittype)
    {
      case UnitType::Alien: units.push_back(std::make_pair(CreateUnit<Alien>(centre), unittype)); 
        break;
      case UnitType::Bullet: units.push_back(std::make_pair(CreateUnit<Bullet>(centre), unittype)); 
        break;
      case UnitType::Obstacle: units.push_back(std::make_pair(CreateUnit<Obstacle>(centre), unittype)); 
        break;
      default:
        std::invalid_argument("oops, the real problem");
    }
  }

  void CheckUnits() 
  {
    for (auto i = std::begin(units); i != std::end(units); i++)
      if (!(*i).first->GetIsEnabled())
        units.erase(i);
  }

  void Draw() {}

  void UpDate() 
  {
    Draw();
    for (auto i : units)
      i.first->UpDate();
    gun->UpDate();
  }

  std::pair<std::shared_ptr<IGameObject>, UnitType>  const & operator [] (unsigned int index) const { return units.at(index); }


protected:
  std::vector<std::pair<std::shared_ptr<IGameObject>, UnitType> > units;
  std::shared_ptr<Gun> gun;
  
private:
  template<typename T>
  std::shared_ptr<IGameObject> CreateUnit(Point2D const & centre) const { return std::make_shared<T>(centre); }
};