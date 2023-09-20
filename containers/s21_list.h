#ifndef CPP2_S21_CONTAINERS_CONTAINERS_S21_LIST_H_
#define CPP2_S21_CONTAINERS_CONTAINERS_S21_LIST_H_

#include <initializer_list>
#include <limits>

namespace s21 {
template <class T>
class list {
 private:
  class ListNode;

 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = list<value_type>::ListIterator;
  using const_iterator = list<value_type>::ListConstIterator;
  using size_type = std::size_t;
  using node_type = ListNode;

  list() : head_(new node_type{}), size_(size_type{}) {}

  explicit list(size_type n) : list() {
    for (; n > 0; n--, push_back(value_type{}))
      ;
  }

  list(std::initializer_list<value_type> const &items) : list() {
    for (auto item : items) {
      push_back(item);
    }
  }

  list(const list &l) : list() {
    for (auto it = l.begin(); it != l.end(); ++it) {
      push_back(*it);
    }
  }

  list(list &&l) : list() { splice(begin(), l); }

  ~list() {
    clear();
    delete head_;
    head_ = nullptr;
  }

  list &operator=(list &&l) {
    if (this != &l) {
      clear();
      splice(begin(), l);
    }
    return *this;
  }

  list &operator=(const list &other) {
    if (this != &other) {
      iterator tbegin = begin(), tend = end();
      const_iterator obegin = other.begin(), oend = other.end();

      while (tbegin != tend && obegin != oend) {
        *tbegin = *obegin;
        ++tbegin;
        ++obegin;
      }

      iterator tmp = tbegin;
      while (tbegin != tend) {
        ++tbegin;
        erase(tmp);
        tmp = tbegin;
      }

      while (obegin != oend) {
        push_back(*obegin);
        ++obegin;
      }
    }

    return *this;
  }

  reference front() noexcept { return *begin(); }

  reference back() noexcept { return *(--end()); }

  const_reference front() const noexcept { return *begin(); }
  const_reference back() const noexcept { return *(--end()); }

  iterator begin() noexcept { return iterator(head_->next_); }
  iterator end() noexcept { return iterator(head_); }

  const_iterator begin() const noexcept { return const_iterator(head_->next_); }
  const_iterator end() const noexcept { return const_iterator(head_); }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(node_type);
  }

  void clear() noexcept {
    while (size_) {
      erase(begin());
    }
  }
  iterator insert(iterator pos, const_reference value) {
    node_type *new_node = new node_type(value);

    pos.node_->BindBeforeCurrent(new_node);
    ++size_;

    return iterator(new_node);
  }
  void erase(iterator pos) noexcept {
    if (pos.node_ != head_) {
      pos.node_->Unbind();
      delete pos.node_;
      --size_;
    }
  }
  void push_back(const_reference value) { insert(this->end(), value); }
  void pop_back() noexcept { erase(--end()); }
  void push_front(const_reference value) { insert(this->begin(), value); }
  void pop_front() noexcept { erase(begin()); }

  void swap(list &other) noexcept {
    std::swap(head_, other.head_);
    std::swap(size_, other.size_);
  }
  void merge(list &other) noexcept {
    if (this != &other) {
      ListIterator this_begin = begin(), this_end = end(),
                   other_begin = other.begin(), other_end = other.end();
      while (this_begin != this_end && other_begin != other_end) {
        if (*other_begin < *this_begin) {
          node_type *tmp = other_begin.node_;
          ++other_begin;
          tmp->Unbind();
          --other.size_;
          this_begin.node_->BindBeforeCurrent(tmp);
          ++size_;
        } else {
          ++this_begin;
        }
      }
    }
    splice(end(), other);
    other.size_ = 0;
  }
  void splice(const_iterator pos, list &other) noexcept {
    if (!other.empty()) {
      iterator curpos{static_cast<node_type *>(pos.node_)};
      iterator pre_pos = curpos - 1, olast = --other.end(),
               ofirst = other.begin();
      olast.node_->next_ = curpos.node_;
      curpos.node_->prev_ = olast.node_;

      pre_pos.node_->next_ = ofirst.node_;
      ofirst.node_->prev_ = pre_pos.node_;

      size_ += other.size_;
      other.size_ = 0;
      other.head_->next_ = other.head_;
      other.head_->prev_ = other.head_;
    }
  }
  void reverse() noexcept {
    iterator begin_it = begin(), end_it = end();
    while (begin_it != end_it) {
      std::swap(begin_it.node_->prev_, begin_it.node_->next_);
      --begin_it;
    }
    std::swap(head_->prev_, head_->next_);
  }
  void unique() noexcept {
    iterator begin_it = begin(), end_it = end(), begin_plus_it = ++begin();
    while (begin_plus_it != end_it) {
      if (*begin_it == *begin_plus_it) {
        erase(begin_plus_it);
        begin_plus_it = begin_it + 1;
      } else {
        ++begin_it;
        ++begin_plus_it;
      }
    }
  }
  void sort() noexcept {
    for (iterator it_i = ++begin(); it_i != end(); ++it_i) {
      value_type value = *it_i;
      iterator it_j = it_i - 1;

      for (; it_j.node_ != nullptr && *it_j > value; --it_j) {
        *(it_j + 1) = *it_j;
      }
      *(it_j + 1) = value;
    }
  }

