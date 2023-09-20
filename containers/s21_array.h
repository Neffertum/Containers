#ifndef CPP2_S21_CONTAINERS_CONTAINERS_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_CONTAINERS_S21_ARRAY_H_

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

namespace s21 {
template <class T, std::size_t N>
class Array {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  // constructors and destructors

  explicit Array() {
    if (size_ > 0) {
      data_ = new value_type[size_]();
    }
  }

  Array(std::initializer_list<value_type> const &items) : Array() {
    if (items.size() > size_) {
      throw std::out_of_range(
          "size of initializer list is greater than size of Array");
    }
    std::copy(items.begin(), items.end(), begin());
  }

  Array(const Array &other)
      : data_(new value_type[other.size_]()), size_(other.size_) {
    std::copy(other.cbegin(), other.cend(), begin());
  }

  Array(Array &&other) noexcept {
    swap(*this, other);
    other.data_ = nullptr;
  }

  ~Array() {
    if (data_) {
      for (size_type i = 0U; i < size_; ++i) {
        data_[i].~value_type();
      }
      delete[] data_;
    }
  }

  // element access
  reference at(const size_type index) {
    if (index >= size_) {
      throw std::out_of_range("index out of range");
    }
    return data_[index];
  }

  const_reference at(const size_type index) const {
    if (index >= size_) {
      throw std::out_of_range("index out of range");
    }
    return data_[index];
  }

  reference operator[](const size_type index) noexcept { return data_[index]; }

  const_reference operator[](const size_type index) const noexcept {
    return data_[index];
  }

  reference front() noexcept { return data_[0]; }

  const_reference front() const noexcept { return data_[0]; }

  reference back() noexcept { return data_[size_ - 1]; }

  const_reference back() const noexcept { return data_[size_ - 1]; }

  pointer data() noexcept { return data_; }

  const_pointer data() const noexcept { return data_; }

  // iterators
  iterator begin() noexcept { return iterator(data_); }

  iterator end() noexcept { return iterator(data_ + size_); }

  const_iterator cbegin() const noexcept { return const_iterator(data_); }

  const_iterator cend() const noexcept { return const_iterator(data_ + size_); }

  reverse_iterator rbegin() noexcept { return reverse_iterator(data_ + size_); }

  reverse_iterator rend() noexcept { return reverse_iterator(data_); }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(data_ + size_);
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(data_);
  }

  // capacity
  bool empty() const noexcept { return size_ == 0U; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept { return size_; }

  // operations
  void fill(const value_type &value) noexcept {
    std::fill(begin(), end(), value);
  }

  friend void swap(Array &lhs, Array &rhs) noexcept {
    std::swap(rhs.size_, lhs.size_);
    std::swap(rhs.data_, lhs.data_);
  }

  // operators
  Array &operator=(const Array &other) {
    if (this != &other) {
      if (data_) delete[] data_;
      size_ = other.size_;
      data_ = new value_type[size_]();
      std::copy(other.cbegin(), other.cend(), begin());
    }
    return *this;
  }

  Array &operator=(Array &&other) {
    if (this != &other) {
      if (data_) delete[] data_;
      swap(*this, other);
      other.data_ = nullptr;
    }
    return *this;
  }

  bool operator==(const Array &other) const noexcept {
    return std::equal(cbegin(), cend(), other.cbegin());
  }

  bool operator!=(const Array &other) const noexcept {
    return !(*this == other);
  }

  bool operator<(const Array &other) const noexcept {
    return std::lexicographical_compare(cbegin(), cend(), other.cbegin(),
                                        other.cend());
  }

  bool operator<=(const Array &other) const noexcept {
    return !(other < *this);
  }

  bool operator>(const Array &other) const noexcept { return other < *this; }

  bool operator>=(const Array &other) const noexcept {
    return !(*this < other);
  }

 private:
  pointer data_ = nullptr;
  size_type size_ = N;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_CONTAINERS_S21_ARRAY_H_
