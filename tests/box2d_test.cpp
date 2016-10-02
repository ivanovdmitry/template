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

TEST(box2d_test, test_GetCenter)
{
  auto point1 = std::make_shared<Point2D>(1.1f,1.2f);
  auto point2 = std::make_shared<Point2D>(2.1f,2.2f);
  Box2D box(point1, point2);

  EXPECT_EQ(*box.GetCenter(), Point2D(1.6, 1.7));
}


TEST(box2d_test, test_Move)
{
  auto point1 = std::make_shared<Point2D>(1.0f,1.0f);
  auto point2 = std::make_shared<Point2D>(2.0f,2.0f);
  Box2D box(point1, point2);

  auto point3 = std::make_shared<Point2D>(3.0f,3.0f);

  box.SetCenter(point3);
  EXPECT_EQ(*box.GetCenter(), Point2D(3.0, 3.0));
  EXPECT_EQ(*box.GetMin(), Point2D(2.5, 2.5));
  EXPECT_EQ(*box.GetMax(), Point2D(3.5, 3.5));
}

TEST(box2d_test, test_Crossing)
{
  {
    auto point1 = std::make_shared<Point2D>(1.0f,1.0f);
    auto point2 = std::make_shared<Point2D>(2.0f,2.0f);
    auto point3 = std::make_shared<Point2D>(2.5f,2.5f);
    auto point4 = std::make_shared<Point2D>(3.5f,3.5f);
    // два прямоугольника на некотором расстоянии друг от друга
    Box2D box1(point1, point2);
    Box2D box2(point3, point4);
    EXPECT_EQ(Crossing(box1, box2), false);

    // пересечение прямоугольников когда одна точка находится внутри другого прямоугольника 
    Box2D box3(point1, point3);
    Box2D box4(point2, point4);
    EXPECT_EQ(Crossing(box3, box4), true);

    // один прямоугольник внутри другого
    Box2D box5(point1, point4);
    Box2D box6(point2, point3);
    EXPECT_EQ(Crossing(box5, box6), true);
  }
  // пересечение, когда внутри прямоугольника нет точки
  {
    auto point5 = std::make_shared<Point2D>(2.0f,1.0f);
    auto point6 = std::make_shared<Point2D>(1.0f,2.0f);
    auto point7 = std::make_shared<Point2D>(3.0f,10.0f);
    auto point8 = std::make_shared<Point2D>(10.0f,3.0f);

    Box2D box7(point5, point7);
    Box2D box8(point6, point8);
    EXPECT_EQ(Crossing(box7, box8), true);
  }
  // пересечение прямоугольников когда две точка находится внутри другого прямоугольника 
  {
    auto point9 = std::make_shared<Point2D>(1.0f,1.0f);
    auto point10 = std::make_shared<Point2D>(5.0f,5.0f);
    auto point11 = std::make_shared<Point2D>(3.0f,2.0f);
    auto point12 = std::make_shared<Point2D>(9.0f,3.0f);

    Box2D box9(point9, point10);
    Box2D box10(point11, point12);
    EXPECT_EQ(Crossing(box9, box10), true);
  }

}
