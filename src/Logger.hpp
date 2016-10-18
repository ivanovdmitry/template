#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "Singleton.hpp"



class Logger 
{
public:

  void log(const std::string& message, const std::string& logLevel)
  {
    m_outputStream.open(m_FileName, std::ios_base::app);
    print(message, logLevel);
    m_outputStream.close();
  }

  static const std::string m_LogLevelDebug;
  static const std::string m_LogLevelInfo;
  static const std::string m_LogLevelError;
  
protected:
  std::ofstream m_outputStream;
  static const char* const m_FileName;
  void print(const std::string& message, const std::string& logLevel)
  { 
    m_outputStream << "[" << logLevel << "] : " << message << std::endl; 
  }
};
