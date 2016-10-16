#include "Obstacle.hpp"
#include "Bullet.hpp"

#include "gtest/gtest.h"


TEST(obstacle_test, test_construction)
{
  Obstacle obstacle1;
  EXPECT_EQ(obstacle1.GetObject(), Box2D(0.0f, 0.0f, 1.0f, 1.0f));

  Obstacle obstacle2(Box2D(1.0, 1.0, 2.0, 2.0)); // move
  EXPECT_EQ(obstacle2.GetObject(), Box2D(1.0, 1.0, 2.0, 2.0));

  Box2D const box(1.0, 1.0, 2.0, 2.0);
  Obstacle obstacle3(box); // copy
  EXPECT_EQ(obstacle3.GetObject(), Box2D(1.0, 1.0, 2.0, 2.0));
}

TEST(obstacle_test, test_enable)
{
  Obstacle obstacle;
  obstacle.SetIsEnabled(false);
  EXPECT_EQ(obstacle.GetIsEnabled(), false);
}

TEST(obstacle_test, test_output)
{
  std::stringstream s;
  s << Obstacle();
  EXPECT_EQ(s.str(), "Unit: Obstacle object: Box 2D {Left Bottom Point 2D {0, 0}, Right Top Point 2D {1, 1}}; is enabled = 1");
}

TEST(obstacle_test, test_contact)
{
  Bullet bullet;
  Obstacle obstacle;

  Contact(bullet, obstacle);
  EXPECT_EQ(obstacle.GetIsEnabled(), false);
}