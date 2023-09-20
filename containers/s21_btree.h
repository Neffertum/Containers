#ifndef CPP2_S21_CONTAINERS_CONTAINERS_S21_BTREE_H_
#define CPP2_S21_CONTAINERS_CONTAINERS_S21_BTREE_H_

#include <functional>
#include <limits>

namespace s21 {

template <class Key, class Comparator = std::less<Key>>
class RedBlackTree {
 public:
  class RedBlackTreeNode;
  class RedBlackTreeIterator;
  class RedBlackTreeConstIterator;
  friend class RedBlackTreeNode;

  using key_type = Key;
  using reference = key_type&;
  using const_reference = const key_type&;
  using iterator = RedBlackTreeIterator;
  using const_iterator = RedBlackTreeConstIterator;
  using node_type = RedBlackTreeNode;
  using size_type = std::size_t;
  using tree_type = RedBlackTree<key_type, Comparator>;

  RedBlackTree()
      : head_(nullptr), nill_leaf_(new node_type{}), size_(size_type{}) {
    nill_leaf_->black_ = true;
  }

  RedBlackTree(const tree_type& other) noexcept : RedBlackTree() {
    CopyTree(other);
  }

  RedBlackTree(tree_type&& other) noexcept : RedBlackTree() { swap(other); }

  tree_type& operator=(const tree_type& other) noexcept {
    if (this != &other) {
      CopyTree(other);
    }
    return *this;
  }

  tree_type& operator=(tree_type&& other) noexcept {
    clear();
    swap(other);
    return *this;
  }

  ~RedBlackTree() {
    clear();
    delete nill_leaf_;
    head_ = nullptr;
    nill_leaf_ = nullptr;
  }

  void clear() {
    DeleteBranch(head_);
    size_ = 0;
    head_ = nullptr;
  }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return ((std::numeric_limits<size_type>::max() / 2) - sizeof(tree_type) -
            sizeof(node_type)) /
           sizeof(node_type);
  }

  std::pair<iterator, bool> insert(const_reference value) {
    node_type* new_node = new node_type{value};
    return InsertNode(new_node);
  }

  std::pair<iterator, bool> InsertNode(node_type* new_node) noexcept {
    node_type *node = head_, *parent = nullptr;
    while (node != nullptr && node->parent_ != nullptr) {
      parent = node;
      if (is_less_(new_node->key_, node->key_)) {
        // new_node < node
        node = node->left_;
      } else {
        // new_node >= node
        if (is_less_(node->key_, new_node->key_)) {
          // new_node > node
          node = node->right_;
        } else {
          // new_node == node
          return {iterator(node), false};
        }
      }
    }

    if (parent == nullptr) {
      head_ = new_node;
      head_->black_ = true;
      head_->parent_ = nill_leaf_;
    } else {
      new_node->parent_ = parent;
      if (is_less_(new_node->key_, parent->key_)) {
        // new_node < parent
        parent->left_ = new_node;
        new_node->left_child_ = true;
      } else {
        // new_node > parent
        parent->right_ = new_node;
        new_node->left_child_ = false;
      }
    }
    ++size_;
    new_node->left_ = nill_leaf_;
    new_node->right_ = nill_leaf_;

    if (nill_leaf_->right_ == nullptr) {
      nill_leaf_->right_ = new_node;
    } else {
      if (is_less_(nill_leaf_->right_->key_, new_node->key_))
        nill_leaf_->right_ = new_node;
    }
    if (nill_leaf_->left_ == nullptr) {
      nill_leaf_->left_ = new_node;
    } else {
      if (is_less_(new_node->key_, nill_leaf_->left_->key_))
        nill_leaf_->left_ = new_node;
    }

    CheckColor(new_node);
    return {iterator(new_node), true};
  }

  iterator begin() noexcept { return iterator(MostLeft(head_)); }

  iterator end() noexcept { return iterator(nill_leaf_); }

  node_type* MostLeft(node_type* pos) noexcept {
    if (pos == nullptr) return nill_leaf_;
    node_type* min = pos;
    while (min->left_ != nill_leaf_) {
      min = min->left_;
    }
    return min;
  }

  node_type* MostRight(node_type* pos) noexcept {
    if (pos == nullptr) return nill_leaf_;
    node_type* max = pos;
    while (max->right_ != nill_leaf_) {
      max = max->right_;
    }
    return max;
  }

