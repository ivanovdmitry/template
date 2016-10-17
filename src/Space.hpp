#pragma once 

#include <memory>
#include <list>

#include "Factory.hpp"

class Space
{
public:
  Space() = default;

  Box2D const & GetObject() const { return m_object; }

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

  void Update() 
  {
    Draw();
    for (auto const & i : m_units) 
    {
      i.first->Move();
      i.first->Draw();
    }
    m_gun->Draw();
  }

  friend void Contact(Bullet & bullet, Space & obj, UnitType unitType) 
  {
    if (!Intsec(bullet.GetObject(), obj.GetObject())) 
    {
      bullet.SetIsEnabled(false);
    }
  }

  std::pair<std::shared_ptr<IGameObject>, UnitType>  const & operator [] (size_t index)  
  { 
    auto it = m_units.cbegin();
    while (index) {it++; index--; }
    return *(it);
  }

protected:
  Box2D m_object = { 0.0f, 0.0f, 1.0f, 1.0f };
  std::list<std::pair<std::shared_ptr<IGameObject>, UnitType> > m_units;
  std::shared_ptr<Gun> m_gun;
};