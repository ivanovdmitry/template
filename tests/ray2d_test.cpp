#include "gtest/gtest.h"
#include <sstream>
#include <unordered_set>
#include <memory>
#include "ray2d.hpp"


TEST(ray2d_test, test_construction)
{
  auto or1 = std::make_shared<Point2D>();
  auto dr1 = std::make_shared<Point2D>(1.0,1.0);

  Ray2D ray1(or1, dr1);
  EXPECT_EQ(*ray1.GetOrigin(), Point2D(0.0, 0.0));
  EXPECT_EQ(*ray1.GetDirection(), Point2D(1.0, 1.0));

  Ray2D ray2;
  EXPECT_EQ(*ray2.GetOrigin(), Point2D(0.0, 0.0));
  EXPECT_EQ(*ray2.GetDirection(), Point2D(0.0, 0.0));

  Ray2D ray3 (ray1);
  EXPECT_EQ(ray3, ray1);

  ray3 = ray2;
  EXPECT_EQ(ray3, ray2);
}