  /*
  return iterator on nill if not found
  else returns iterator on desired node
  */
  iterator find(const_reference key) const noexcept {
    if (head_ == nullptr) return iterator{nill_leaf_};
    node_type* cur = head_;
    while (cur) {
      if (cur == nill_leaf_) {
        break;
      }
      if (is_less_(key, cur->key_)) {
        // cur > key
        cur = cur->left_;
      } else {
        // cur <= key
        if (is_less_(cur->key_, key)) {
          cur = cur->right_;
          // cur < key
        } else {
          break;
        }
      }
    }
    return iterator(cur);
  }

  void swap(tree_type& other) noexcept {
    std::swap(other.head_, head_);
    std::swap(other.size_, size_);
    std::swap(other.is_less_, is_less_);
    std::swap(other.nill_leaf_, nill_leaf_);
  }

  void merge(tree_type& other) noexcept {
    if (this != &other) {
      iterator other_it = other.begin();
      iterator other_end = other.end();
      iterator tmp = other_it;
      node_type* moving_node = nullptr;
      while (other_it != other_end) {
        if (!contains(*other_it)) {
          tmp = other_it;
          ++tmp;
          moving_node = other.ExtractNode(other_it.node_);
          InsertNode(moving_node);
          other_it = tmp;
        } else {
          ++other_it;
        }
      }
    }
  }

  bool contains(const_reference key) const noexcept {
    return ((find(key).node_) != nill_leaf_);
  }

  void CopyTree(const tree_type& o) {
    clear();
    size_ = o.size_;
    is_less_ = o.is_less_;
    RecursiveCopy(o.head_, nill_leaf_);
  }

  node_type* RecursiveCopy(node_type* node, node_type* parent) {
    if (node == nullptr) return nullptr;

    node_type* new_node = new node_type{node};
    new_node->parent_ = parent;

    if (node->parent_->parent_ == nullptr) {
      head_ = new_node;
    }

    if (node->left_->parent_ != nullptr) {
      new_node->left_ = RecursiveCopy(node->left_, new_node);
    } else {
      new_node->left_ = nill_leaf_;
    }

    if (node->right_->parent_ != nullptr) {
      new_node->right_ = RecursiveCopy(node->right_, new_node);
    } else {
      new_node->right_ = nill_leaf_;
    }
    return new_node;
  }

  void erase(iterator pos) noexcept {
    node_type* extracted_node = ExtractNode(pos.node_);
    delete extracted_node;
  }

  // инструкция, по которой написан код:
  // https://habr.com/ru/companies/otus/articles/521034/
  node_type* ExtractNode(node_type* pos) noexcept {
    if (pos == nill_leaf_->left_) {
      nill_leaf_->left_ = pos->parent_;
    }
    if (pos == nill_leaf_->right_) {
      nill_leaf_->right_ = pos->parent_;
    }
    if (pos == nill_leaf_) {
      return nullptr;
    }
    node_type* exchanging_node = nullptr;

    // красный или черный члены с двумя детьми
    if (pos->left_ != nill_leaf_ && pos->right_ != nill_leaf_) {
      exchanging_node = MostLeft(pos->right_);
      if (exchanging_node->left_->parent_ != nullptr ||
          exchanging_node->right_->parent_ != nullptr) {
        exchanging_node = MostRight(pos->left_);
      }
      SwapNodesValues(pos, exchanging_node);
    }

    // черный член с одним ребенком
    if (pos->black_ == true &&
        (pos->left_ == nill_leaf_) ^ (pos->right_ == nill_leaf_)) {
      exchanging_node = (pos->right_ == nill_leaf_ ? pos->left_ : pos->right_);
      SwapNodesValues(pos, exchanging_node);
    }

    // черный бездетный член
    if (pos->black_ == true && pos->left_ == nill_leaf_ &&
        pos->right_ == nill_leaf_) {
      BalanceBlackChildFreeNode(pos);
    }

    // выдергивание члена
    if (pos != head_) {
      if (pos->left_child_) {
        pos->parent_->left_ = nill_leaf_;
      } else {
        pos->parent_->right_ = nill_leaf_;
      }
    } else {
      head_ = nullptr;
    }
    --size_;
    pos->MakeDefault();
    return pos;
  }

