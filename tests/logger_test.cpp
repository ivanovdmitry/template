#include "Singleton.hpp"
#include "Logger.hpp"

#include "gtest/gtest.h"


TEST(logger_test, test_write2file)
{
  auto & logger = Singleton<Logger>::Instance();
  logger.log("this is the test", Logger::m_LogLevelDebug);
}
