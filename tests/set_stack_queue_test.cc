#include <gtest/gtest.h>

#include <queue>
#include <set>
#include <stack>

#include "../containers/s21_queue.h"
#include "../containers/s21_set.h"
#include "../containers/s21_stack.h"

// ---------------------STACK---------------------

TEST(Stack, Default) {
  s21::Stack<int> x;
  std::stack<int> y;
  EXPECT_EQ(x.size(), y.size());
}
TEST(Stack, Init) {
  std::initializer_list<int> list = {1, 2, 3, 4};
  s21::Stack<int> x{list};
  std::stack<int> y{list};
  EXPECT_EQ(x.size(), y.size());
  EXPECT_EQ(x.top(), y.top());
}
TEST(Stack, Copy_1) {
  std::initializer_list<int> list = {1, 2, 3, 4};
  s21::Stack<int> x{list};
  std::stack<int> y{list};
  s21::Stack<int> new_copy(x);
  EXPECT_EQ(new_copy.size(), y.size());
  EXPECT_EQ(new_copy.top(), y.top());
}

TEST(Stack, Move_1) {
  std::initializer_list<int> list = {1, 2, 3, 4};
  s21::Stack<int> x{list};
  std::stack<int> y{list};
  s21::Stack<int> new_move((s21::Stack<int> &&) x);
  EXPECT_EQ(new_move.size(), y.size());
  EXPECT_EQ(new_move.top(), y.top());
  EXPECT_EQ(x.size(), 0);
}

TEST(Stack, Copy_2) {
  std::initializer_list<int> list = {1, 2, 3, 4};
  s21::Stack<int> x{list};
  std::stack<int> y{list};
  s21::Stack<int> new_copy;
  new_copy = x;
  EXPECT_EQ(new_copy.size(), y.size());
  EXPECT_EQ(new_copy.top(), y.top());
}

TEST(Stack, Move_2) {
  std::initializer_list<int> list = {1, 2, 3, 4};
  s21::Stack<int> x{list};
  std::stack<int> y{list};
  s21::Stack<int> new_move;
  new_move = (s21::Stack<int> &&) x;
  EXPECT_EQ(new_move.size(), y.size());
  EXPECT_EQ(new_move.top(), y.top());
  EXPECT_EQ(x.size(), 0);
}

TEST(Stack, Push) {
  s21::Stack<int> x;
  std::stack<int> y;
  x.push(1);
  x.push(2);
  y.push(1);
  y.push(2);
  EXPECT_EQ(x.size(), y.size());
  EXPECT_EQ(x.top(), y.top());
}

TEST(Stack, Pop) {
  s21::Stack<int> x;
  std::stack<int> y;
  x.push(1);
  x.push(2);
  x.pop();
  y.push(1);
  y.push(2);
  y.pop();
  EXPECT_EQ(x.size(), y.size());
  EXPECT_EQ(x.top(), y.top());
}

TEST(Stack, Swap) {
  s21::Stack<int> x;
  s21::Stack<int> y;
  x.push(1);
  x.push(2);
  y.push(2);
  y.push(1);
  x.swap(y);
  EXPECT_EQ(x.top(), 1);
  EXPECT_EQ(y.top(), 2);
}

TEST(Stack, Top) {
  s21::Stack<int> x;
  EXPECT_THROW(x.top(), std::out_of_range);
}

TEST(Stack, Empty) {
  s21::Stack<int> x;
  EXPECT_EQ(x.empty(), true);
}

// ---------------------QUEUE---------------------

TEST(Queue, Default) {
  s21::Queue<int> x;
  std::queue<int> y;
  EXPECT_EQ(x.size(), y.size());
}

TEST(Queue, Init) {
  std::initializer_list<int> list = {1, 2, 3, 4};
  s21::Queue<int> x{list};
  std::queue<int> y{list};
  EXPECT_EQ(x.front(), y.front());
  EXPECT_EQ(x.back(), y.back());
}

TEST(Queue, Copy_1) {
  std::initializer_list<int> list = {1, 2, 3, 4};
  s21::Queue<int> x{list};
  std::queue<int> y{list};
  s21::Queue<int> new_copy(x);
  EXPECT_EQ(new_copy.front(), y.front());
  EXPECT_EQ(new_copy.back(), y.back());
}

TEST(Queue, Move_1) {
  std::initializer_list<int> list = {1, 2, 3, 4};
  s21::Queue<int> x{list};
  std::queue<int> y{list};
  s21::Queue<int> new_move((s21::Queue<int> &&) x);
  EXPECT_EQ(new_move.front(), y.front());
  EXPECT_EQ(new_move.back(), y.back());
  EXPECT_EQ(x.size(), 0);
}

TEST(Queue, Copy_2) {
  std::initializer_list<int> list = {1, 2, 3, 4};
  s21::Queue<int> x{list};
  std::queue<int> y{list};
  s21::Queue<int> new_copy;
  new_copy = x;
  EXPECT_EQ(new_copy.front(), y.front());
  EXPECT_EQ(new_copy.back(), y.back());
}

TEST(Queue, Move_2) {
  std::initializer_list<int> list = {1, 2, 3, 4};
  s21::Queue<int> x{list};
  std::queue<int> y{list};
  s21::Queue<int> new_move;
  new_move = (s21::Queue<int> &&) x;
  EXPECT_EQ(new_move.front(), y.front());
  EXPECT_EQ(new_move.back(), y.back());
  EXPECT_EQ(x.size(), 0);
}

TEST(Queue, Push) {
  s21::Queue<int> x;
  x.push(1);
  x.push(2);
  std::queue<int> y;
  y.push(1);
  y.push(2);
  EXPECT_EQ(x.front(), y.front());
  EXPECT_EQ(x.back(), y.back());
}

