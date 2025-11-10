template <class T>
Array<T>::Array()
    : size_array(0), capacity(2), data_array(std::make_shared<T[]>(2)) {}

template <class T>
Array<T>::Array(const Array &other)
    : size_array(other.size_array), capacity(other.capacity) {
  data_array = std::make_shared<T[]>(capacity);
  for (size_t i = 0; i < size_array; ++i) {
    if constexpr (PointerLike<T>) {
      data_array[i] = other.data_array[i]->clone();
    } else {
      data_array[i] = other.data_array[i];
    }
  }
}

template <class T>
Array<T>::Array(Array<T> &&other) noexcept
    : size_array(other.size_array), data_array(std::move(other.data_array)),
      capacity(other.capacity) {
  other.size_array = 0;
  other.capacity = 0;
}

template <class T> size_t Array<T>::getSize() const { return size_array; }

template <class T> void Array<T>::Resize(size_t new_size) {
  capacity = new_size;
  std::shared_ptr<T[]> new_data = std::make_shared<T[]>(new_size);
  for (size_t i = 0; i < size_array; ++i) {
    new_data[i] = std::move(data_array[i]);
  }
  data_array = std::move(new_data);
}

template <class T> T &Array<T>::operator[](size_t i) {
  if (i >= size_array) {
    throw std::out_of_range("Ошибка index out of range");
  }
  return data_array[i];
}

template <class T> const T &Array<T>::operator[](size_t i) const {
  if (i >= size_array) {
    throw std::out_of_range("Ошибка index out of range");
  }
  return data_array[i];
}

template <class T> void Array<T>::PushItem(T &t) {
  if (capacity == size_array) {
    Resize(capacity * 2);
  }
  data_array[size_array++] = t;
}

template <class T> void Array<T>::PushItem(T &&t) {
  if (capacity == size_array) {
    Resize(capacity * 2);
  }
  data_array[size_array++] = std::move(t);
}

template <class T> void Array<T>::PopItem() {
  if (!(size_array)) {
    throw std::out_of_range(" Ошибка Cannot pop from empty array");
  }
  --size_array;
}

template <class T> void Array<T>::PrintFigures() {
  if constexpr (PointerLike<T>) {
    for (size_t i = 0; i < size_array; ++i) {
      std::cout << *data_array[i] << std::endl;
      std::cout << "Центр: (" << data_array[i]->getGeomitricCenter().x << ", "
                << data_array[i]->getGeomitricCenter().y << ")" << std::endl;
      std::cout << "Площадь: " << double(*data_array[i]) << std::endl;
    }
  } else {
    for (size_t i = 0; i < size_array; ++i) {
      std::cout << data_array[i] << std::endl;
      std::cout << "Центр: (" << data_array[i].getGeomitricCenter().x << ", "
                << data_array[i].getGeomitricCenter().y << ")" << std::endl;
      std::cout << "Площадь: " << double(data_array[i]) << std::endl;
    }
  }
}

template <typename T> double Array<T>::TotalArea() {
  double res = 0.0;
  if constexpr (PointerLike<T>) {
    for (size_t i = 0; i < size_array; ++i)
      res += double(*data_array[i]);
  } else {
    for (size_t i = 0; i < size_array; ++i)
      res += double(data_array[i]);
  }
  return res;
}

template <class T> void Array<T>::DeleteFigure(size_t idx) {
  if (idx >= size_array) {
    throw std::out_of_range("Ошибка index out range");
  }
  for (size_t i = idx; i < size_array - 1; ++i) {
    data_array[i] = data_array[i + 1];
  }
  --size_array;
}

template <class T> Array<T>::~Array() noexcept {
  size_array = 0;
  capacity = 0;
}