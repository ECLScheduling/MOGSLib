#pragma once

#include <system/traits.h>
#include <vector>
#include <array>

namespace Structures {

template<typename ElementType>
using SparseMatrixWrapperType = std::vector<ElementType>;

/**
 * @brief A structure that represents the components and methods of a dynamic-sized sparse matrix row.
 * @details This structure serves the purpose of binding a common syntax to access the elements of sparse matrices.
 * @type ElementType The type of element contained in the sparse matrix.
 * @type Wrapper The container type that holds the element types. This type must contain a size, push_back, erase and operator[] method.
 */
template<typename ElementType, typename Wrapper = SparseMatrixWrapperType<ElementType> >
struct SparseMatrixRow {
  using value_type = ElementType;
  
  Wrapper elements;

  typename Wrapper::reference operator [](const typename Wrapper::size_type n) {
    return elements[n];
  }

  decltype(elements.size()) size() const {
    return elements.size();
  }

  void push(ElementType e) {
    elements.push_back(e);
  }

  void remove(typename Wrapper::size_type pos) {
    elements.erase(elements.begin() + pos);
  }
};

/**
 * @brief A structure that represents the components and methods of a fixed-sized sparse matrix row.
 * @details This structure serves the purpose of binding a common syntax to access the elements of sparse matrices.
 * @type ElementType The type of element contained in the sparse matrix.
 * @type Wrapper The container type that holds the element types. This type must contain a size and operator[] method.
 */
template<typename ElementType, std::size_t _size>
struct SparseMatrixRowStatic {
  using value_type = ElementType;
  using Wrapper = std::array<ElementType, _size>;
  
  Wrapper elements;

  typename Wrapper::reference operator [](const typename Wrapper::size_type n) {
    return elements[n];
  }

  decltype(elements.size()) size() const {
    return elements.size();
  }
};


/**
 * @brief A sparse matrix with a fixed size of rows.
 */
template<typename ElementType, std::size_t _size, typename Wrapper = SparseMatrixWrapperType<ElementType> >
using SparseMatrix = SparseMatrixRowStatic<SparseMatrixRow<ElementType, Wrapper>, _size>;

/**
 * @brief A sparse matrix with a dynamic size of rows.
 */
template<typename ElementType, typename ColWrapper = SparseMatrixWrapperType<ElementType>, typename RowWrapper = SparseMatrixWrapperType<SparseMatrixRow<ElementType, ColWrapper> > >
using DynamicSparseMatrix = SparseMatrixRow<SparseMatrixRow<ElementType, ColWrapper>, RowWrapper>;

}