  void BalanceBlackChildFreeNode(node_type* node) noexcept {
    if (node == head_) {
      return;
    }

    node_type *parent = node->parent_,
              *sibling = node->left_child_ ? parent->right_ : parent->left_;

    // родитель красный, другой ребёнок чёрный с чёрными внуками
    if (parent->black_ == false && sibling != nill_leaf_ &&
        sibling->left_->black_ == true && sibling->right_->black_ == true) {
      sibling->black_ = false;
      parent->black_ = true;
    }

    // родитель красный, левый ребёнок чёрный с левым красным внуком.
    if (parent->black_ == false && sibling->black_) {
      if (sibling->left_child_ == true && sibling->left_->black_ == false) {
        // брат слева
        RightRotation(parent);
        parent->black_ = true;
        sibling->black_ = false;
      }
      if (sibling->left_child_ == false && sibling->right_->black_ == false) {
        // брат справа
        LeftRotation(parent);
        parent->black_ = true;
        sibling->black_ = false;
      }
    }

    // родитель чёрный, левый сын красный, у правого внука чёрные правнуки
    if (parent->black_ == true && sibling->black_ == false &&
        sibling->left_->black_ == true && sibling->right_->black_ == true) {
      if (sibling->left_child_) {
        if (sibling->right_ != nill_leaf_ && sibling->right_->right_->black_ &&
            sibling->right_->left_->black_) {
          sibling->black_ = true;
          sibling->right_->black_ = false;
          RightRotation(parent);
        }
      } else {
        if (sibling->left_ != nill_leaf_ && sibling->left_->right_->black_ &&
            sibling->left_->left_->black_) {
          sibling->black_ = true;
          sibling->left_->black_ = false;
          LeftRotation(parent);
        }
      }
    }

    // родитель чёрный, левый сын красный, у правого внука левый правнук красный
    if (parent->black_ == true && sibling->black_ == false) {
      if (sibling->left_child_) {
        if (sibling->right_ != nill_leaf_ &&
            sibling->right_->left_->black_ == false) {
          sibling->right_->left_->black_ = true;
          LeftRotation(sibling);
          RightRotation(parent);
        }
      } else {
        if (sibling->left_ != nill_leaf_ &&
            sibling->left_->right_->black_ == false) {
          sibling->left_->right_->black_ = true;
          LeftRotation(sibling);
          RightRotation(parent);
        }
      }
    }

    // родитель чёрный, левый сын чёрный с правым красным внуком.
    if (parent->black_ == true && sibling->black_ == true &&
        sibling != nill_leaf_) {
      if (sibling->left_child_) {
        if (sibling->left_->black_ == false &&
            sibling->right_->black_ != false) {
          std::swap(sibling->black_, sibling->left_->black_);
          RightRotation(sibling);
          sibling = parent->left_;
        }
        if (sibling->right_->black_ == false) {
          sibling->right_->black_ = true;
          LeftRotation(sibling);
          RightRotation(parent);
          sibling = nill_leaf_;
        }
      } else {
        if (sibling->right_->black_ == false &&
            sibling->left_->black_ != false) {
          std::swap(sibling->black_, sibling->right_->black_);
          LeftRotation(sibling);
          sibling = parent->right_;
        }

        if (sibling->left_->black_ == false) {
          sibling->left_->black_ = true;
          RightRotation(sibling);
          LeftRotation(parent);
          sibling = nill_leaf_;
        }
      }
    }

    // родитель чёрный, левый сын чёрный, его внуки тоже чёрные
    if (parent->black_ == true && sibling != nill_leaf_ &&
        sibling->black_ == true && sibling->left_->black_ == true &&
        sibling->right_->black_ == true) {
      sibling->black_ = false;
      // В результате чёрная высота всей нашей структуры уменьшится на 1 и мы
      // должны рекурсивно воззвать балансировку к праотцам.
      BalanceBlackChildFreeNode(parent);
    }
  }

