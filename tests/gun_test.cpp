#include "Gun.hpp"

#include "gtest/gtest.h"


TEST(gun_test, test_construction)
{
  Gun gun;
  EXPECT_EQ(gun.GetObject(), Box2D(0.0f, 0.0f, 1.0f, 1.0f));
  EXPECT_EQ(gun.GetDirection(), Ray2D(0.5f, 0.5f, 1.0f, 0.5f));
  EXPECT_EQ(gun.GetCage(), 5);
  EXPECT_EQ(gun.GetCanShoot(), true);
}

TEST(gun_test, test_shot)
{
  Gun gun;
  EXPECT_EQ(gun.GetCage(), 5);
  EXPECT_EQ(gun.GetCanShoot(), true);
  gun.Shot();
  EXPECT_EQ(gun.GetCage(), 4);
  EXPECT_EQ(gun.GetCanShoot(), true);
}


TEST(gun_test, test_update)
{
  Gun gun;

  for (auto i = 5; i > 0; i--)
  {
    gun.Shot();
    EXPECT_EQ(gun.GetCage(), i-1);
    EXPECT_EQ(gun.GetCanShoot(), true);
  }
  gun.Shot();
  EXPECT_EQ(gun.GetCage(), 0);
  EXPECT_EQ(gun.GetCanShoot(), false);
}
