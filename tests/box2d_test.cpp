#include "gtest/gtest.h"
#include <sstream>
#include <unordered_set>
#include <memory>
#include "box2d.hpp"


TEST(box2d_test, test_construction)
{
  Box2D box1;
  EXPECT_EQ(*box1.GetMin(), *std::make_shared<Point2D>(0.0f, 0.0f));
  EXPECT_EQ(*box1.GetMax(), *std::make_shared<Point2D>(0.0f, 0.0f));

  auto point1 = std::make_shared<Point2D>(1.1f,1.2f);
  auto point2 = std::make_shared<Point2D>(2.1f,2.2f);
  Box2D box2 (point1, point2);

  EXPECT_EQ(*box2.GetMin(), *std::make_shared<Point2D>(1.1,1.2));
  EXPECT_EQ(*box2.GetMax(), *std::make_shared<Point2D>(2.1f,2.2f));

  Box2D box3 = box2;
  EXPECT_EQ(box3, box2);
}


TEST(box2d_test, test_output)
{
  auto point1 = std::make_shared<Point2D>(1.1f,1.2f);
  auto point2 = std::make_shared<Point2D>(2.1f,2.2f);

  std::stringstream s;
  s << Box2D(point1, point2);

  EXPECT_EQ(s.str(), "Box2D {(1.1, 1.2), (2.1, 2.2)}");
}
