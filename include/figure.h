#pragma once

#include <memory>
#include <ostream>

#include "point.h"

template <Scalar T> class Figure {
public:
  Figure() = default;
  virtual std::shared_ptr<Figure<T>> clone() const = 0;
  virtual Point<T> getGeomitricCenter() const = 0;
  virtual operator double() const = 0;
  virtual void print(std::ostream &os) const = 0;
  virtual void read(std::istream &is) = 0;
  virtual ~Figure() = default;
};

template <Scalar T>
inline std::ostream &operator<<(std::ostream &os, const Figure<T> &fig) {
  fig.print(os);
  return os;
}

template <Scalar T>
inline std::istream &operator>>(std::istream &is, Figure<T> &fig) {
  fig.read(is);
  return is;
}