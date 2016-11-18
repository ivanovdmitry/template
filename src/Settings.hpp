#pragma once

#include <string>
#include "GameLevel.hpp"

class Settings
{
public:
  Settings() = default;
  Settings(std::string const & name, GameLevel const & level) : m_name(name), m_level(level) {}; 

  void SetName(std::string const & name) { m_name = name; }
  void SetLevel(GameLevel const & level) { m_level = level;}

  std::string const & GetName() const { return m_name; }
  GameLevel const & GetLevel() const { return m_level; } 
private:
  std::string m_name = "NONAME";
  GameLevel m_level = GameLevel::Easy;
};