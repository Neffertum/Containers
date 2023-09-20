#ifndef CPP2_S21_CONTAINERS_CONTAINERS_S21_SET_H_
#define CPP2_S21_CONTAINERS_CONTAINERS_S21_SET_H_

#include <vector>

#include "../containers/s21_btree.h"

namespace s21 {

template <class Key>
class Set {
 public:
  using key_type = Key;
  using value_type = key_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using rbtree_type = RedBlackTree<value_type>;
  using iterator = typename rbtree_type::iterator;
  using const_iterator = typename rbtree_type::const_iterator;

  Set() { rbtree_ = new rbtree_type; };

  Set(std::initializer_list<value_type> const &list) noexcept : Set() {
    for (const auto i : list) {
      insert(i);
    }
  }

  Set(const Set &other) { rbtree_ = new rbtree_type(*other.rbtree_); }

  Set(Set &&other) noexcept {
    rbtree_ = new rbtree_type(std::move(*other.rbtree_));
  }

  Set &operator=(const Set &other) {
    rbtree_ = new rbtree_type(*other.rbtree_);
    return *this;
  }

  Set &operator=(Set &&other) noexcept {
    rbtree_ = new rbtree_type(std::move(*other.rbtree_));
    return *this;
  }

  ~Set() {
    delete rbtree_;
    rbtree_ = nullptr;
  }

  bool empty() const noexcept { return rbtree_->empty(); };

  size_type size() const noexcept { return rbtree_->size(); };

  size_type max_size() const noexcept { return rbtree_->max_size(); };

  std::pair<iterator, bool> insert(const value_type &val) {
    return rbtree_->insert(val);
  }

  iterator find(const key_type &key) noexcept { return rbtree_->find(key); }

  bool contains(const key_type &key) const noexcept {
    bool flag = rbtree_->find(key) != rbtree_->end();
    return flag;
  }

  void erase(iterator iter) noexcept { rbtree_->erase(iter); }

  void clear() { rbtree_->clear(); }

  void swap(Set &other) noexcept { rbtree_->swap(*other.rbtree_); }

  void merge(Set &other) { rbtree_->merge(*other.rbtree_); };

  iterator begin() noexcept { return rbtree_->begin(); };
  iterator end() noexcept { return rbtree_->end(); };
  const_iterator cbegin() const noexcept { return rbtree_->begin(); };
  const_iterator cend() const noexcept { return rbtree_->end(); };

 private:
  rbtree_type *rbtree_;
};

};  // namespace s21

#endif  // CPP2_S21_CONTAINERS_CONTAINERS_S21_SET_H_