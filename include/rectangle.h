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

#include "rectangle.ipp"