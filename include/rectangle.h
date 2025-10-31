#pragma once

#include <cmath>
#include <format>
#include <iostream>

#include "figure.h"

template <Scalar T> class Rectangle final : public Figure<T> {
public:
  Rectangle();
  static constexpr int VERTICIES_COUNT = 4;
  Rectangle(std::unique_ptr<Point<T>> vertex[VERTICIES_COUNT]);
  Point<T> getGeomitricCenter() const override;
  void print(std::ostream &os) const override;
  void read(std::istream &is) override;
  std::shared_ptr<Figure<T>> clone() const override;
  Rectangle(const Rectangle &other);
  Rectangle(Rectangle &&other) noexcept;
  Rectangle &operator=(Rectangle &r_fig);
  Rectangle &operator=(Rectangle &&r_fig);
  bool operator==(const Rectangle &r_fig) const;
  operator double() const override;
  ~Rectangle();

private:
  std::unique_ptr<Point<T>> vertex[VERTICIES_COUNT];
};

template <Scalar T> Rectangle<T>::Rectangle() {
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    vertex[i] = std::make_unique<Point<T>>(Point<T>{0, 0});
  }
}

template <Scalar T>
Rectangle<T>::Rectangle(std::unique_ptr<Point<T>> vertices[VERTICIES_COUNT]) {
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    vertex[i] = std::make_unique<Point<T>>(*vertices[i]);
  }
}

template <Scalar T> std::shared_ptr<Figure<T>> Rectangle<T>::clone() const {
  auto copy = std::make_shared<Rectangle<T>>();
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    *copy->vertex[i] = *this->vertex[i];
  }
  return copy;
}

template <Scalar T> void Rectangle<T>::print(std::ostream &os) const {
  os << "Прямоугольник:" << std::endl;
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    os << std::format("Вершина {}: ({}, {})", i + 1, vertex[i]->x,
                      vertex[i]->y);
  }
}

template <Scalar T> void Rectangle<T>::read(std::istream &is) {
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    std::cout << "Введите координаты x и y прямоугольника через пробел: "
              << std::endl;
    is >> vertex[i]->x >> vertex[i]->y;
  }
}

template <Scalar T> Rectangle<T>::Rectangle(const Rectangle<T> &other) {
  for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
    vertex[i] = std::make_unique<Point<T>>(*other.vertex[i]);
  }
}

template <Scalar T> Rectangle<T>::Rectangle(Rectangle<T> &&other) noexcept {
  for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
    vertex[i] = std::move(other.vertex[i]);
  }
}

template <Scalar T> Rectangle<T> &Rectangle<T>::operator=(Rectangle &r_fig) {
  if (this != &r_fig) {
    for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
      *vertex[i] = *r_fig.vertex[i];
    }
  }
  return *this;
}

template <Scalar T>
Rectangle<T> &Rectangle<T>::operator=(Rectangle<T> &&r_fig) {
  if (this != &r_fig) {
    for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
      vertex[i] = std::move(r_fig.vertex[i]);
    }
  }
  return *this;
}

template <Scalar T>
bool Rectangle<T>::operator==(const Rectangle<T> &r_fig) const {
  for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
    if ((vertex[i]->x != r_fig.vertex[i]->x) ||
        (vertex[i]->y != r_fig.vertex[i]->y)) {
      return false;
    }
  }
  return true;
}

template <Scalar T> Rectangle<T>::operator double() const {
  double a = std::sqrt(std::pow(vertex[0]->x - vertex[1]->x, 2) +
                       std::pow(vertex[0]->y - vertex[1]->y, 2));
  double b = std::sqrt(std::pow(vertex[1]->x - vertex[2]->x, 2) +
                       std::pow(vertex[1]->y - vertex[2]->y, 2));
  return a * b;
}

template <Scalar T> Point<T> Rectangle<T>::getGeomitricCenter() const {
  return {.x = (vertex[0]->x + vertex[2]->x) / 2,
          .y = (vertex[0]->y + vertex[2]->y) / 2};
}

template <Scalar T> Rectangle<T>::~Rectangle() {}