  class ListIterator {
   public:
    friend void list::sort() noexcept;
    friend list::iterator list::insert(iterator pos, const_reference value);
    friend void list::erase(iterator pos) noexcept;
    friend void list::clear() noexcept;
    friend void list::splice(const_iterator pos, list &other) noexcept;
    friend void list::reverse() noexcept;
    friend void list::merge(list &other) noexcept;
    friend class ListConstIterator;

    ListIterator() : node_(nullptr) {}
    explicit ListIterator(node_type *node) : node_(node) {}

    iterator &operator++() noexcept {
      node_ = node_->next_;
      return *this;
    }
    iterator &operator--() noexcept {
      node_ = node_->prev_;
      return *this;
    }
    iterator operator++(int) noexcept {
      iterator tmp{node_};
      node_ = node_->next_;
      return tmp;
    }
    iterator operator--(int) noexcept {
      iterator tmp{node_};
      node_ = node_->prev_;
      return tmp;
    }
    bool operator==(const iterator &other) const noexcept {
      return node_ == other.node_;
    }
    bool operator!=(const iterator &other) const noexcept {
      return node_ != other.node_;
    }
    iterator operator+(size_type n) {
      iterator tmp{node_};
      for (; n > 0; n--) {
        ++tmp;
      }
      return tmp;
    }
    iterator operator-(size_type n) {
      iterator tmp{node_};
      for (; n > 0; n--) {
        --tmp;
      }
      return tmp;
    }
    reference operator*() noexcept { return node_->data_; }

   private:
    node_type *node_;
  };

  class ListConstIterator {
   public:
    friend void list::splice(const_iterator pos, list &other) noexcept;
    ListConstIterator() : node_(nullptr) {}
    ListConstIterator(const ListIterator &it) : node_(it.node_) {}
    ListConstIterator(node_type *node) : node_(node) {}
    const_iterator &operator++() noexcept {
      node_ = node_->next_;
      return *this;
    }
    const_iterator &operator--() noexcept {
      node_ = node_->prev_;
      return *this;
    }
    const_iterator operator++(int) noexcept {
      const_iterator tmp{node_};
      node_ = node_->next_;
      return tmp;
    }
    const_iterator operator--(int) noexcept {
      const_iterator tmp{node_};
      node_ = node_->prev_;
      return tmp;
    }
    bool operator==(const const_iterator &other) const noexcept {
      return node_ == other.node_;
    }
    bool operator!=(const const_iterator &other) const noexcept {
      return node_ != other.node_;
    }
    const_iterator operator+(size_type n) noexcept {
      const_iterator tmp{node_};
      for (; n > 0; n--) {
        ++tmp;
      }
      return tmp;
    }
    const_iterator operator-(size_type n) noexcept {
      const_iterator tmp{node_};
      for (; n > 0; n--) {
        --tmp;
      }
      return tmp;
    }
    const_reference operator*() const noexcept { return node_->data_; }

   private:
    node_type *node_;
  };

 private:
  class ListNode {
   public:
    ListNode() : next_(this), prev_(this), data_(value_type{}) {}
    explicit ListNode(const_reference value)
        : next_(nullptr), prev_(nullptr), data_(value) {}

    void BindBeforeCurrent(ListNode *new_node) noexcept {
      new_node->next_ = this;
      new_node->prev_ = prev_;
      prev_->next_ = new_node;
      prev_ = new_node;
    }

    void Unbind() noexcept {
      prev_->next_ = next_;
      next_->prev_ = prev_;
      next_ = nullptr;
      prev_ = nullptr;
    }

    ListNode *next_;
    ListNode *prev_;
    value_type data_;
  };

  ListNode *head_;
  size_type size_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_CONTAINERS_S21_LIST_H_