  void SwapNodesValues(node_type* current,
                       node_type* exchanging_node) noexcept {
    if (current == head_) {
      head_ = exchanging_node;
    } else {
      if (current->left_child_) {
        current->parent_->left_ = exchanging_node;
      } else {
        current->parent_->right_ = exchanging_node;
      }
    }

    if (exchanging_node->left_child_) {
      exchanging_node->parent_->left_ = current;
    } else {
      exchanging_node->parent_->right_ = current;
    }

    std::swap(current->black_, exchanging_node->black_);
    std::swap(current->left_, exchanging_node->left_);
    std::swap(current->right_, exchanging_node->right_);
    std::swap(current->left_child_, exchanging_node->left_child_);
    std::swap(current->parent_, exchanging_node->parent_);

    if (exchanging_node->left_ != nill_leaf_) {
      exchanging_node->left_->parent_ = exchanging_node;
    }

    if (exchanging_node->right_ != nill_leaf_) {
      exchanging_node->right_->parent_ = exchanging_node;
    }
  }

  // HELPERS
  void CheckColor(node_type* node) noexcept {
    if (node == head_ || node->parent_ == nullptr) return;
    if (!node->black_ && !node->parent_->black_) CorrectTree(node);
    CheckColor(node->parent_);
  }

  // инструкция, по которой написан код:
  // https://habr.com/ru/companies/otus/articles/472040/
  void CorrectTree(node_type* node) noexcept {
    node_type *parent = node->parent_, *gparent = parent->parent_;
    if (parent->left_child_) {
      if (gparent->right_->black_) {
        if (!node->left_child_) {
          LeftRotation(parent);
          std::swap(parent, node);
        }
        RightRotation(gparent);
        if (gparent == head_) head_ = parent;
        parent->black_ = true;
        gparent->black_ = false;
      } else {
        parent->black_ = true;
        if (gparent != head_) gparent->black_ = false;
        gparent->right_->black_ = true;
        CheckColor(gparent);
      }
    } else {
      // зеркальный случай
      if (gparent->left_->black_) {
        if (!node->right_->black_) {
          RightRotation(parent);
          std::swap(parent, node);
        }
        LeftRotation(gparent);
        if (gparent == head_) head_ = parent;
        parent->black_ = true;
        gparent->black_ = false;
      } else {
        parent->black_ = true;
        if (gparent != head_) gparent->black_ = false;
        gparent->left_->black_ = true;
        CheckColor(gparent);
      }
    }
    head_->black_ = true;
  }

  /*
  берет ноду слева и поднимает ее на место узла-параметра
  узел параметр опускает направо
  */
  void RightRotation(node_type* node) noexcept {
    node_type* pivot = node->left_;
    pivot->parent_ = node->parent_;

    if (node->parent_->parent_ == nullptr) {
      head_ = pivot;
    } else {
      if (node->left_child_) {
        node->parent_->left_ = pivot;
      } else {
        node->parent_->right_ = pivot;
      }
    }

    pivot->left_child_ = node->left_child_;
    node->left_child_ = false;
    node->parent_ = pivot;
    node->left_ = pivot->right_;
    if (node->left_->parent_ != nullptr) node->left_->left_child_ = true;
    pivot->right_ = node;
    if (node->left_ != nill_leaf_) {
      node->left_->parent_ = node;
    }
  }

  void LeftRotation(node_type* node) noexcept {
    node_type* pivot = node->right_;
    pivot->parent_ = node->parent_;

    if (node->parent_->parent_ == nullptr) {
      head_ = pivot;
    } else {
      if (node->left_child_) {
        node->parent_->left_ = pivot;
      } else {
        node->parent_->right_ = pivot;
      }
    }

    pivot->left_child_ = node->left_child_;
    node->left_child_ = true;
    node->parent_ = pivot;
    node->right_ = pivot->left_;
    if (node->right_->parent_ != nullptr) node->right_->left_child_ = false;
    pivot->left_ = node;
    if (node->right_ != nill_leaf_) {
      node->right_->parent_ = node;
    }
  }

  void DeleteBranch(node_type* root) noexcept {
    if (root != nullptr && root != nill_leaf_) {
      DeleteBranch(root->left_);
      DeleteBranch(root->right_);
      delete root;
    }
  }

  class RedBlackTreeNode {
   public:
    RedBlackTreeNode() : key_(key_type{}) { MakeDefault(); }

    RedBlackTreeNode(const key_type& key) : key_(key) { MakeDefault(); }

    RedBlackTreeNode(key_type key, bool isBlack) : RedBlackTreeNode(key) {
      black_ = isBlack;
    }