TEST(Queue, Pop_1) {
  s21::Queue<int> x;
  x.push(1);
  x.push(2);
  x.pop();
  std::queue<int> y;
  y.push(1);
  y.push(2);
  y.pop();
  EXPECT_EQ(x.front(), y.front());
  EXPECT_EQ(x.back(), y.back());
}

TEST(Queue, Pop_2) {
  s21::Queue<int> x;
  x.push(1);
  x.pop();
  EXPECT_THROW(x.front(), std::out_of_range);
  EXPECT_THROW(x.back(), std::out_of_range);
}

TEST(Queue, Swap) {
  s21::Queue<int> x;
  s21::Queue<int> y;
  x.push(1);
  x.push(2);
  y.push(2);
  y.push(1);
  x.swap(y);
  EXPECT_EQ(x.back(), 1);
  EXPECT_EQ(y.back(), 2);
  EXPECT_EQ(x.front(), 2);
  EXPECT_EQ(y.front(), 1);
}

TEST(Queue, Throw_Nullptr) {
  s21::Queue<int> x;
  EXPECT_THROW(x.front(), std::out_of_range);
  EXPECT_THROW(x.back(), std::out_of_range);
}

TEST(Queue, Empty) {
  s21::Queue<int> x;
  EXPECT_EQ(x.empty(), true);
}

// ---------------------SET---------------------

TEST(Set, Default) {
  s21::Set<int> x;
  std::set<int> y;
  EXPECT_EQ(x.size(), y.size());
}

TEST(Set, Init) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  s21::Set<int> x{list};
  std::set<int> y{list};
  EXPECT_EQ(x.size(), y.size());
}

TEST(Set, Copy_1) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  s21::Set<int> x{list};
  std::set<int> y{list};
  s21::Set<int> new_copy(x);
  EXPECT_EQ(new_copy.size(), y.size());
}

TEST(Set, Move_1) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  s21::Set<int> x{list};
  std::set<int> y{list};
  s21::Set<int> new_move((s21::Set<int> &&) x);
  EXPECT_EQ(new_move.size(), y.size());
  EXPECT_EQ(x.size(), 0);
}

TEST(Set, Copy_2) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  s21::Set<int> x{list};
  std::set<int> y{list};
  s21::Set<int> new_copy;
  new_copy = x;
  EXPECT_EQ(new_copy.size(), y.size());
}

TEST(Set, Move_2) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  s21::Set<int> x{list};
  std::set<int> y{list};
  s21::Set<int> new_move;
  new_move = (s21::Set<int> &&) x;
  EXPECT_EQ(new_move.size(), y.size());
  EXPECT_EQ(x.size(), 0);
}

TEST(Set, Begin) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  s21::Set<int> x{list};
  std::set<int> y{list};
  EXPECT_EQ(*(x.begin()), *(y.begin()));
}

TEST(Set, End) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  s21::Set<int> x{list};
  std::set<int> y{list};
  EXPECT_EQ(*(--x.end()), *(--y.end()));
}

TEST(Set, Cbegin) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  s21::Set<int> x{list};
  std::set<int> y{list};
  EXPECT_EQ(*(x.cbegin()), *(y.cbegin()));
}

TEST(Set, Cend) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  s21::Set<int> x{list};
  std::set<int> y{list};
  EXPECT_EQ(*(--x.cend()), *(--y.cend()));
}

TEST(Set, Size_MaxSize) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  s21::Set<int> x{list};
  std::set<int> y{list};
  EXPECT_EQ(x.size(), y.size());
  EXPECT_GT(x.max_size(), 0);
}

TEST(Set, Clear) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  s21::Set<int> x{list};
  x.clear();
  EXPECT_EQ(x.empty(), 1);
}

TEST(Set, Insert) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  std::set<int> y{list};
  s21::Set<int> x;
  x.insert(2);
  x.insert(0);
  x.insert(1);
  x.insert(2);
  EXPECT_EQ(x.size(), y.size());
  EXPECT_EQ(*(x.begin()), *(y.begin()));
  EXPECT_EQ(*(--x.end()), *(--y.end()));
}

TEST(Set, Find_Erase) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  s21::Set<int> x{list};
  std::set<int> y{list};
  x.erase(x.find(0));
  y.erase(y.find(0));
  EXPECT_EQ(x.size(), y.size());
  EXPECT_EQ(*(x.begin()), *(y.begin()));
  EXPECT_EQ(*(--x.end()), *(--y.end()));
}

TEST(Set, Swap) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  s21::Set<int> x{list};
  std::set<int> y{list};
  s21::Set<int> new_swap = {3, 3};
  x.swap(new_swap);
  EXPECT_EQ(new_swap.size(), y.size());
  EXPECT_EQ(x.size(), 1);
}

TEST(Set, Merge) {
  std::initializer_list<int> list = {3, 3, 1, 2, 2, 0};
  std::set<int> y{list};
  s21::Set<int> x = {1, 2, 2, 0};
  s21::Set<int> new_merge = {3, 3};
  x.merge(new_merge);
  EXPECT_EQ(*(x.begin()), *(y.begin()));
  EXPECT_EQ(*(--x.end()), *(--y.end()));
}

TEST(Set, Bool_Contains) {
  std::initializer_list<int> list = {1, 2, 2, 0};
  s21::Set<int> x{list};
  std::set<int> y{list};
  EXPECT_EQ(x.contains(3), y.find(3) != y.end());
  EXPECT_EQ(x.contains(2), y.find(2) != y.end());
}
