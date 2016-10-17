#pragma once 

#include <memory>
#include <list>
#include <algorithm>
#include <iterator> 

#include "Factory.hpp"

class Space
{
public:
  Space() = default;

  Box2D const & GetObject() const noexcept { return m_object; }

  size_t const  GetGameObjectsCount() const noexcept { return m_units.size(); }

  void CreateNewUnit(UnitType unittype, Point2D const & centre) 
  {
    m_units.push_back(std::make_pair(UnitsFactory::CreateUnitByType(unittype, centre), unittype));
  }

  void CheckCollision()
  {
    for (auto i = std::begin(m_units); i != std::end(m_units); i++)
    {
      if (i->second == UnitType::Bullet)
      {
        for (auto k = std::begin(m_units); k != std::end(m_units); k++)
        {
          if (i != k) 
          {
            Contact(static_cast<Bullet &>(*((*i).first.get())), *((*k).first.get()), (*k).second);
          }
        }
        Contact(static_cast<Bullet &>(*((*i).first.get())), *this,  UnitType::Space);
      }
    }
  }

  void CheckValidUnits() 
  {
    for (auto it = std::begin(m_units); it != std::end(m_units); it++)
      if (!it->first->GetIsEnabled()) 
        it = m_units.erase(it);
  }

  void Draw() {}

  void Update() 
  {
    CheckCollision();
    CheckValidUnits();

    Draw();
    for (auto const & i : m_units) 
    {
      i.first->Draw();
      i.first->Move();
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

  std::pair<std::shared_ptr<IGameObject>, UnitType>  const & operator [] (size_t const index)  
  { 
    auto it = std::begin(m_units);
    std::advance(it, index);
    return *(it);
  }

protected:
  Box2D m_object = { 0.0f, 0.0f, 10.0f, 10.0f };
  std::list<std::pair<std::shared_ptr<IGameObject>, UnitType>> m_units;
  std::shared_ptr<IGameObject> m_gun = std::make_shared<Gun>();
};