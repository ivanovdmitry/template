#include "Alien.hpp"

#include "gtest/gtest.h"


TEST(alien_test, test_construction)
{
  Alien alien;
  EXPECT_EQ(alien.GetObject(), Box2D(0.0f, 0.0f, 1.0f, 1.0f));
  EXPECT_EQ(alien.GetDirection(), Ray2D(0.0f, 0.0f, 1.0f, 0.0f));
  EXPECT_EQ(alien.GetVelocity(), 1.0);
  EXPECT_EQ(alien.GetHealth(), 100.0);
  EXPECT_EQ(alien.GetIsAlive(), true);

}

TEST(alien_test, test_sets)
{
  Alien alien;

  alien.SetObject(Box2D(3.0, 2.0, 5.0, 7.0));
  EXPECT_EQ(alien.GetObject(), Box2D(3.0, 2.0, 5.0, 7.0));

  alien.SetDirection(Ray2D(1.0, 2.0, 5.0, 5.0));
  EXPECT_EQ(alien.GetDirection(), Ray2D(1.0, 2.0, 5.0, 5.0));

  alien.SetVelocity(8.0);
  EXPECT_EQ(alien.GetVelocity(), 8.0);

  alien.SetHealth(80.0);
  EXPECT_EQ(alien.GetHealth(), 80.0);
}

TEST(alien_test, test_update)
{
  Alien alien;
  alien.UpDate();

  EXPECT_EQ(alien.GetObject(), Box2D(1.0f, 0.0f, 2.0f, 1.0f));

  alien.Damage(110);
  alien.UpDate();
  EXPECT_EQ(alien.GetObject(), Box2D(1.0f, 0.0f, 2.0f, 1.0f));
  EXPECT_EQ(alien.GetIsAlive(), false);
}

