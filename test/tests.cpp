#include <gtest/gtest.h>

#include "array.h"
#include "figure.h"
#include "rectangle.h"
#include "square.h"
#include "triangle.h"

TEST(PointTest, BasicCreation) {
  Point<int> p{1, 2};
  EXPECT_EQ(p.x, 1);
  EXPECT_EQ(p.y, 2);
}

TEST(PointTest, DifferentTypes) {
  Point<double> p{1.5, 2.5};
  EXPECT_DOUBLE_EQ(p.x, 1.5);
  EXPECT_DOUBLE_EQ(p.y, 2.5);
}

TEST(TriangleTest, DefaultConstructor) {
  Triangle<double> t;
  SUCCEED();
}

TEST(TriangleTest, AreaCalculation) {
  std::unique_ptr<Point<double>> vertices[3];
  vertices[0] = std::make_unique<Point<double>>(Point<double>{0, 0});
  vertices[1] = std::make_unique<Point<double>>(Point<double>{3, 0});
  vertices[2] = std::make_unique<Point<double>>(Point<double>{0, 4});

  Triangle<double> t(vertices);
  double area = static_cast<double>(t);
  EXPECT_DOUBLE_EQ(area, 6.0); // (3*4)/2 = 6
}

TEST(TriangleTest, GeometricCenter) {
  std::unique_ptr<Point<double>> vertices[3];
  vertices[0] = std::make_unique<Point<double>>(Point<double>{0, 0});
  vertices[1] = std::make_unique<Point<double>>(Point<double>{3, 0});
  vertices[2] = std::make_unique<Point<double>>(Point<double>{0, 3});

  Triangle<double> t(vertices);
  Point<double> center = t.getGeomitricCenter();
  EXPECT_DOUBLE_EQ(center.x, 1.0);
  EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(TriangleTest, Clone) {
  std::unique_ptr<Point<double>> vertices[3];
  vertices[0] = std::make_unique<Point<double>>(Point<double>{0, 0});
  vertices[1] = std::make_unique<Point<double>>(Point<double>{1, 0});
  vertices[2] = std::make_unique<Point<double>>(Point<double>{0, 1});

  Triangle<double> t(vertices);
  auto cloned = t.clone();

  EXPECT_NE(cloned.get(), &t);
  EXPECT_DOUBLE_EQ(static_cast<double>(*cloned), 0.5);
}

TEST(SquareTest, DefaultConstructor) {
  Square<double> s;
  SUCCEED();
}

TEST(SquareTest, AreaCalculation) {
  std::unique_ptr<Point<double>> vertices[4];
  vertices[0] = std::make_unique<Point<double>>(Point<double>{0, 0});
  vertices[1] = std::make_unique<Point<double>>(Point<double>{2, 0});
  vertices[2] = std::make_unique<Point<double>>(Point<double>{2, 2});
  vertices[3] = std::make_unique<Point<double>>(Point<double>{0, 2});

  Square<double> s(vertices);
  double area = static_cast<double>(s);
  EXPECT_DOUBLE_EQ(area, 4.0);
}

TEST(SquareTest, GeometricCenter) {
  std::unique_ptr<Point<double>> vertices[4];
  vertices[0] = std::make_unique<Point<double>>(Point<double>{0, 0});
  vertices[1] = std::make_unique<Point<double>>(Point<double>{2, 0});
  vertices[2] = std::make_unique<Point<double>>(Point<double>{2, 2});
  vertices[3] = std::make_unique<Point<double>>(Point<double>{0, 2});

  Square<double> s(vertices);
  Point<double> center = s.getGeomitricCenter();
  EXPECT_DOUBLE_EQ(center.x, 1.0);
  EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(RectangleTest, DefaultConstructor) {
  Rectangle<double> r;
  SUCCEED();
}

TEST(RectangleTest, AreaCalculation) {
  std::unique_ptr<Point<double>> vertices[4];
  vertices[0] = std::make_unique<Point<double>>(Point<double>{0, 0});
  vertices[1] = std::make_unique<Point<double>>(Point<double>{4, 0});
  vertices[2] = std::make_unique<Point<double>>(Point<double>{4, 3});
  vertices[3] = std::make_unique<Point<double>>(Point<double>{0, 3});

  Rectangle<double> r(vertices);
  double area = static_cast<double>(r);
  EXPECT_DOUBLE_EQ(area, 12.0);
}

TEST(RectangleTest, GeometricCenter) {
  std::unique_ptr<Point<double>> vertices[4];
  vertices[0] = std::make_unique<Point<double>>(Point<double>{0, 0});
  vertices[1] = std::make_unique<Point<double>>(Point<double>{4, 0});
  vertices[2] = std::make_unique<Point<double>>(Point<double>{4, 3});
  vertices[3] = std::make_unique<Point<double>>(Point<double>{0, 3});

  Rectangle<double> r(vertices);
  Point<double> center = r.getGeomitricCenter();
  EXPECT_DOUBLE_EQ(center.x, 2.0);
  EXPECT_DOUBLE_EQ(center.y, 1.5);
}

TEST(ArrayTest, BasicOperations) {
  Array<Square<double>> arr;

  // Создаем квадрат
  std::unique_ptr<Point<double>> vertices[4];
  vertices[0] = std::make_unique<Point<double>>(Point<double>{0, 0});
  vertices[1] = std::make_unique<Point<double>>(Point<double>{1, 0});
  vertices[2] = std::make_unique<Point<double>>(Point<double>{1, 1});
  vertices[3] = std::make_unique<Point<double>>(Point<double>{0, 1});

  Square<double> square(vertices);

  arr.PushItem(square);
  EXPECT_EQ(arr.getSize(), 1);

  Square<double> &first = arr[0];
  EXPECT_DOUBLE_EQ(static_cast<double>(first), 1.0);

  arr.DeleteFigure(0);
  EXPECT_EQ(arr.getSize(), 0);
}

TEST(ArrayTest, TotalAreaCalculation) {
  Array<Square<double>> arr;

  std::unique_ptr<Point<double>> vertices1[4];
  vertices1[0] = std::make_unique<Point<double>>(Point<double>{0, 0});
  vertices1[1] = std::make_unique<Point<double>>(Point<double>{1, 0});
  vertices1[2] = std::make_unique<Point<double>>(Point<double>{1, 1});
  vertices1[3] = std::make_unique<Point<double>>(Point<double>{0, 1});
  Square<double> square1(vertices1);

  std::unique_ptr<Point<double>> vertices2[4];
  vertices2[0] = std::make_unique<Point<double>>(Point<double>{0, 0});
  vertices2[1] = std::make_unique<Point<double>>(Point<double>{2, 0});
  vertices2[2] = std::make_unique<Point<double>>(Point<double>{2, 2});
  vertices2[3] = std::make_unique<Point<double>>(Point<double>{0, 2});
  Square<double> square2(vertices2);

  arr.PushItem(square1);
  arr.PushItem(square2);

  double totalArea = arr.TotalArea();
  EXPECT_DOUBLE_EQ(totalArea, 5.0); // 1 + 4 = 5
}

TEST(ArrayTest, ResizeAndMove) {
  Array<Square<double>> arr;

  for (int i = 0; i < 10; ++i) {
    Square<double> s;
    arr.PushItem(s);
  }

  EXPECT_GE(arr.getSize(), 10);
}

TEST(ArrayTest, MoveSemantics) {
  Array<Square<int>> arr1;
  Square<int> sq;
  arr1.PushItem(sq);

  Array<Square<int>> arr2(std::move(arr1));
  EXPECT_EQ(arr1.getSize(), 0);
  EXPECT_EQ(arr2.getSize(), 1);
}

TEST(FigureTest, Polymorphism) {
  Array<std::shared_ptr<Figure<double>>> figures;

  auto tri = std::make_shared<Triangle<double>>();
  auto sq = std::make_shared<Square<double>>();

  figures.PushItem(tri);
  figures.PushItem(sq);

  EXPECT_NO_THROW(figures.TotalArea());
  EXPECT_NO_THROW(figures.PrintFigures());
}

TEST(ArrayPointerTest, BasicOperations) {
  Array<std::shared_ptr<Figure<double>>> arr;

  std::unique_ptr<Point<double>> triVertices[3];
  triVertices[0] = std::make_unique<Point<double>>(Point<double>{0, 0});
  triVertices[1] = std::make_unique<Point<double>>(Point<double>{3, 0});
  triVertices[2] = std::make_unique<Point<double>>(Point<double>{0, 4});
  auto triangle = std::make_shared<Triangle<double>>(triVertices);

  std::unique_ptr<Point<double>> squareVertices[4];
  squareVertices[0] = std::make_unique<Point<double>>(Point<double>{0, 0});
  squareVertices[1] = std::make_unique<Point<double>>(Point<double>{2, 0});
  squareVertices[2] = std::make_unique<Point<double>>(Point<double>{2, 2});
  squareVertices[3] = std::make_unique<Point<double>>(Point<double>{0, 2});
  auto square = std::make_shared<Square<double>>(squareVertices);

  arr.PushItem(triangle);
  arr.PushItem(square);

  EXPECT_EQ(arr.getSize(), 2);

  double totalArea = arr.TotalArea();
  EXPECT_DOUBLE_EQ(totalArea, 10.0); // 6 (triangle) + 4 (square) = 10
}

TEST(ArrayPointerTest, CloneAndAssignment) {
  Array<std::shared_ptr<Figure<double>>> arr;

  std::unique_ptr<Point<double>> vertices[3];
  vertices[0] = std::make_unique<Point<double>>(Point<double>{0, 0});
  vertices[1] = std::make_unique<Point<double>>(Point<double>{2, 0});
  vertices[2] = std::make_unique<Point<double>>(Point<double>{0, 2});
  auto triangle = std::make_shared<Triangle<double>>(vertices);

  arr.PushItem(triangle);

  Array<std::shared_ptr<Figure<double>>> arrCopy(arr);
  EXPECT_EQ(arrCopy.getSize(), arr.getSize());
}

TEST(IOTest, TriangleInputOutput) {
  Triangle<double> t;

  std::istringstream input("1 2\n3 4\n5 6\n");
  std::ostringstream output;

  t.read(input);
  t.print(output);

  EXPECT_FALSE(output.str().empty());
  EXPECT_TRUE(output.str().find("Треугольник") != std::string::npos);
}

TEST(IOTest, SquareInputOutput) {
  Square<double> s;

  std::istringstream input("0 0\n1 0\n1 1\n0 1\n");
  std::ostringstream output;

  s.read(input);
  s.print(output);

  EXPECT_FALSE(output.str().empty());
  EXPECT_TRUE(output.str().find("Квадрат") != std::string::npos);
}

TEST(ExceptionTest, ArrayOutOfBounds) {
  Array<Square<double>> arr;

  EXPECT_THROW(arr[0], std::out_of_range);

  Square<double> s;
  arr.PushItem(s);

  EXPECT_NO_THROW(arr[0]);
  EXPECT_THROW(arr[1], std::out_of_range);
}

TEST(ExceptionTest, PopEmptyArray) {
  Array<Square<double>> arr;

  EXPECT_THROW(arr.PopItem(), std::out_of_range);
}

TEST(TypeTest, DifferentScalarTypes) {
  Triangle<int> triInt;
  Square<int> squareInt;
  Rectangle<int> rectInt;

  Triangle<float> triFloat;
  Square<float> squareFloat;
  Rectangle<float> rectFloat;

  Triangle<double> triDouble;
  Square<double> squareDouble;
  Rectangle<double> rectDouble;

  SUCCEED();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}