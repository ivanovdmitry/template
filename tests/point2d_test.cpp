#include "gtest/gtest.h"
#include "Point2D.hpp"
#include <sstream>
#include <unordered_set>

TEST(Point2D_test, test_construction)
{
  // Тест на создание объекта по умолчанию.
  Point2D p1;
  EXPECT_EQ(p1.x(), 0.0f);
  EXPECT_EQ(p1.y(), 0.0f);

  // Тест на создание объекта с параметрами.
  Point2D p2 = { 1.2f, 2.4f };
  EXPECT_EQ(p2.x(), 1.2f);
  EXPECT_EQ(p2.y(), 2.4f);

  // Тест на создание копии объекта.
  Point2D p3 = p2;
  EXPECT_EQ(p3, p2);
}

TEST(Point2D_test, test_initializer_list)
{
  Point2D p1 = { 1.0f, 2.0f, 3.0f };
  EXPECT_EQ(p1.x(), 1.0f);
  EXPECT_EQ(p1.y(), 2.0f);

  Point2D p2 = { 1.0f };
  EXPECT_EQ(p2.x(), 1.0f);
  EXPECT_EQ(p2.y(), 0.0f);
}

TEST(Point2D_test, test_assignment)
{
  Point2D p1;
  p1 = { 1.2f, 2.4f };
  EXPECT_EQ(p1, Point2D(1.2f, 2.4f));
}

TEST(Point2D_test, test_equality)
{
  Point2D p1 = { 1.2f, 2.4f };
  Point2D p2 = { 1.2f, 2.4f };
  Point2D p3 = { 1.3f, 2.4f };
  Point2D p4 = { 1.2f, 2.5f };

  EXPECT_EQ(p1, p2);
  EXPECT_NE(p1, p3);
  EXPECT_LT(p1, p3);
  EXPECT_LT(p1, p4);
}

TEST(Point2D_test, test_calculus)
{
  Point2D p1 = { 1.2f, 2.4f };
  Point2D p2 = { 1.0f, 2.0f };

  EXPECT_EQ(p1 + p2, Point2D(2.2f, 4.4f));
  EXPECT_EQ(p1 - p2, Point2D(0.2f, 0.4f));
  EXPECT_EQ(p1 * 2.0f, Point2D(2.4f, 4.8f));
  EXPECT_EQ(p1 / 2.0f, Point2D(0.6f, 1.2f));

  p1 += { 1.2f, 2.4f };
  EXPECT_EQ(p1, Point2D(2.4f, 4.8f));

  p1 -= { 1.2f, 2.4f };
  EXPECT_EQ(p1, Point2D(1.2f, 2.4f));

  p1 *= 2.0f;
  EXPECT_EQ(p1, Point2D(2.4f, 4.8f));

  p1 /= 2.0f;
  EXPECT_EQ(p1, Point2D(1.2f, 2.4f));

  ASSERT_THROW(p1 / 0.0f, std::invalid_argument);

  Point2D p3 = { 6.0f, 8.0f };
  EXPECT_EQ(p3.Lenght(), 10.0);

  Point2D p4 = { 0.0, 0.0 };
  ASSERT_THROW(p4.Normalization() , std::invalid_argument);
  ASSERT_THROW(GetNormal(p4) , std::invalid_argument);
}

TEST(Point2D_test, test_square_brackets)
{
  Point2D p1 = { 1.2f, 2.4f };
  EXPECT_EQ(p1[0], 1.2f);
  EXPECT_EQ(p1[1], 2.4f);
  EXPECT_EQ(p1[2], 0.0f);
}

TEST(Point2D_test, test_hash)
{
  Point2D::Hash hasher;
  EXPECT_EQ(hasher(Point2D(0.0f, 0.0f)), 0);

  std::unordered_set<Point2D, Point2D::Hash> hashTable;
  hashTable.insert(Point2D(0.0f, 0.0f));
  hashTable.insert(Point2D(1.0f, 0.0f));
  EXPECT_EQ(hashTable.size(), 2);
}

TEST(Point2D_test, test_output)
{
  std::stringstream s;
  s << Point2D(1.2f, 0.2f);
  EXPECT_EQ(s.str(), "Point 2D {1.2, 0.2}");
}

TEST(point2d_test, test_lenght)
{
  Point2D p = {6.0, 8.0};
  EXPECT_EQ(p.Lenght(), 10.0);
}

TEST(point2d_test, test_normalization)
{
  Point2D p = {6.0, 8.0};
  p.Normalization();
  EXPECT_EQ(p.x(), 0.6f);
  EXPECT_EQ(p.y(), 0.8f);
}

TEST(Point2D_test, test_move_semantics)
{
  Point2D point1;
  Point2D point2(1.0f, 1.0f);
  EXPECT_EQ(point1 = std::move(point2), Point2D(1.0f, 1.0f));
  EXPECT_EQ(point2, Point2D(0.0f, 0.0f));

  Point2D point3(Point2D(1.0f, 1.0f));
  EXPECT_EQ(point3, Point2D(1.0f, 1.0f));
}