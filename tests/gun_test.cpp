#include "Gun.hpp"

#include "gtest/gtest.h"


TEST(gun_test, test_construction)
{
  Gun gun;
  EXPECT_EQ(gun.GetObject(), Box2D(0.0f, 0.0f, 1.0f, 1.0f));
  EXPECT_EQ(gun.GetDirection(), Ray2D(0.5f, 0.5f, 1.0f, 0.5f));
  EXPECT_EQ(gun.GetCage(), 5);
  EXPECT_EQ(gun.GetIsEnabled(), true);
}

TEST(gun_test, test_shot)
{
  Gun gun;
  EXPECT_EQ(gun.GetCage(), 5);
  EXPECT_EQ(gun.GetIsEnabled(), true);
 /* Bullet bullet(gun.Shot());
  EXPECT_EQ(bullet.GetDirection(), Ray2D(0.5f, 0.5f, 1.0f, 0.5f));
  EXPECT_EQ(gun.GetCage(), 4);
  EXPECT_EQ(gun.GetIsEnabled(), true);*/
}


TEST(gun_test, test_update)
{
  Gun gun;

  for (auto i = 5; i > 0; i--)
  {
    gun.Shot();
    EXPECT_EQ(gun.GetCage(), i-1);
    EXPECT_EQ(gun.GetIsEnabled(), true); 
  }
  EXPECT_THROW(gun.Shot(), ExceptionEmptyChamber);
  EXPECT_EQ(gun.GetCage(), 0);
  EXPECT_EQ(gun.GetIsEnabled(), false);
}

TEST(gun_test, test_output)
{
  std::stringstream s;
  s << Gun();
  EXPECT_EQ(s.str(), "Unit: Gun object: Box 2D {Left Bottom Point 2D {0, 0}, Right Top Point 2D {1, 1}}; Direction Ray 2D { Origin Point 2D {0.5, 0.5}, Direction Point 2D {1, 0.5}}; Cage = 5; is enabled = 1");
}

TEST(gun_test, test_contact)
{
  Bullet bullet;
  Gun obj;

  Contact(bullet, obj, UnitType::Alien);
  EXPECT_EQ(obj.GetIsEnabled(), true);
  EXPECT_EQ(obj.GetHealth(), 99.0);
}