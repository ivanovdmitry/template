#include "gtest/gtest.h"
#include "Box2D.h"
#include <sstream>
#include <unordered_set>



TEST(Box2D_test, test_construction)
{
  Box2D box1;
  EXPECT_EQ(box1.LeftBot(), Point2D(0.0, 0.0));
  EXPECT_EQ(box1.RightTop(), Point2D(1.0, 1.0));

  Box2D box2 = {Point2D(1.0, 2.0), Point2D(5.0, 6.0)};
  EXPECT_EQ(box2.LeftBot(), Point2D(1.0, 2.0));
  EXPECT_EQ(box2.RightTop(), Point2D(5.0, 6.0));

  Box2D box3 = box2;
  EXPECT_EQ(box2, box3);
}
