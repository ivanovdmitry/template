#pragma once

#include <string>
#include <fstream>

#include "GameLevel.hpp"
#include "json/json.h"

class Settings
{
public:
  Settings() = default;
  Settings(std::string const & name, GameLevel const & level) : m_name(name), m_level(level) {}; 

  void SetName(std::string const & name) { m_name = name; }
  void SetLevel(GameLevel const & level) { m_level = level;}

  void Save()
  {
    Json::Value settings;
    auto & root = settings["settings"];
    root["game"]["UserName"] = m_name;
    root["game"]["GameLevel"] = static_cast<unsigned char> (m_level);

    std::ofstream settingsFile("settings.json");
    if (settingsFile.is_open())
    {
      Json::StyledWriter styledWriter;
      settingsFile << styledWriter.write(settings);
      settingsFile.close();
    }
  }

  void Read()
  {
    Json::Value settings;
    std::ifstream file("settings.json");
    if (file.is_open())
    {
      file >> settings;
      file.close();
    }
    auto & game = settings["settings"]["game"];
    m_name = game["UserName"].asString();
    m_level = static_cast<GameLevel> (game["GameLevel"].asInt());
  }

  std::string const & GetName() const { return m_name; }
  GameLevel const & GetLevel() const { return m_level; } 
private:
  std::string m_name = "";
  GameLevel m_level = GameLevel::Easy;
};