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

  Box2D box4(1.0, 2.0, 3.0, 4.0);
  EXPECT_EQ(box4.LeftBot(), Point2D(1.0, 2.0));
  EXPECT_EQ(box4.RightTop(), Point2D(3.0, 4.0));

// TODO need fix: 
  Box2D box5(3.0, 2.0, 1.0, 4.0);
  EXPECT_EQ(box5.LeftBot(), Point2D(1.0, 2.0));
  EXPECT_EQ(box5.RightTop(), Point2D(3.0, 4.0));

  Box2D box6(3.0, 8.0, 1.0, 4.0);
  EXPECT_EQ(box6.LeftBot(), Point2D(1.0, 4.0));
  EXPECT_EQ(box6.RightTop(), Point2D(3.0, 8.0));
}

TEST(Box2D_test, test_tips)
{
  Box2D box;
  EXPECT_EQ(box.LeftBot(), Point2D(0.0, 0.0));
  EXPECT_EQ(box.LeftTop(), Point2D(0.0, 1.0));
  EXPECT_EQ(box.RightTop(), Point2D(1.0, 1.0));
  EXPECT_EQ(box.RightBot(), Point2D(1.0, 0.0));
}


TEST(Box2D_test, test_output)
{
  std::stringstream s;
  s << Box2D();
  EXPECT_EQ(s.str(), "Box 2D {Left Bot Point 2D {0, 0}, Right Top Point 2D {1, 1}}");
}

TEST(Box2D_test, test_initializer_list)
{
  Box2D box1 = {Point2D(1.0, 2.0), Point2D(5.0, 6.0), Point2D(3.0, 3.0)};
  EXPECT_EQ(box1.LeftBot(), Point2D(1.0, 2.0));
  EXPECT_EQ(box1.RightTop(), Point2D(5.0, 6.0));

  Box2D box2 = {Point2D(1.0, 8.0)};
  EXPECT_EQ(box2.LeftBot(), Point2D(1.0, 8.0));
  EXPECT_EQ(box2.RightTop(), Point2D(1.0, 1.0));

  Box2D box3 = {0.0, 5.0, 7.0, 9.0, 1.0};
  EXPECT_EQ(box3.LeftBot(), Point2D(0.0, 5.0));
  EXPECT_EQ(box3.RightTop(), Point2D(7.0, 9.0));

// TODO: need fix bug: Box2D.h line 32
  Box2D box4 = {2.0, 3.0, 4.0};
  EXPECT_EQ(box4.LeftBot(), Point2D(2.0, 3.0));
  EXPECT_EQ(box4.RightTop(), Point2D(4.0, 1.0));
}

TEST(Box2D_test, test_square_brackets)
{
  Box2D box;
  EXPECT_EQ(box[0], Point2D(0.0, 0.0));
  EXPECT_EQ(box[1], Point2D(1.0, 1.0));
  ASSERT_THROW(box[2], std::invalid_argument);
}

TEST(Box2D_test, test_centre)
{
  Box2D box1;
  EXPECT_EQ(box1.Centre(), Point2D(0.5, 0.5));
  Box2D box2 = { Point2D(-1.0, -1.0), Point2D(1.0, 1.0)};
  EXPECT_EQ(box2.Centre(), Point2D(0.0, 0.0));
}

TEST(Box2D_test, test_move)
{
  Box2D box1;
  box1.Move(Point2D(1.5, 1.5));
  EXPECT_EQ(box1.LeftBot(), Point2D(1.0, 1.0));
  EXPECT_EQ(box1.RightTop(), Point2D(2.0, 2.0));

  Box2D box2;
  box2.Move(3.5, 3.5);
  EXPECT_EQ(box2.LeftBot(), Point2D(3.0, 3.0));
  EXPECT_EQ(box2.RightTop(), Point2D(4.0, 4.0));
}

TEST(Box2D_test, test_intsec)
{
  Box2D box1 = {Point2D(0, 0), Point2D{5, 5}};
  Box2D box2 = {3, 3, 8, 8};
  EXPECT_EQ(Intsec(box1, box2), true);

  box2.Move(7.5, 7.5);
  EXPECT_EQ(Intsec(box1, box2), true);

  box2.Move(10, 10);
  EXPECT_EQ(Intsec(box1, box2), false);

  Box2D box3 = {-1, 1, 8, 2};
  EXPECT_EQ(Intsec(box1, box3), true);

  Box2D box4 = {1, -1, 2, 8};
  EXPECT_EQ(Intsec(box1, box4), true);
}
