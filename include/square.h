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

#include "square.ipp"