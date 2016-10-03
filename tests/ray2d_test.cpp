#include "gtest/gtest.h"
#include <sstream>
#include <unordered_set>
#include <memory>
#include "ray2d.hpp"

#include "box2d.hpp"

TEST(ray2d_test, test_construction)
{
  auto or1 = std::make_shared<Point2D>();
  auto dr1 = std::make_shared<Point2D>(1.0,1.0);

  auto ray1 = std::make_shared<Ray2D>(or1, dr1);
  EXPECT_EQ(*ray1->GetOrigin(), Point2D(0.0, 0.0));
  EXPECT_EQ(*ray1->GetDirection(), Point2D(1.0, 1.0));

  auto ray2 = std::make_shared<Ray2D>();
  EXPECT_EQ(*ray2->GetOrigin(), Point2D(0.0, 0.0));
  EXPECT_EQ(*ray2->GetDirection(), Point2D(0.0, 0.0));


  auto ray3 = std::make_shared<Ray2D>(*ray1);
  EXPECT_EQ(*ray3, *ray1);

  ray3 = ray2;
  EXPECT_EQ(*ray3, *ray2);
}


TEST(ray2d_test, test_calculus) 
{
  auto or1 = std::make_shared<Point2D>();
  auto dr1 = std::make_shared<Point2D>(1.0,1.0);


  auto or2 = std::make_shared<Point2D>(1.0, 1.0);
  auto dr2 = std::make_shared<Point2D>(2.0,0.0);

  {
    auto ray1 = std::make_shared<Ray2D>(or1, dr1);
    auto ray2 = std::make_shared<Ray2D>(or2, dr2);

    auto ray11 = *ray1 + *ray2;

    auto ray3 = std::make_shared<Ray2D>(ray11);;

    EXPECT_EQ(*ray3->GetOrigin(), Point2D(0.0, 0.0));
    EXPECT_EQ(*ray3->GetDirection(), Point2D(3.0, 1.0));

    auto ray4 = *ray1 - *ray3;

    EXPECT_EQ(*ray4.GetOrigin(), Point2D(3.0, 1.0));
    EXPECT_EQ(*ray4.GetDirection(), Point2D(-2.0, 0.0));
  }

  {
    auto ray1 = std::make_shared<Ray2D>(or1, dr1);
    auto ray2 = std::make_shared<Ray2D>(or1, dr2);


    EXPECT_EQ(*ray1 * *ray2, 2.0);
    EXPECT_EQ(*ray2 * *ray1, 2.0);
  }

  {
    float const value = 6;

    auto ray1 = std::make_shared<Ray2D>(or1, dr1);
    *ray1 = *ray1 * value;

    EXPECT_EQ(*ray1->GetOrigin(), Point2D(0.0, 0.0));
    EXPECT_EQ(*ray1->GetDirection(), Point2D(6.0, 6.0));
  }




  auto ray1 = std::make_shared<Ray2D>(or1, dr2);
  auto ray2 = std::make_shared<Ray2D>(dr1, dr2);

  ASSERT_THROW(*ray1 + *ray2, std::invalid_argument); 
  ASSERT_THROW(*ray1 - *ray2, std::invalid_argument); 
  ASSERT_THROW(*ray1 * *ray2, std::invalid_argument); 


}

TEST(ray2d_test, test_abs) 
{
  auto or1 = std::make_shared<Point2D>(1.0, 1.0);
  auto dr1 = std::make_shared<Point2D>(2.0,0.0);

  auto ray1 = std::make_shared<Ray2D>(or1, dr1);


  EXPECT_EQ(ray1->Abs(), 2.0);
}


TEST(ray2d_test, test_Normalisation) 
{
  auto or1 = std::make_shared<Point2D>(1.0, 1.0);
  auto dr1 = std::make_shared<Point2D>(2.0,0.0);


  auto ray = std::make_shared<Ray2D>(or1, dr1);

  ray->Normalisation();

  EXPECT_EQ(*ray->GetOrigin(), Point2D(1.0, 1.0));
  EXPECT_EQ(*ray->GetDirection(), Point2D(1.0, 0.0));
}

TEST(ray2d_test, test_CrossingRays) 
{
  auto or1 = std::make_shared<Point2D>(0.0, 0.0);
  auto dr1 = std::make_shared<Point2D>(1.0,1.0);

  auto or2 = std::make_shared<Point2D>(2.0, 1.0);
  auto dr2 = std::make_shared<Point2D>(8.0,8.0);

  auto ray1 = std::make_shared<Ray2D>(or1, dr1);
  auto ray2 = std::make_shared<Ray2D>(or2, dr2);

  EXPECT_EQ(Crossing(*ray1, *ray2), false);

  auto or3 = std::make_shared<Point2D>(2.0, 1.0);
  auto dr3 = std::make_shared<Point2D>(8.0,3.0);

  auto ray3 = std::make_shared<Ray2D>(or3, dr3);

  EXPECT_EQ(Crossing(*ray1, *ray3), true);
}


TEST(ray2d_test, test_CrossingRayBox) 
{
  auto p1 = std::make_shared<Point2D>(1.0, 2.0);
  auto p2 = std::make_shared<Point2D>(4.0,4.0);

  auto or1 = std::make_shared<Point2D>(0.0, 0.0);
  auto dr1 = std::make_shared<Point2D>(1.0,1.0);

  auto box = std::make_shared<Box2D>(p1, p2);
  auto ray1 = std::make_shared<Ray2D>(or1, dr1);

  EXPECT_EQ(Crossing(*ray1, *box), true);


  auto or2 = std::make_shared<Point2D>(0.0, 0.0);
  auto dr2 = std::make_shared<Point2D>(4.0,1.0);

  auto ray2 = std::make_shared<Ray2D>(or2, dr2);

  EXPECT_EQ(Crossing(*ray2, *box), true);
}


TEST(ray2d_test, test_output) 
{
  auto p1 = std::make_shared<Point2D>(1.0, 2.0);
  auto p2 = std::make_shared<Point2D>(4.0,4.0);

  std::stringstream s;
  s << Ray2D(p1, p2);

  EXPECT_EQ(s.str(), "Ray2D { from (1, 2), to (4, 4)}");
}