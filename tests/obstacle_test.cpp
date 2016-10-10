#include "Obstacle.hpp"

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