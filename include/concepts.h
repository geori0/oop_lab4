#pragma once

#include <type_traits>

template <class T>
concept Scalar = std::is_scalar_v<T>;

template <typename T>
concept PointerLike = requires(T t) { *t; };