    RedBlackTreeNode(node_type* node)
        : RedBlackTreeNode(node->key_, node->black_) {
      left_child_ = node->left_child_;
    }

    ~RedBlackTreeNode() { MakeDefault(); }

    node_type* NextNode() const {
      node_type* cur = const_cast<node_type*>(this);
      if (cur == nullptr) return cur;
      if (cur->parent_ == nullptr) return cur->left_;
      if (cur->right_->parent_ != nullptr) {
        cur = cur->right_;
        while (cur->left_->parent_ != nullptr) {
          cur = cur->left_;
        }
      } else {
        while (!cur->left_child_ && cur->parent_ != nullptr) {
          cur = cur->parent_;
        }
        if (cur->parent_ != nullptr) {
          cur = cur->parent_;
        }
      }
      return cur;
    }

    node_type* PrevNode() const {
      node_type* cur = const_cast<node_type*>(this);
      if (cur == nullptr) return cur;
      if (cur->parent_ == nullptr) return cur->right_;
      if (cur->left_->parent_ != nullptr) {
        cur = cur->left_;
        while (cur->right_->parent_ != nullptr) {
          cur = cur->right_;
        }
      } else {
        while (cur->left_child_ && cur->parent_ != nullptr) {
          cur = cur->parent_;
        }
        if (cur->parent_ != nullptr) {
          cur = cur->parent_;
        }
      }
      return cur;
    }
    void MakeDefault() noexcept {
      parent_ = nullptr;
      left_ = nullptr;
      right_ = nullptr;
      black_ = false;
      left_child_ = false;
    }

    node_type* parent_;
    node_type* left_;
    node_type* right_;
    key_type key_;
    bool black_;
    bool left_child_;
  };

  class RedBlackTreeIterator {
   public:
    RedBlackTreeIterator() = delete;
    explicit RedBlackTreeIterator(node_type* node) : node_(node) {}
    RedBlackTreeIterator(const iterator& o) : node_(o.node_) {}

    iterator& operator++() noexcept {
      node_ = node_->NextNode();
      return *this;
    }

    iterator& operator--() noexcept {
      node_ = node_->PrevNode();
      return *this;
    }

    iterator operator++(int) noexcept {
      iterator tmp{node_};
      node_ = node_->NextNode();
      return tmp;
    }

    iterator operator--(int) noexcept {
      iterator tmp{node_};
      node_ = node_->PrevNode();
      return tmp;
    }

    iterator& operator=(const iterator& other) noexcept {
      node_ = other.node_;
      return *this;
    }

    reference operator*() noexcept { return node_->key_; }

    bool operator==(const iterator& o) const noexcept {
      return node_ == o.node_;
    }

    bool operator!=(const iterator& o) const noexcept {
      return node_ != o.node_;
    }

    node_type* node_;
  };

  class RedBlackTreeConstIterator {
   public:
    RedBlackTreeConstIterator() = delete;
    RedBlackTreeConstIterator(const const_iterator& o) : node_(o.node_) {}
    explicit RedBlackTreeConstIterator(const node_type* node) : node_(node) {}
    RedBlackTreeConstIterator(const iterator& o) : node_(o.node_) {}

    const_iterator& operator++() noexcept {
      node_ = node_->NextNode();
      return *this;
    }

    const_iterator& operator--() noexcept {
      node_ = node_->PrevNode();
      return *this;
    }

    const_iterator operator++(int) noexcept {
      const_iterator tmp{node_};
      node_ = node_->NextNode();
      return tmp;
    }

    const_iterator operator--(int) noexcept {
      const_iterator tmp{node_};
      node_ = node_->PrevNode();
      return tmp;
    }

    const_reference operator*() const noexcept { return node_->key_; }

    friend bool operator==(const const_iterator& it1,
                           const const_iterator& it2) noexcept {
      return it1.node_ == it2.node_;
    }

    friend bool operator!=(const const_iterator& it1,
                           const const_iterator& it2) noexcept {
      return it1.node_ != it2.node_;
    }

   private:
    const node_type* node_;
  };

  node_type* head_;
  node_type* nill_leaf_;
  size_type size_;
  Comparator is_less_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_CONTAINERS_S21_BTREE_H_
