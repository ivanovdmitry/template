#include "Space.hpp"

#include "gtest/gtest.h"

#include <iostream>

TEST(space_test, test_creation)
{
  Space space;

  space.CreateNewUnit(UnitType::Alien, Point2D(2.0, 2.0));
  space.CreateNewUnit(UnitType::Obstacle, Point2D(2.0, 2.0));
  space.CreateNewUnit(UnitType::Bullet, Point2D(2.0, 2.0));

  auto alien = std::static_pointer_cast<Alien> (space[0].first);
  auto obstacle = std::static_pointer_cast<Obstacle> (space[1].first);
  auto bullet = std::static_pointer_cast<Bullet> (space[2].first);

  std::stringstream s1; 
  s1 << *alien;
  EXPECT_EQ(s1.str(), "Unit: Alien object: Box 2D {Left Bottom Point 2D {1.5, 1.5}, Right Top Point 2D {2.5, 2.5}}; Direction Ray 2D { Origin Point 2D {0, 0}, Direction Point 2D {1, 0}}; Velocity = 1; Health = 100; is enabled = 1");

  std::stringstream s2; 
  s2 << *obstacle;
  EXPECT_EQ(s2.str(), "Unit: Obstacle object: Box 2D {Left Bottom Point 2D {0, 0}, Right Top Point 2D {2, 2}}; is enabled = 1");
  
  std::stringstream s3; 
  s3 << *bullet;
  EXPECT_EQ(s3.str(), "Unit: Bullet object: Box 2D {Left Bottom Point 2D {0, 0}, Right Top Point 2D {2, 2}}; Direction Ray 2D { Origin Point 2D {0, 0}, Direction Point 2D {1, 0.5}}; Velocity = 1; Energy = 1; is enabled = 1");
}