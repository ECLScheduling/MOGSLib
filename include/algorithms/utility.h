#pragma once

#include <cassert>

namespace UtilityAlgorithms {

/**
 * @brief A function that returns an array with the cummulative sum of the elements.
 *
 * @type T The type of elements to be sorted. Must perform < operator.
 * @type UInt The unsigned integer type to be used as the array index.
 *
 * @param a The array of elements to be compute the sum.
 * @param size The size of the array.
 */
template<typename T, typename UInt>
T *compute_cummulativesum(const T* a, const UInt size) {
  UInt i;
  T *sum = new T[size];

  assert(sum != nullptr);
  sum[0] = 0;

  for (i = 1; i < size; ++i)
    sum[i] = sum[i - 1] + a[i - 1];

  return (sum);
}

/** Swap two values by reference **/
template<typename T>
void swap(T &a, T &b) {
  const T t = a;
  a = b;
  b = t;
} 

// ############### Sorting Functions #####################

/** @brief Structure to auxiliate the comparison in the sort algorithms **/
template<typename T, bool ascending_order>
struct Compare {
  static bool value(T &a, T &b) {
    return a < b;
  }
};

/** @brief Structure specialization to auxiliate the comparison in the sort algorithms **/
template<typename T>
struct Compare<T, false> {
  static bool value(T &a, T &b) {
    return a > b;
  }
};

/*
 * @brief Insertion sort.
 *
 * @type T The type of elements to be sorted. Must perform < operator.
 * @type UInt The unsigned integer type to be used as the array index.
 * @type ascending_order A boolean to choose whether the algorithm should increasing in ascending order or not. This value defaults to decreasing order.
 *
 * @param map The original indices of the elements in a.
 * @param a The array of elements to be sorted.
 * @param n the size of the array a.
 */
template <typename T, typename UInt, bool ascending_order = true>
void insertion_sort(UInt *map, T *a, const UInt n) {
  UInt i, j; /* Loop indexes.    */
  
  /* Sort. */
  for (i = 0; i < (n - 1); i++)
  {
    for (j = i + 1; j < n; j++)
    {
      /* Swap. */
      if (Compare<T, ascending_order>::value(a[j], a[i]))
      {
        swap<T>(a[i], a[j]);
        swap<UInt>(map[i], map[j]);
      }
    }
  }
}

}