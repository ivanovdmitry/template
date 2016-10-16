#include "Alien.hpp"
#include "Bullet.hpp"
#include "Gun.hpp"
#include "Obstacle.hpp"

#include "gtest/gtest.h"


TEST(bullet_test, test_construction)
{
  Bullet bullet1;

  EXPECT_EQ(bullet1.GetObject(), Box2D(0.0f, 0.0f, 1.0f, 1.0f));
  EXPECT_EQ(bullet1.GetDirection(), Ray2D(0.0f, 0.0f, 1.0f, 0.5f));
  EXPECT_EQ(bullet1.GetVelocity(), 1);
  EXPECT_EQ(bullet1.GetEnergy(), 1);
  EXPECT_EQ(bullet1.GetIsEnabled(), true);

  Bullet bullet2(Box2D(2.0, 3.0, 4.0, 5.0));
  EXPECT_EQ(bullet2.GetObject(), Box2D(2.0, 3.0, 4.0, 5.0));

  Bullet bullet3(Ray2D(2.0, 3.0, 4.0, 6.0));
  EXPECT_EQ(bullet3.GetDirection(), Ray2D(2.0, 3.0, 4.0, 6.0));

  Bullet bullet4(Box2D(2.0, 3.0, 4.0, 5.0), Ray2D(2.0, 3.0, 4.0, 6.0));
  EXPECT_EQ(bullet4.GetObject(), Box2D(2.0, 3.0, 4.0, 5.0));
  EXPECT_EQ(bullet4.GetDirection(), Ray2D(2.0, 3.0, 4.0, 6.0));
}

TEST(bullet_test, test_sets)
{
  Bullet bullet;
  bullet.SetObject(Box2D(1.0, 2.0, 3.0, 4.0));
  EXPECT_EQ(bullet.GetObject(), Box2D(1.0, 2.0, 3.0, 4.0));

  bullet.SetDirection(Ray2D(5.0, 6.0, 7.0, 8.0));
  EXPECT_EQ(bullet.GetDirection(), Ray2D(5.0f, 6.0f, 7.0f, 8.0f));

  bullet.SetVelocity(2.03f);
  EXPECT_EQ(bullet.GetVelocity(), 2.03f);

  bullet.SetEnergy(7.03f);
  EXPECT_EQ(bullet.GetEnergy(), 7.03f);
  EXPECT_EQ(bullet.GetIsEnabled(), true);
}

TEST(bullet_test, test_move)
{
  Bullet bullet;
  bullet.SetDirection({ 0.0, 0.0, 0.0, 1.0 });
  bullet.Move();
  EXPECT_EQ(bullet.GetObject(), Box2D(0.0, 1.0, 1.0, 2.0));
}

TEST(bullet_test, test_output)
{
  std::stringstream s;
  s << Bullet();
  EXPECT_EQ(s.str(), "Unit: Bullet object: Box 2D {Left Bottom Point 2D {0, 0}, Right Top Point 2D {1, 1}}; Direction Ray 2D { Origin Point 2D {0, 0}, Direction Point 2D {1, 0.5}}; Velocity = 1; Energy = 1; is enabled = 1");
}

TEST(bullet_test, test_contact)
{
  Bullet bullet;
  Obstacle obstacle;

  Contact(bullet, obstacle);
  EXPECT_EQ(bullet.GetIsEnabled(), false);
}