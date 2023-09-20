#ifndef CPP2_S21_CONTAINERS_CONTAINERS_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_CONTAINERS_S21_QUEUE_H_

#include <cstddef>
#include <stdexcept>

namespace s21 {
template <class T>
class Queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  Queue() noexcept : root_(nullptr), end_(nullptr) { queue_size_ = 0; }
  Queue(std::initializer_list<value_type> const& list) noexcept : Queue() {
    for (const auto& i : list) {
      push(i);
    }
  }
  Queue(const Queue& other) noexcept : Queue() { this->CopyQueue(other); }
  Queue(Queue&& other) noexcept { this->MoveQueue((Queue &&) other); }

  Queue& operator=(const Queue& other) noexcept {
    this->CopyQueue(other);
    return *this;
  }
  Queue& operator=(Queue&& other) noexcept {
    this->MoveQueue((Queue &&) other);
    return *this;
  }
  ~Queue() noexcept {
    while (root_) {
      node* elem = root_->next_;
      delete root_;
      root_ = elem;
    }
  }

  const_reference front() const {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return root_->value_;
  }
  const_reference back() const {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return end_->value_;
  }
  bool empty() const noexcept { return queue_size_ == 0; }
  size_type size() const noexcept { return queue_size_; }
  void push(const_reference element) noexcept {
    node* new_queue = new node{element, nullptr};
    if (empty()) {
      root_ = new_queue;
      end_ = new_queue;
    } else {
      end_->next_ = new_queue;
      end_ = new_queue;
    }
    queue_size_++;
  }
  void pop() noexcept {
    if (!empty()) {
      node* elem = root_;
      root_ = root_->next_;
      delete elem;
      if (root_ == nullptr) {
        end_ = nullptr;
      }
      queue_size_--;
    }
  }
  void swap(Queue& other) noexcept {
    node* root_elem = root_;
    node* end_elem = end_;
    size_type size_e = queue_size_;
    root_ = other.root_;
    end_ = other.end_;
    queue_size_ = other.queue_size_;
    other.root_ = root_elem;
    other.end_ = end_elem;
    other.queue_size_ = size_e;
  }
  void CopyQueue(const Queue& other) {
    node* elem = other.root_;
    while (elem) {
      push(elem->value_);
      elem = elem->next_;
    }
  }
  void MoveQueue(Queue&& other) {
    root_ = other.root_;
    end_ = other.end_;
    queue_size_ = other.queue_size_;
    other.root_ = nullptr;
    other.end_ = nullptr;
    other.queue_size_ = 0;
  }

 private:
  struct node {
    value_type value_;
    node* next_;
  };

  node* root_;
  node* end_;
  size_type queue_size_;
};
}  // namespace s21

#endif  //  CPP2_S21_CONTAINERS_CONTAINERS_S21_QUEUE_H_