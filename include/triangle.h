#pragma once

#include <cmath>
#include <format>
#include <iostream>

#include "figure.h"

template <Scalar T> class Triangle final : public Figure<T> {
public:
  Triangle();
  static constexpr int VERTICIES_COUNT = 3;
  Triangle(std::unique_ptr<Point<T>> vertex[VERTICIES_COUNT]);
  Point<T> getGeomitricCenter() const override;
  void print(std::ostream &os) const override;
  void read(std::istream &is) override;
  std::shared_ptr<Figure<T>> clone() const override;
  Triangle(const Triangle &other);
  Triangle(Triangle &&other) noexcept;
  Triangle &operator=(Triangle &r_fig);
  Triangle &operator=(Triangle &&r_fig);
  bool operator==(const Triangle &r_fig) const;
  operator double() const override;
  ~Triangle();

private:
  std::unique_ptr<Point<T>> vertex[VERTICIES_COUNT];
};

template <Scalar T> Triangle<T>::Triangle() {
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    vertex[i] = std::make_unique<Point<T>>(Point<T>{0, 0});
  }
}

template <Scalar T>
Triangle<T>::Triangle(std::unique_ptr<Point<T>> vertices[VERTICIES_COUNT]) {
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    vertex[i] = std::make_unique<Point<T>>(*vertices[i]);
  }
}

template <Scalar T> std::shared_ptr<Figure<T>> Triangle<T>::clone() const {
  auto copy = std::make_shared<Triangle<T>>();
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    *copy->vertex[i] = *this->vertex[i];
  }
  return copy;
}

template <Scalar T> void Triangle<T>::print(std::ostream &os) const {
  os << "Треугольник:" << std::endl;
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    os << std::format("Вершина {}: ({}, {})", i + 1, vertex[i]->x,
                      vertex[i]->y);
  }
}

template <Scalar T> void Triangle<T>::read(std::istream &is) {
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    std::cout << "Введите координаты x и y треугольника через пробел: "
              << std::endl;
    is >> vertex[i]->x >> vertex[i]->y;
  }
}

template <Scalar T> Triangle<T> &Triangle<T>::operator=(Triangle &r_fig) {
  if (this != &r_fig) {
    for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
      *vertex[i] = *r_fig.vertex[i];
    }
  }
  return *this;
}

template <Scalar T> Triangle<T> &Triangle<T>::operator=(Triangle<T> &&r_fig) {
  if (this != &r_fig) {
    for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
      vertex[i] = std::move(r_fig.vertex[i]);
    }
  }
  return *this;
}

template <Scalar T> Triangle<T>::Triangle(const Triangle<T> &other) {
  for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
    vertex[i] = std::make_unique<Point<T>>(*other.vertex[i]);
  }
}

template <Scalar T> Triangle<T>::Triangle(Triangle<T> &&other) noexcept {
  for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
    vertex[i] = std::move(other.vertex[i]);
  }
}

template <Scalar T>
bool Triangle<T>::operator==(const Triangle<T> &r_fig) const {
  for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
    if ((vertex[i]->x != r_fig.vertex[i]->x) ||
        (vertex[i]->y != r_fig.vertex[i]->y)) {
      return false;
    }
  }
  return true;
}

template <Scalar T> Triangle<T>::operator double() const {
  return std::abs(vertex[0]->x * (vertex[1]->y - vertex[2]->y) +
                  vertex[1]->x * (vertex[2]->y - vertex[0]->y) +
                  vertex[2]->x * (vertex[0]->y - vertex[1]->y)) /
         2;
}

template <Scalar T> Point<T> Triangle<T>::getGeomitricCenter() const {
  return {.x = (vertex[0]->x + vertex[1]->x + vertex[2]->x) / 3,
          .y = (vertex[0]->y + vertex[1]->y + vertex[2]->y) / 3};
}

template <Scalar T> Triangle<T>::~Triangle() {}
