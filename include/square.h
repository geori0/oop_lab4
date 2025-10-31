#pragma once

#include <cmath>
#include <format>
#include <iostream>

#include "figure.h"

template <Scalar T> class Square final : public Figure<T> {
public:
  Square();
  static constexpr int VERTICIES_COUNT = 4;
  Square(std::unique_ptr<Point<T>> vertex[VERTICIES_COUNT]);
  Point<T> getGeomitricCenter() const override;
  void print(std::ostream &os) const override;
  void read(std::istream &is) override;
  std::shared_ptr<Figure<T>> clone() const override;
  Square(const Square &other);
  Square(Square &&other) noexcept;
  Square &operator=(Square &r_fig);
  Square &operator=(Square &&r_fig);
  bool operator==(const Square &r_fig) const;
  operator double() const override;
  ~Square();

private:
  std::unique_ptr<Point<T>> vertex[VERTICIES_COUNT];
};

template <Scalar T> Square<T>::Square() {
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    vertex[i] = std::make_unique<Point<T>>(Point<T>{0, 0});
  }
}

template <Scalar T>
Square<T>::Square(std::unique_ptr<Point<T>> vertices[VERTICIES_COUNT]) {
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    vertex[i] = std::make_unique<Point<T>>(*vertices[i]);
  }
}

template <Scalar T> std::shared_ptr<Figure<T>> Square<T>::clone() const {
  auto copy = std::make_shared<Square<T>>();
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    *copy->vertex[i] = *this->vertex[i];
  }
  return copy;
}

template <Scalar T> void Square<T>::print(std::ostream &os) const {
  os << "Квадрат:" << std::endl;
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    os << std::format("Вершина {}: ({}, {})", i + 1, vertex[i]->x,
                      vertex[i]->y);
  }
}

template <Scalar T> void Square<T>::read(std::istream &is) {
  for (int i = 0; i < VERTICIES_COUNT; ++i) {
    std::cout << "Введите координаты x и y квадрата через пробел: "
              << std::endl;
    is >> vertex[i]->x >> vertex[i]->y;
  }
}

template <Scalar T> Square<T>::Square(const Square<T> &other) {
  for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
    vertex[i] = std::make_unique<Point<T>>(*other.vertex[i]);
  }
}

template <Scalar T> Square<T>::Square(Square<T> &&other) noexcept {
  for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
    vertex[i] = std::move(other.vertex[i]);
  }
}

template <Scalar T> Square<T> &Square<T>::operator=(Square &r_fig) {
  if (this != &r_fig) {
    for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
      vertex[i] = std::make_unique<Point<T>>(*r_fig.vertex[i]);
    }
  }
  return *this;
}

template <Scalar T> Square<T> &Square<T>::operator=(Square<T> &&r_fig) {
  if (this != &r_fig) {
    for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
      vertex[i] = std::move(r_fig.vertex[i]);
    }
  }
  return *this;
}

template <Scalar T> bool Square<T>::operator==(const Square<T> &r_fig) const {
  for (size_t i = 0; i < VERTICIES_COUNT; ++i) {
    if ((vertex[i]->x != r_fig.vertex[i]->x) ||
        (vertex[i]->y != r_fig.vertex[i]->y)) {
      return false;
    }
  }
  return true;
}

template <Scalar T> Square<T>::operator double() const {
  double a = std::sqrt(std::pow(vertex[0]->x - vertex[1]->x, 2) +
                       std::pow(vertex[0]->y - vertex[1]->y, 2));
  return a * a;
}

template <Scalar T> Point<T> Square<T>::getGeomitricCenter() const {
  return {.x = (vertex[0]->x + vertex[2]->x) / 2,
          .y = (vertex[0]->y + vertex[2]->y) / 2};
}

template <Scalar T> Square<T>::~Square() {}
