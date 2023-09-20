#ifndef CPP2_S21_CONTAINERS_CONTAINERS_S21_MAP_H_
#define CPP2_S21_CONTAINERS_CONTAINERS_S21_MAP_H_

#include <initializer_list>

#include "../containers/s21_btree.h"

namespace s21 {
template <class Key, class T>
class map {
 private:
  class Comparator;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using tree_type = RedBlackTree<value_type, Comparator>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;

  map() : body_(new tree_type{}) {}

  map(std::initializer_list<value_type> const& items) : map() {
    for (auto item : items) {
      insert(item);
    }
  }

  map(const map& m) : body_(new tree_type{*m.body_}) {}

  map(map&& m) : body_(new tree_type{std::move(*m.body_)}) {}

  ~map() {
    delete body_;
    body_ = nullptr;
  }

  map& operator=(map& m) {
    *body_ = *m.body_;
    return *this;
  }

  map& operator=(map&& m) {
    *body_ = std::move(*m.body_);
    return *this;
  }

  mapped_type& at(const Key& key) {
    value_type val(key, mapped_type{});
    iterator it = body_->find(val);
    if (it == end()) {
      throw std::out_of_range("s21::map::at: key not found");
    }
    return (*it).second;
  }

  const mapped_type& at(const Key& key) const {
    return const_cast<map<Key, T>*>(this)->at(key);
  }

  mapped_type& operator[](const Key& key) noexcept {
    value_type val(key, mapped_type{});
    iterator it = body_->find(val);

    if (it == end()) {
      std::pair<iterator, bool> result = body_->insert(val);
      return (*result.first).second;
    } else {
      return (*it).second;
    }
  }

  iterator find(const Key& key) noexcept {
    value_type val(key, mapped_type{});
    return body_->find(val);
  }
  iterator begin() noexcept { return body_->begin(); }
  iterator end() noexcept { return body_->end(); }
  const_iterator begin() const noexcept { return body_->begin(); }
  const_iterator end() const noexcept { return body_->end(); }

  bool empty() const noexcept { return body_->empty(); }

  size_type size() const noexcept { return body_->size(); }

  size_type max_size() const noexcept { return body_->max_size(); }

  void clear() noexcept { body_->clear(); }

  std::pair<iterator, bool> insert(const value_type& value) noexcept {
    return body_->insert(value);
  }

  std::pair<iterator, bool> insert(const Key& key,
                                   const mapped_type& obj) noexcept {
    return body_->insert(value_type{key, obj});
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key,
                                             const mapped_type& obj) noexcept {
    iterator result = body_->find(value_type{key, obj});

    if (result == end()) {
      return body_->insert(value_type{key, obj});
    }

    (*result).second = obj;
    return std::pair(result, false);
  }

  void erase(iterator pos) noexcept { body_->erase(pos); }

  void swap(map& other) noexcept { body_->swap(*other.body_); }
  void merge(map& other) noexcept { body_->merge(*other.body_); }
  bool contains(const Key& key) noexcept {
    return body_->contains({key, mapped_type{}});
  }

 private:
  class Comparator {
   public:
    bool operator()(const_reference value1,
                    const_reference value2) const noexcept {
      return value1.first < value2.first;
    }
  };

  tree_type* body_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_CONTAINERS_S21_MAP_H_