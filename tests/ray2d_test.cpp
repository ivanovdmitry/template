#include "gtest/gtest.h"
#include "Ray2D.h"
#include <sstream>
#include <unordered_set>



TEST(Ray2D_test, test_construction)
{
  Ray2D ray1;
  EXPECT_EQ(ray1.Point(), Point2D(0.0, 0.0));
  EXPECT_EQ(ray1.Vector(), Point2D(0.0, 0.0));

  Ray2D ray2(Point2D(1.0,1.0), Point2D(2.0,2.0));
  EXPECT_EQ(ray2.Point(), Point2D(1.0, 1.0));
  EXPECT_EQ(ray2.Vector(), Point2D(2.0, 2.0));

  Ray2D ray3 = ray2;
  EXPECT_EQ(ray2, ray3);

  Ray2D ray4(1.0, 2.0, 3.0, 4.0);
  EXPECT_EQ(ray4.Point(), Point2D(1.0, 2.0));
  EXPECT_EQ(ray4.Vector(), Point2D(3.0, 4.0));


  Ray2D ray5(3.0, 8.0, 1.0, 0.00000001);
  EXPECT_EQ(ray5.Point(), Point2D(3.0, 8.0));
  EXPECT_EQ(ray5.Vector(), Point2D(1.0, 0.0));

  Ray2D ray6(Point2D(3.0, 8.0), Point2D(1.0, 0.0));
  EXPECT_EQ(ray6.Point(), Point2D(3.0, 8.0));
  EXPECT_EQ(ray6.Vector(), Point2D(1.0, 0.0));
}

TEST(Ray2D_test, test_output)
{
  std::stringstream s;
  s << Ray2D();
  EXPECT_EQ(s.str(), "Ray 2D { Origin Point 2D {0, 0}, Direction Point 2D {0, 0}}");
}