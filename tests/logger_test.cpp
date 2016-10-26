#include "Singleton.hpp"
#include "Logger.hpp"

#include "gtest/gtest.h"


TEST(logger_test, test_write2file)
{
  Singleton<Logger>::Instance().log("this is the test", Logger::Debug);
}


TEST(logger_test, test_write2file_stream)
{
  Log.log("test_write2file_stream1", Logger::Debug);
}

TEST(logger_test, test_write2file_stream2)
{
  Log(Logger::Debug) << "test_write2file Debug";
  Log(Logger::Info)  << "test_write2file Info";
  Log(Logger::Error) << "test_write2file Error";
}