#include "Alien.hpp"
#include "Bullet.hpp"

#include "gtest/gtest.h"


TEST(alien_test, test_construction)
{
  Alien alien;
  EXPECT_EQ(alien.GetObject(), Box2D(0.0f, 0.0f, 1.0f, 1.0f));
  EXPECT_EQ(alien.GetDirection(), Ray2D(0.0f, 0.0f, 0.0f, 1.0f));
  EXPECT_EQ(alien.GetVelocity(), 1.0f);
  EXPECT_EQ(alien.GetHealth(), 100.0f);
  EXPECT_EQ(alien.GetIsEnabled(), true);

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
  alien.Move();

  EXPECT_EQ(alien.GetObject(), Box2D(0.0f, 1.0f, 1.0f, 2.0f));

  alien.Damage(110);
  alien.Move();
  EXPECT_EQ(alien.GetObject(), Box2D(0.0f, 1.0f, 1.0f, 2.0f));
  EXPECT_EQ(alien.GetIsEnabled(), false);
}

TEST(alien_test, test_output)
{
  std::stringstream s;
  s << Alien();
  EXPECT_EQ(s.str(), "Unit: Alien object: Box 2D {Left Bottom Point 2D {0, 0}, Right Top Point 2D {1, 1}}; Direction Ray 2D { Origin Point 2D {0, 0}, Direction Point 2D {0, 1}}; Velocity = 1; Health = 100; is enabled = 1");
}

TEST(alien_test, test_contact)
{
  Bullet bullet;
  Alien obj;

  Contact(bullet, obj, UnitType::Alien);
  EXPECT_EQ(obj.GetIsEnabled(), true);
  EXPECT_EQ(obj.GetHealth(), 99.0);
}