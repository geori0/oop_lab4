#pragma once

#include <iostream>

#include "figure.h"

template <class T> class Array {
public:
  Array();
  Array(const Array &other);
  Array(Array &&other) noexcept;
  ~Array() noexcept;

  void Resize(size_t new_size);
  T &operator[](size_t i);
  const T &operator[](size_t i) const;
  void PushItem(T &t);
  void PushItem(T &&t);
  void PopItem();
  size_t getSize() const;
  double TotalArea();
  void PrintFigures();
  void DeleteFigure(size_t i);

private:
  size_t size_array;
  std::shared_ptr<T[]> data_array;
  size_t capacity;
};

#include "array.ipp"