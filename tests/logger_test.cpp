#include "Logger.hpp"
#include "Gun.hpp"
#include "Alien.hpp"
#include "Bullet.hpp"

#include "gtest/gtest.h"

TEST(logger_test, test_write2file_stream)
{
  Singleton<Logger>::Instance().log("this is the test", Logger::Debug);
}

TEST(logger_test, test_write2file_stream_short)
{
  Log.log("test_write2file_stream1", Logger::Debug);
}

TEST(logger_test, test_Debug)
{
  Log(Logger::Debug) << "test_Debug ";
}

TEST(logger_test, test_Info)
{
  Log(Logger::Info)  << "test_Info";
}

TEST(logger_test, test_Error)
{
  Log(Logger::Error) << "test_Error";
}

TEST(logger_test, test_Gun)
{
  Log(Logger::Debug) << Gun();
}

TEST(logger_test, test_Alien)
{
  Log(Logger::Debug) << Alien();
}

TEST(logger_test, test_Bullet)
{
  Log(Logger::Debug) << Bullet();
}

TEST(logger_test, test_Box2D)
{
  Log(Logger::Debug) << Box2D();
}

TEST(logger_test, test_Ray2D)
{
  Log(Logger::Debug) << Ray2D();
}

TEST(logger_test, test_Point2D)
{
  Log(Logger::Debug) << Point2D();
}