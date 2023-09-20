#ifndef CPP2_S21_CONTAINERS_CONTAINERS_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_CONTAINERS_S21_VECTOR_H_

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>
namespace s21 {

template <class T>
class Vector {
 public:
  // types
  using value_type = T;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  // constructors and destructors
  explicit Vector() : arr_(nullptr), size_(0U), capacity_(0U) {}

  explicit Vector(size_type n)
      : arr_(n ? new value_type[n]() : nullptr), size_(n), capacity_(n) {
    if (arr_) std::uninitialized_default_construct(begin(), end());
  }

  explicit Vector(size_type n, const_reference value)
      : arr_(n ? new value_type[n] : nullptr), size_(n), capacity_(n) {
    if (arr_) std::uninitialized_fill(begin(), end(), value);
  }

  Vector(std::initializer_list<value_type> const &items)
      : arr_(items.size() ? new value_type[items.size()] : nullptr),
        size_(items.size()),
        capacity_(items.size()) {
    std::uninitialized_copy(items.begin(), items.end(), begin());
  }

  Vector(const Vector &other) : size_(other.size_), capacity_(other.capacity_) {
    arr_ = (capacity_ ? new value_type[capacity_]() : nullptr);
    std::uninitialized_copy(other.cbegin(), other.cend(), begin());
  }

  Vector(Vector &&other) noexcept : arr_(nullptr), size_(0U), capacity_(0U) {
    swap(*this, other);
  }

  ~Vector() {
    if (arr_) {
      for (size_type i = 0U; i < size_; ++i) {
        arr_[i].~value_type();
      }
      delete[] arr_;
    }
  }

  // accessors and mutators

  reference at(size_type index) {
    if (index >= size_) {
      throw std::out_of_range("index out of range");
    }
    return arr_[index];
  }
  const_reference at(size_type index) const {
    if (index >= size_) {
      throw std::out_of_range("index out of range");
    }
    return arr_[index];
  }
  reference operator[](size_type pos) noexcept { return arr_[pos]; }
  const_reference operator[](size_type pos) const noexcept { return arr_[pos]; }
  reference front() noexcept { return arr_[0]; }
  const_reference front() const noexcept { return arr_[0]; }
  reference back() noexcept { return arr_[size_ - 1]; }
  const_reference back() const noexcept { return arr_[size_ - 1]; }
  pointer data() noexcept { return arr_; }
  const_pointer data() const noexcept { return arr_; }

  bool empty() const noexcept { return size_ == 0U; }
  size_type size() const noexcept { return size_; }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }
  void reserve(size_type new_capacity) {
    if (new_capacity <= capacity_) return;
    if (new_capacity > max_size()) {
      throw std::length_error("value exceeds maximum size");
    }
    pointer new_arr = new value_type[new_capacity]();
    std::move(begin(), end(), new_arr);
    if (arr_ != nullptr) delete[] arr_;
    arr_ = new_arr;
    capacity_ = new_capacity;
  }
  size_type capacity() const noexcept { return capacity_; }
  void shrink_to_fit() {
    if (size_ == capacity_) return;
    if (size_ == 0U) {
      delete[] arr_;
      arr_ = nullptr;
      capacity_ = 0U;
    } else {
      pointer new_arr = new value_type[size_];
      std::move(begin(), end(), new_arr);
      delete[] arr_;
      arr_ = new_arr;
      capacity_ = size_;
    }
  }

  void clear() noexcept { size_ = 0U; }

  iterator insert(iterator pos, const_reference value) {
    size_type diff = pos - begin();
    if (size_ == capacity_) {
      reserve(capacity_ == 0U ? 1U : capacity_ * 2U);
      pos = begin() + diff;
    }
    if (size_ != 0U) {
      *end() = std::move(*(end() - 1));
    }
    std::rotate(pos, end(), end() + 1);
    *pos = value;
    ++size_;
    return pos;
  }

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    iterator it_current{const_cast<value_type *>(pos)};
    for (auto value : {std::forward<Args>(args)...}) {
      it_current = insert(it_current, std::move(value));
      ++it_current;
    }
    return --it_current;
  }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    for (auto value : {std::forward<Args>(args)...}) {
      push_back(std::move(value));
    }
  }

  void erase(iterator pos) {
    if (pos == end() - 1) {
      --size_;
    } else {
      std::rotate(pos, pos + 1, end());
      --size_;
    }
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve(capacity_ == 0U ? 1U : capacity_ * 2U);
    }
    *(end()) = value;
    ++size_;
  }

  void pop_back() noexcept { --size_; }

  void resize(const size_type count) {
    if (capacity_ < count) {
      reserve(capacity_ == 0U ? 1U : capacity_ * 2U);
      if (capacity_ < count) reserve(count);
    }
    if (size_ < count) {
      std::uninitialized_default_construct(begin() + size_, begin() + count);
    }
    size_ = count;
  }

  void resize(const size_type count, const_reference value) {
    if (capacity_ < count) {
      reserve(capacity_ == 0U ? 1U : capacity_ * 2U);
      if (capacity_ < count) reserve(count);
    }
    if (size_ < count) {
      std::fill_n(end(), count - size_, value);
    }
    size_ = count;
  }

  friend void swap(Vector &lhs, Vector &rhs) noexcept {
    std::swap(lhs.arr_, rhs.arr_);
    std::swap(lhs.size_, rhs.size_);
    std::swap(lhs.capacity_, rhs.capacity_);
  }

  // iterators
  iterator begin() noexcept { return iterator(arr_); }
  iterator end() noexcept { return iterator(arr_ + size_); }
  const_iterator cbegin() const noexcept { return const_iterator(arr_); }
  const_iterator cend() const noexcept { return const_iterator(arr_ + size_); }

  reverse_iterator rbegin() noexcept { return reverse_iterator(arr_ + size_); }
  reverse_iterator rend() noexcept { return reverse_iterator(arr_); }
  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(arr_ + size_);
  }
  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(arr_);
  }

  // operators
  bool operator==(const Vector &rhs) const {
    return size_ == rhs.size_ && std::equal(cbegin(), cend(), rhs.cbegin());
  }

  bool operator!=(const Vector &rhs) const { return !(*this == rhs); }

  bool operator<(const Vector &rhs) const {
    return std::lexicographical_compare(cbegin(), cend(), rhs.cbegin(),
                                        rhs.cend());
  }

  bool operator<=(const Vector &rhs) const { return !(rhs < *this); }

  bool operator>(const Vector &rhs) const { return rhs < *this; }

  bool operator>=(const Vector &rhs) const { return !(*this < rhs); }

  Vector &operator=(const Vector &other) {
    if (this != &other) {
      if (capacity_ < other.size_) {
        delete[] arr_;
        arr_ = new value_type[other.size_];
        capacity_ = other.size_;
      }
      size_ = other.size_;
      std::copy(other.cbegin(), other.cend(), begin());
    }
    return *this;
  }

  Vector &operator=(Vector &&other) noexcept {
    if (this != &other) {
      delete[] arr_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      arr_ = other.arr_;
      other.arr_ = nullptr;
      other.size_ = other.capacity_ = 0U;
    }
    return *this;
  }

 private:
  value_type *arr_;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_CONTAINERS_S21_VECTOR_H_
