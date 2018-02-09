#pragma once

#include <cassert>

namespace UtilityAlgorithms {

#define exch(a, b, t) \
  { (t) = (a); (a) = (b); (b) = (t); }

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


// ############### Sorting Functions #####################

/*
 * @brief Insertion sort.
 *
 * @type T The type of elements to be sorted. Must perform < operator.
 * @type UInt The unsigned integer type to be used as the array index.
 *
 * @param map The original indices of the elements in a
 * @param a The array of elements to be sorted.
 * @param n the size of the array a.
 */
template <typename T, typename UInt>
static void insertion_sort(UInt *map, T *a, const UInt n) {
  T t;    /* Temporary value. */
  UInt i, j, t_map; /* Loop indexes.    */
  
  /* Sort. */
  for (i = 0; i < (n - 1); i++)
  {
    for (j = i + 1; j < n; j++)
    {
      /* Swap. */
      if (a[j] < a[i])
      {
        exch(a[i], a[j], t);
        exch(map[i], map[j], t_map);
      }
    }
  }
}

template <typename T, typename UInt>
static void heap_sort(UInt *map, T *a, const UInt n) {
  T t;    /* Temporary value. */
  UInt i, j, t_map; /* Loop indexes.    */
  
  /* Sort. */
  for (i = 0; i < (n - 1); i++)
  {
    for (j = i + 1; j < n; j++)
    {
      /* Swap. */
      if (a[j] < a[i])
      {
        exch(a[i], a[j], t);
        exch(map[i], map[j], t_map);
      }
    }
  }
}

}