#pragma once 

#include <memory>
#include <list>

#include "Factory.hpp"

class Space
{
public:
  Space() = default;

  void CreateNewUnit(UnitType unittype, Point2D const & centre) 
  {
    m_units.push_back(std::make_pair(UnitsFactory::CreateUnitByType(unittype, centre), unittype));
  }

  void CheckUnits() 
  {
    for (auto i = std::begin(m_units); i != std::end(m_units); i++)
      if (!(*i).first->GetIsEnabled())
        m_units.erase(i);
  }

  void Draw() {}

  void UpDate() 
  {
    Draw();
    for (auto i : m_units) 
    {
      i.first->Move();
      i.first->Draw();
    }
    m_gun->Draw();
  }

  std::pair<std::shared_ptr<IGameObject>, UnitType>  const & operator [] (size_t index)  throw (std::out_of_range) 
  { 
    auto it = m_units.cbegin();
    while (index) {it++; index--; }
    return *(it);
  }

protected:
  std::list<std::pair<std::shared_ptr<IGameObject>, UnitType> > m_units;
  std::shared_ptr<Gun> m_gun;
};