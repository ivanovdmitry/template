#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "Singleton.hpp"


class Logger : public Singleton <Logger>
{
public:
  static const std::string Debug;
  static const std::string Info;
  static const std::string Error;

  void log(std::string const & message, std::string const & logLevel)
  {
    PrintToFile(message, logLevel);
  }

  Logger & operator() (std::string const & logLevel)
  {
    m_logLevel = logLevel;
    return *this;
  }

  Logger & operator<<(std::string const & message) 
  {
    log(message, m_logLevel);
  }
  
protected:
  std::ofstream m_outputStream;
  static const char* const m_FileName;
  std::string m_logLevel;

  void PrintToFile(std::string const & message, std::string const & logLevel)
  { 
    m_outputStream.open(m_FileName, std::ios_base::app);
    m_outputStream << "[" << logLevel << "] : " << message << std::endl; 
    m_outputStream.close();
  }

  friend class Singleton<Logger>;
};

#define Log Singleton<Logger>::Instance()