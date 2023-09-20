#ifndef CPP2_S21_CONTAINERS_CONTAINERS_S21_STACK_H_
#define CPP2_S21_CONTAINERS_CONTAINERS_S21_STACK_H_

#include <cstddef>
#include <stdexcept>

namespace s21 {

template <class T>
class Stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  Stack() noexcept {
    stack_size_ = 0;
    root_ = nullptr;
  }
  Stack(std::initializer_list<value_type> const& list) noexcept : Stack() {
    for (const value_type& i : list) {
      push(i);
    }
  }
  Stack(const Stack& other) noexcept { this->CopyStack(other); }
  Stack(Stack&& other) noexcept { this->MoveStack((Stack &&) other); }
  Stack& operator=(const Stack& other) noexcept {
    this->CopyStack(other);
    return *this;
  }
  Stack& operator=(Stack&& other) noexcept {
    this->MoveStack((Stack &&) other);
    return *this;
  }
  ~Stack() noexcept {
    while (root_ != nullptr) {
      node* temp = root_;
      root_ = root_->next_;
      delete temp;
    }
    stack_size_ = 0;
  }

  void push(const_reference val) noexcept {
    node* temp = new node;
    temp->value_ = val;
    if (root_) {
      temp->next_ = root_;
      root_ = temp;
    } else {
      root_ = temp;
      root_->next_ = nullptr;
    }
    stack_size_++;
  }

  void pop() noexcept {
    if (root_) {
      node* temp = root_->next_;
      delete root_;
      root_ = temp;
      stack_size_--;
    }
  }

  void swap(Stack& other) noexcept {
    node* temp = root_;
    root_ = other.root_;
    other.root_ = temp;
    size_t temp_size = stack_size_;
    stack_size_ = other.stack_size_;
    other.stack_size_ = temp_size;
  }
  bool empty() const noexcept { return root_ == nullptr; }
  const_reference top() const {
    if (root_ == nullptr) {
      throw std::out_of_range("Empty stack");
    }
    return root_->value_;
  }
  size_type size() const noexcept { return stack_size_; }

  void CopyStack(const Stack& other) {
    stack_size_ = other.stack_size_;
    root_ = nullptr;
    if (other.root_ != nullptr) {
      root_ = new node{other.root_->value_, nullptr};
      node* stack = root_;
      node* stack_new = other.root_->next_;
      while (stack_new != nullptr) {
        stack->next_ = new node{stack_new->value_, nullptr};
        stack = stack->next_;
        stack_new = stack_new->next_;
      }
    }
  }
  void MoveStack(Stack&& other) {
    stack_size_ = other.stack_size_;
    root_ = other.root_;
    other.stack_size_ = 0;
    other.root_ = nullptr;
  }

 private:
  struct node {
    value_type value_;
    node* next_;
  };
  node* root_;
  size_type stack_size_;
};

}  // namespace s21

#endif  //  CPP2_S21_CONTAINERS_CONTAINERS_S21_STACK_H_