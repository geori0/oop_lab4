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

#include "triangle.ipp"