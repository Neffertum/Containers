#include <gtest/gtest.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "../containers/s21_vector.h"

TEST(Vector_test, default_constructor) {
  s21::Vector<int> s21_vec_empty;
  std::vector<int> stl_vec_empty;
  EXPECT_EQ(s21_vec_empty.size(), stl_vec_empty.size());
  EXPECT_EQ(s21_vec_empty.capacity(), stl_vec_empty.capacity());
  EXPECT_EQ(s21_vec_empty.data(), stl_vec_empty.data());
}

TEST(Vector_test, zero_val_constructor) {
  s21::Vector<int> s21_vec_zero_val(5);
  std::vector<int> stl_vec_zero_val(5);
  EXPECT_EQ(s21_vec_zero_val.size(), stl_vec_zero_val.size());
  EXPECT_EQ(s21_vec_zero_val.capacity(), stl_vec_zero_val.capacity());
  auto stl = stl_vec_zero_val.begin();
  for (auto s21 = s21_vec_zero_val.begin(); s21 != s21_vec_zero_val.end();
       ++s21, ++stl) {
    EXPECT_EQ(*s21, *stl);
    EXPECT_EQ(*s21, 0);
  }
}

TEST(Vector_test, zero_parameters) {
  s21::Vector<int> s21_vec_1(0);
  std::vector<int> stl_vec_1(0);
  s21::Vector<int> s21_vec_2(0, 0);
  std::vector<int> stl_vec_2(0, 0);
  EXPECT_EQ(s21_vec_1.size(), stl_vec_1.size());
  EXPECT_EQ(s21_vec_1.capacity(), stl_vec_1.capacity());
  EXPECT_EQ(s21_vec_1.data(), stl_vec_1.data());
  EXPECT_EQ(s21_vec_2.size(), stl_vec_2.size());
  EXPECT_EQ(s21_vec_2.capacity(), stl_vec_2.capacity());
  EXPECT_EQ(s21_vec_2.data(), stl_vec_2.data());
}

TEST(Vector_test, same_val_constructor) {
  s21::Vector<int> s21_vec_same_val(5, 1);
  std::vector<int> stl_vec_same_val(5, 1);
  EXPECT_EQ(s21_vec_same_val.size(), stl_vec_same_val.size());
  EXPECT_EQ(s21_vec_same_val.capacity(), stl_vec_same_val.capacity());
  auto stl = stl_vec_same_val.begin();
  for (auto s21 = s21_vec_same_val.begin(); s21 != s21_vec_same_val.end();
       ++s21, ++stl) {
    EXPECT_EQ(*s21, *stl);
  }
}

TEST(Vector_test, init_list_constructor) {
  s21::Vector<int> s21_vec_init_list = {1, 2, 3, 4, 5};
  std::vector<int> stl_vec_init_list = {1, 2, 3, 4, 5};
  EXPECT_EQ(s21_vec_init_list.size(), stl_vec_init_list.size());
  EXPECT_EQ(s21_vec_init_list.capacity(), stl_vec_init_list.capacity());
  auto stl = stl_vec_init_list.begin();
  for (auto s21 = s21_vec_init_list.begin(); s21 != s21_vec_init_list.end();
       ++s21, ++stl) {
    EXPECT_EQ(*s21, *stl);
  }
}

TEST(Vector_test, copy_constructor) {
  s21::Vector<int> original = {1, 2, 3, 4, 5};
  s21::Vector<int> cpy(original);
  auto orig = original.cbegin();
  for (auto cp = cpy.cbegin(); cp != cpy.cend(); ++cp, ++orig) {
    EXPECT_EQ(*orig, *cp);
  }
}

TEST(Vector_test, move_constructor) {
  s21::Vector<int> original(5, 10);
  s21::Vector<int> cpy(std::move(original));
  for (auto it = cpy.cbegin(); it != cpy.cend(); ++it) {
    EXPECT_EQ(*it, 10);
  }
}

TEST(Vector_test, at_test) {
  s21::Vector<int> s21 = {1, 2, 3};
  std::vector<int> stl = {1, 2, 3};
  EXPECT_EQ(s21.at(0), stl.at(0));
  EXPECT_EQ(s21.at(2), stl.at(2));
  ASSERT_THROW(s21.at(10), std::out_of_range);
}

TEST(Vector_test, at_const_test) {
  const s21::Vector<int> s21 = {1, 2, 3};
  const std::vector<int> stl = {1, 2, 3};
  const int s21_at = s21.at(0);
  const int stl_at = stl.at(0);
  EXPECT_EQ(s21_at, stl_at);
  const int s21_at2 = s21.at(2);
  const int stl_at2 = stl.at(2);
  EXPECT_EQ(s21_at2, stl_at2);
  ASSERT_THROW(s21.at(10), std::out_of_range);
}

TEST(Vector_test, operator_square_brackets) {
  s21::Vector<int> s21 = {1, 2, 3};
  std::vector<int> stl = {1, 2, 3};
  EXPECT_EQ(s21[0], stl[0]);
  EXPECT_EQ(s21[1], stl[1]);
  EXPECT_EQ(s21[2], stl[2]);
}

TEST(Vector_test, operator_square_brackets_const) {
  const s21::Vector<int> s21 = {1, 2, 3};
  const std::vector<int> stl = {1, 2, 3};
  for (auto i = 0; i < 3; ++i) {
    const int s21_at = s21[i];
    const int stl_at = stl[i];
    EXPECT_EQ(s21_at, stl_at);
  }
}

TEST(Vector_test, front_test) {
  s21::Vector<int> s21 = {1, 2, 3};
  std::vector<int> stl = {1, 2, 3};
  EXPECT_EQ(s21.front(), stl.front());
}

TEST(Vector_test, const_front_test) {
  const s21::Vector<int> s21 = {1, 2, 3};
  const std::vector<int> stl = {1, 2, 3};
  EXPECT_EQ(s21.front(), stl.front());
}

TEST(Vector_test, back_test) {
  s21::Vector<int> s21 = {1, 2, 3};
  std::vector<int> stl = {1, 2, 3};
  EXPECT_EQ(s21.back(), stl.back());
}

TEST(Vector_test, const_back_test) {
  const s21::Vector<int> s21 = {1, 2, 3};
  const std::vector<int> stl = {1, 2, 3};
  EXPECT_EQ(s21.back(), stl.back());
}

TEST(Vector_test, data_test) {
  s21::Vector<int> s21(10, 1);
  std::vector<int> stl(10, 1);
  EXPECT_EQ(*s21.data(), *stl.data());
}

TEST(Vector_test, const_data_test) {
  const s21::Vector<int> s21(10, 5);
  const std::vector<int> stl(10, 5);
  EXPECT_EQ(*s21.data(), *stl.data());
}

TEST(Vector_test, empty_true_test) {
  s21::Vector<int> s21;
  EXPECT_TRUE(s21.empty());
}

TEST(Vector_test, empty_false_test) {
  s21::Vector<int> s21(150);
  EXPECT_FALSE(s21.empty());
}

TEST(Vector_test, size_test) {
  s21::Vector<int> s21;
  EXPECT_EQ(s21.size(), 0U);
  s21.push_back(10);
  EXPECT_EQ(s21.size(), 1U);
  s21.push_back(158);
  EXPECT_EQ(s21.size(), 2U);
}

TEST(Vector_test, max_size_test) {
  s21::Vector<int> s21;
  std::vector<int> stl;
  EXPECT_EQ(s21.size(), stl.size());
  EXPECT_GT(s21.max_size(), 0);
}

TEST(Vector_test, reserve_test) {
  s21::Vector<int> s21 = {1, 2, 3};
  std::vector<int> stl = {1, 2, 3};
  s21.reserve(100);
  stl.reserve(100);
  EXPECT_EQ(s21.capacity(), stl.capacity());
  ASSERT_THROW(s21.reserve(s21.max_size() + 1), std::length_error);
}

TEST(Vector_test, capacity_test) {
  s21::Vector<int> s21(100);
  std::vector<int> stl(100);
  EXPECT_EQ(s21.capacity(), stl.capacity());
}

TEST(Vector_test, shrink_to_fit_test) {
  s21::Vector<int> s21(10, 5);
  std::vector<int> stl(10, 5);
  s21.reserve(100);
  stl.reserve(100);
  s21.shrink_to_fit();
  stl.shrink_to_fit();
  EXPECT_EQ(s21.capacity(), stl.capacity());
}

TEST(Vector_test, shrink_to_fit_test2) {
  s21::Vector<int> s21 = {1, 2, 3};
  std::vector<int> stl = {1, 2, 3};
  for (auto i = 0; i < 3; ++i) {
    s21.pop_back();
    stl.pop_back();
  }
  s21.shrink_to_fit();
  stl.shrink_to_fit();
  EXPECT_EQ(s21.size(), stl.size());
  EXPECT_EQ(s21.capacity(), stl.capacity());
  EXPECT_EQ(s21.data(), stl.data());
}

TEST(Vector_test, clear_test) {
  s21::Vector<int> s21(10, 5);
  std::vector<int> stl(10, 5);
  s21.clear();
  stl.clear();
  EXPECT_EQ(s21.size(), stl.size());
}

TEST(Vector_test, insert_test) {
  s21::Vector<int> s21(10, 5);
  std::vector<int> stl(10, 5);
  auto s21_it = s21.begin() + 4;
  auto stl_it = stl.begin() + 4;
  s21.insert(s21_it, 6);
  stl.insert(stl_it, 6);
  EXPECT_EQ(s21.size(), stl.size());
  EXPECT_EQ(s21.capacity(), stl.capacity());
  for (auto i = 0; i < 11; ++i) {
    EXPECT_EQ(s21[i], stl[i]);
  }
}

TEST(Vector_test, insert_test_noreserve) {
  s21::Vector<int> s21 = {1, 2, 3, 4, 5};
  std::vector<int> stl = {1, 2, 3, 4, 5};
  s21.reserve(10);
  stl.reserve(10);
  auto s21_it = s21.begin() + 2;
  auto stl_it = stl.begin() + 2;
  s21.insert(s21_it, 10);
  stl.insert(stl_it, 10);
  EXPECT_EQ(s21.size(), stl.size());
  EXPECT_EQ(s21.capacity(), stl.capacity());
  for (auto i = 0U; i < s21.size(); ++i) {
    EXPECT_EQ(s21[i], stl[i]);
  }
}

TEST(Vector_test, erase_test) {
  s21::Vector<int> s21 = {1, 2, 3, 4, 5};
  std::vector<int> stl = {1, 2, 3, 4, 5};
  auto s21_it = s21.begin();
  auto stl_it = stl.begin();
  s21.erase(s21_it);
  stl.erase(stl_it);
  EXPECT_EQ(s21.size(), stl.size());
  EXPECT_EQ(s21.capacity(), stl.capacity());
  for (auto i = 0U; i < s21.size(); ++i) {
    EXPECT_EQ(s21[i], stl[i]);
  }
}

TEST(Vector_test, erase_test_end) {
  s21::Vector<std::string> s21 = {"hello", "world", "!"};
  std::vector<std::string> stl = {"hello", "world", "!"};
  s21.erase(s21.end() - 1);
  stl.erase(stl.end() - 1);
  EXPECT_EQ(s21.size(), stl.size());
  EXPECT_EQ(s21.capacity(), stl.capacity());
  for (auto i = 0U; i < s21.size(); ++i) {
    EXPECT_EQ(s21[i], stl[i]);
  }
}

TEST(Vector_test, push_back_test) {
  s21::Vector<int> s21 = {1, 2, 3, 4, 5};
  std::vector<int> stl = {1, 2, 3, 4, 5};
  s21.push_back(11);
  stl.push_back(11);
  EXPECT_EQ(s21.size(), stl.size());
  EXPECT_EQ(s21.capacity(), stl.capacity());
  for (auto i = 0U; i < s21.size(); ++i) {
    EXPECT_EQ(s21[i], stl[i]);
  }
}

TEST(Vector_test, pop_back_test) {
  s21::Vector<int> s21 = {1, 2, 3, 4, 5, 6};
  std::vector<int> stl = {1, 2, 3, 4, 5, 6};
  s21.pop_back();
  stl.pop_back();
  EXPECT_EQ(s21.size(), stl.size());
  EXPECT_EQ(s21.capacity(), stl.capacity());
  for (auto i = 0U; i < s21.size(); ++i) {
    EXPECT_EQ(s21[i], stl[i]);
  }
}

TEST(Vector_test, resize_test) {
  s21::Vector<int> s21 = {1, 2, 3, 4, 5, 6};
  std::vector<int> stl{1, 2, 3, 4, 5, 6};
  s21.resize(150);
  stl.resize(150);
  EXPECT_EQ(s21.size(), stl.size());
  EXPECT_EQ(s21.capacity(), stl.capacity());
  for (auto i = 0U; i < s21.size(); ++i) {
    EXPECT_EQ(s21[i], stl[i]);
  }

  s21.resize(3);
  stl.resize(3);
  EXPECT_EQ(s21.size(), stl.size());
  EXPECT_EQ(s21.capacity(), stl.capacity());
  for (auto i = 0U; i < s21.size(); ++i) {
    EXPECT_EQ(s21[i], stl[i]);
  }

  s21.resize(5, 1111);
  stl.resize(5, 1111);
  EXPECT_EQ(s21.size(), stl.size());
  EXPECT_EQ(s21.capacity(), stl.capacity());
  for (auto i = 0U; i < s21.size(); ++i) {
    EXPECT_EQ(s21[i], stl[i]);
  }

  s21.shrink_to_fit();
  stl.shrink_to_fit();
  s21.resize(10, 1500);
  stl.resize(10, 1500);
  EXPECT_EQ(s21.size(), stl.size());
  EXPECT_EQ(s21.size(), stl.size());
  for (auto i = 0U; i < s21.size(); ++i) {
    EXPECT_EQ(s21[i], stl[i]);
  }
}

TEST(Vector_test, swap_test) {
  s21::Vector<int> first(10, 1);
  s21::Vector<int> second(11, 2);
  swap(first, second);
  EXPECT_EQ(first.size(), 11U);
  EXPECT_EQ(first.capacity(), 11U);
  for (auto i = 0U; i < first.size(); ++i) {
    EXPECT_EQ(first[i], 2);
  }

  EXPECT_EQ(second.size(), 10U);
  EXPECT_EQ(second.capacity(), 10U);
  for (auto i = 0U; i < second.size(); ++i) {
    EXPECT_EQ(second[i], 1);
  }
}

TEST(Vector_test, begin_test) {
  s21::Vector<int> s21 = {1, 2, 3, 4, 5};
  std::vector<int> stl = {1, 2, 3, 4, 5};
  auto s21_it = s21.begin();
  auto stl_it = stl.begin();
  EXPECT_EQ(*s21_it, *stl_it);

  ++s21_it;
  ++stl_it;
  EXPECT_EQ(*s21_it, *stl_it);

  --s21_it;
  --stl_it;
  EXPECT_EQ(*s21_it, *stl_it);

  s21_it++;
  stl_it++;
  EXPECT_EQ(*s21_it, *stl_it);

  s21_it--;
  stl_it--;
  EXPECT_EQ(*s21_it, *stl_it);

  s21_it += 2;
  stl_it += 2;
  EXPECT_EQ(*s21_it, *stl_it);

  s21_it -= 2;
  stl_it -= 2;
  EXPECT_EQ(*s21_it, *stl_it);

  s21_it += 2;
  stl_it += 2;
  auto s21_begin = s21.begin();
  auto stl_begin = stl.begin();
  EXPECT_EQ((s21_it - s21_begin), (stl_it - stl_begin));
}

TEST(Vector_test, end_test) {
  s21::Vector<int> s21 = {1, 2, 3, 4, 5};
  std::vector<int> stl = {1, 2, 3, 4, 5};
  auto s21_it = s21.end();
  auto stl_it = stl.end();

  --s21_it;
  --stl_it;
  EXPECT_EQ(*s21_it, *stl_it);
}

TEST(Vector_test, cbegin_test) {
  s21::Vector<int> s21 = {1, 2, 3, 4, 5};
  std::vector<int> stl = {1, 2, 3, 4, 5};
  auto s21_it = s21.cbegin();
  auto stl_it = stl.cbegin();

  s21_it++;
  stl_it++;

  EXPECT_EQ(*s21_it, *stl_it);
}

TEST(Vector_test, cend_test) {
  s21::Vector<int> s21 = {1, 2, 3, 4, 5};
  std::vector<int> stl = {1, 2, 3, 4, 5};
  auto s21_it = s21.cend();
  auto stl_it = stl.cend();

  --s21_it;
  --stl_it;

  EXPECT_EQ(*s21_it, *stl_it);
}

TEST(Vector_test, rbegin_test) {
  s21::Vector<int> s21 = {1, 2, 3, 4, 5};
  std::vector<int> stl = {1, 2, 3, 4, 5};
  auto s21_it = s21.rbegin();
  auto stl_it = stl.rbegin();
  EXPECT_EQ(*s21_it, *stl_it);
  ++s21_it;
  ++stl_it;
  EXPECT_EQ(*s21_it, *stl_it);
}

TEST(Vector_test, rend_test) {
  s21::Vector<int> s21 = {1, 2, 3, 4, 5};
  std::vector<int> stl = {1, 2, 3, 4, 5};
  auto s21_it = s21.rend();
  auto stl_it = stl.rend();
  --s21_it;
  --stl_it;
  EXPECT_EQ(*s21_it, *stl_it);
}

TEST(Vector_test, crbegin_test) {
  s21::Vector<int> s21 = {1, 2, 3, 4, 5};
  std::vector<int> stl = {1, 2, 3, 4, 5};
  auto s21_it = s21.crbegin();
  auto stl_it = stl.crbegin();
  EXPECT_EQ(*s21_it, *stl_it);
  ++s21_it;
  ++stl_it;
  EXPECT_EQ(*s21_it, *stl_it);
}

TEST(Vector_test, crend_test) {
  s21::Vector<int> s21 = {1, 2, 3, 4, 5};
  std::vector<int> stl = {1, 2, 3, 4, 5};
  auto s21_it = s21.crend();
  auto stl_it = stl.crend();
  --s21_it;
  --stl_it;
  EXPECT_EQ(*s21_it, *stl_it);
}

TEST(Vector_test, eq_comparison_operator_test) {
  s21::Vector<int> s21_first = {1, 2, 3, 4, 5};
  s21::Vector<int> s21_second(s21_first);
  std::vector<int> stl_first = {1, 2, 3, 4, 5};
  std::vector<int> stl_second(stl_first);

  EXPECT_EQ((s21_first == s21_second), (stl_first == stl_second));

  s21_second.back() = 6;
  stl_second.back() = 6;

  EXPECT_EQ((s21_first == s21_second), (stl_first == stl_second));

  s21_second = s21_first;
  stl_second = stl_first;

  s21_second.front() = 10;
  stl_second.front() = 10;

  EXPECT_EQ((s21_first == s21_second), (stl_first == stl_second));

  s21_second = s21_first;
  stl_second = stl_first;
  s21_second.resize(2);
  stl_second.resize(2);

  EXPECT_EQ((s21_first == s21_second), (stl_first == stl_second));
}

TEST(Vector_test, neq_comparison_operator_test) {
  s21::Vector<int> s21_first = {1, 2, 3, 4, 5};
  s21::Vector<int> s21_second(s21_first);
  std::vector<int> stl_first = {1, 2, 3, 4, 5};
  std::vector<int> stl_second(stl_first);

  EXPECT_EQ((s21_first != s21_second), (stl_first != stl_second));

  s21_second.back() = 6;
  stl_second.back() = 6;

  EXPECT_EQ((s21_first != s21_second), (stl_first != stl_second));

  s21_second = s21_first;
  stl_second = stl_first;
  s21_second.front() = 6;
  stl_second.front() = 6;

  EXPECT_EQ((s21_first != s21_second), (stl_first != stl_second));

  s21_second = s21_first;
  stl_second = stl_first;
  s21_second.resize(2);
  stl_second.resize(2);

  EXPECT_EQ((s21_first != s21_second), (stl_first != stl_second));
}

TEST(Vector_test, less_comparison_operator_test) {
  s21::Vector<int> s21_first = {1, 2, 3, 4, 5};
  s21::Vector<int> s21_second(s21_first);
  std::vector<int> stl_first = {1, 2, 3, 4, 5};
  std::vector<int> stl_second(stl_first);

  EXPECT_EQ((s21_first < s21_second), (stl_first < stl_second));

  s21_first.back() = 0;
  stl_first.back() = 0;

  EXPECT_EQ((s21_first < s21_second), (stl_first < stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.back() = 0;
  stl_first.back() = 0;

  EXPECT_EQ((s21_first < s21_second), (stl_first < stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.back() = 10;
  stl_first.back() = 10;

  EXPECT_EQ((s21_first < s21_second), (stl_first < stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.front() = 10;
  stl_first.front() = 10;

  EXPECT_EQ((s21_first < s21_second), (stl_first < stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.resize(2);
  stl_first.resize(2);

  EXPECT_EQ((s21_first < s21_second), (stl_first < stl_second));
}

TEST(Vector_test, less_or_eq_comparison_operator_test) {
  s21::Vector<int> s21_first = {1, 2, 3, 4, 5};
  s21::Vector<int> s21_second(s21_first);
  std::vector<int> stl_first = {1, 2, 3, 4, 5};
  std::vector<int> stl_second(stl_first);

  EXPECT_EQ((s21_first <= s21_second), (stl_first <= stl_second));

  s21_first.back() = 0;
  stl_first.back() = 0;

  EXPECT_EQ((s21_first <= s21_second), (stl_first <= stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.front() = 0;
  stl_first.front() = 0;

  EXPECT_EQ((s21_first <= s21_second), (stl_first <= stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.back() = 10;
  stl_first.back() = 10;

  EXPECT_EQ((s21_first <= s21_second), (stl_first <= stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.front() = 10;
  stl_first.front() = 10;

  EXPECT_EQ((s21_first <= s21_second), (stl_first <= stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.resize(2);
  stl_first.resize(2);

  EXPECT_EQ((s21_first <= s21_second), (stl_first <= stl_second));
}

TEST(Vector_test, greater_comparison_operator_test) {
  s21::Vector<int> s21_first = {1, 2, 3, 4, 5};
  s21::Vector<int> s21_second(s21_first);
  std::vector<int> stl_first = {1, 2, 3, 4, 5};
  std::vector<int> stl_second(stl_first);

  EXPECT_EQ((s21_first > s21_second), (stl_first > stl_second));

  s21_first.back() = 0;
  stl_first.back() = 0;

  EXPECT_EQ((s21_first > s21_second), (stl_first > stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.front() = 0;
  stl_first.front() = 0;

  EXPECT_EQ((s21_first > s21_second), (stl_first > stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.back() = 10;
  stl_first.back() = 10;

  EXPECT_EQ((s21_first > s21_second), (stl_first > stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.front() = 10;
  stl_first.front() = 10;

  EXPECT_EQ((s21_first > s21_second), (stl_first > stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.resize(2);
  stl_first.resize(2);

  EXPECT_EQ((s21_first > s21_second), (stl_first > stl_second));
}

TEST(Vector_test, greater_or_eq_comparison_operator_test) {
  s21::Vector<int> s21_first = {1, 2, 3, 4, 5};
  s21::Vector<int> s21_second(s21_first);
  std::vector<int> stl_first = {1, 2, 3, 4, 5};
  std::vector<int> stl_second(stl_first);

  EXPECT_EQ((s21_first >= s21_second), (stl_first >= stl_second));

  s21_first.back() = 0;
  stl_first.back() = 0;

  EXPECT_EQ((s21_first >= s21_second), (stl_first >= stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.front() = 0;
  stl_first.front() = 0;

  EXPECT_EQ((s21_first >= s21_second), (stl_first >= stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.back() = 10;
  stl_first.back() = 10;

  EXPECT_EQ((s21_first >= s21_second), (stl_first >= stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.front() = 10;
  stl_first.front() = 10;

  EXPECT_EQ((s21_first >= s21_second), (stl_first >= stl_second));

  s21_first = s21_second;
  stl_first = stl_second;
  s21_first.resize(2);
  stl_first.resize(2);

  EXPECT_EQ((s21_first >= s21_second), (stl_first >= stl_second));
}

TEST(Vector_test, assign_operator_test) {
  s21::Vector<int> first = {1, 2, 3, 4, 5};
  s21::Vector<int> second;
  second = first;
  EXPECT_EQ(first.size(), second.size());
  EXPECT_EQ(first.capacity(), second.capacity());
  for (auto f_it = first.cbegin(), s_it = second.cbegin(); f_it != first.cend();
       ++f_it, ++s_it) {
    EXPECT_EQ(*f_it, *s_it);
  }
}

TEST(Vector_test, assign_operator_eq_vals_test) {
  s21::Vector<int> first = {1, 2, 3, 4, 5};
  s21::Vector<int> second = {1, 2, 3, 4, 5};
  second = first;
  EXPECT_EQ(first.size(), second.size());
  EXPECT_EQ(first.capacity(), second.capacity());
  for (auto f_it = first.cbegin(), s_it = second.cbegin(); f_it != first.cend();
       ++f_it, ++s_it) {
    EXPECT_EQ(*f_it, *s_it);
  }
}

TEST(Vector_test, move_assign_operator_test) {
  s21::Vector<int> first = {1, 2, 3, 4, 5};
  s21::Vector<int> second;
  second = std::move(first);
  EXPECT_EQ(second.size(), 5U);
  EXPECT_EQ(second.capacity(), 5U);
  int check = 1;
  for (auto it = second.cbegin(); it != second.cend(); ++it, ++check) {
    EXPECT_EQ(*it, check);
  }
  EXPECT_EQ(first.data(), nullptr);
}

TEST(Vector_test, move_assign_operator_test2) {
  s21::Vector<int> first = {1, 2, 3, 4, 5};
  s21::Vector<int> second = {5, 6, 7, 8, 9};
  second = std::move(first);
  EXPECT_EQ(second.size(), 5U);
  EXPECT_EQ(second.capacity(), 5U);
  int check = 1;
  for (auto it = second.cbegin(); it != second.cend(); ++it, ++check) {
    EXPECT_EQ(*it, check);
  }
  EXPECT_EQ(first.data(), nullptr);
}

TEST(Vector_test, move_assign_operator_eq_vals_test) {
  s21::Vector<int> first = {1, 2, 3, 4, 5};
  s21::Vector<int> second = {1, 2, 3, 4, 5};
  second = std::move(first);
  EXPECT_EQ(second.size(), 5U);
  EXPECT_EQ(second.capacity(), 5U);
  int check = 1;
  for (auto it = second.cbegin(); it != second.cend(); ++it, ++check) {
    EXPECT_EQ(*it, check);
  }
  EXPECT_EQ(first.data(), nullptr);
}

TEST(Vector_test, insert_many_test) {
  s21::Vector<int> vec = {1, 2, 3, 4};
  vec.insert_many(vec.cbegin() + 1, 10, 11, 12);
  EXPECT_EQ(vec.size(), 7U);
  EXPECT_EQ(vec.at(0), 1);
  EXPECT_EQ(vec.at(1), 10);
  EXPECT_EQ(vec.at(2), 11);
  EXPECT_EQ(vec.at(3), 12);
  EXPECT_EQ(vec.at(4), 2);
  EXPECT_EQ(vec.at(5), 3);
  EXPECT_EQ(vec.at(6), 4);
}

TEST(Vector_test, insert_many_test2) {
  s21::Vector<int> vec = {1, 2, 3, 4};
  s21::Vector<int> check = {-2, -1, 0, 1, 2, 3, 4};
  vec.insert_many(vec.cbegin(), -2, -1, 0);
  EXPECT_EQ(check.size(), vec.size());
  for (auto i = vec.cbegin(), ch = check.cbegin(); i != vec.cend(); ++i, ++ch) {
    EXPECT_EQ(*ch, *i);
  }
}

TEST(Vector_test, insert_many_test3) {
  s21::Vector<int> vec = {1, 2, 3, 4};
  s21::Vector<int> check = {1, 2, 3, 4, 5, 6, 7};
  vec.insert_many(vec.cend(), 5, 6, 7);
  EXPECT_EQ(vec.size(), check.size());
  for (auto i = vec.cbegin(), ch = check.cbegin(); i != vec.cend(); ++i, ++ch) {
    EXPECT_EQ(*ch, *i);
  }
}

TEST(Vector_test, insert_many_test4) {
  s21::Vector<int> vec;

  vec.insert_many(vec.begin(), 7, 8, 9);

  ASSERT_EQ(vec.size(), 3U);
  ASSERT_EQ(vec[0], 7);
  ASSERT_EQ(vec[1], 8);
  ASSERT_EQ(vec[2], 9);
}

TEST(Vector_test, insert_many_back_test) {
  s21::Vector<int> vec = {1, 2, 3, 4};
  s21::Vector<int> check = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  vec.insert_many_back(5, 6, 7, 8, 9);
  EXPECT_EQ(vec.size(), check.size());
  for (auto i = vec.cbegin(), ch = check.cbegin(); i != vec.cend(); ++i, ++ch) {
    EXPECT_EQ(*ch, *i);
  }
}

TEST(Vector_test, insert_many_back2) {
  s21::Vector<int> vec = {1, 2, 3, 4};
  s21::Vector<int> check = {1, 2, 3, 4, 5};
  vec.insert_many_back(5);
  EXPECT_EQ(vec.size(), check.size());
  for (auto i = vec.cbegin(), ch = check.cbegin(); i != vec.cend(); ++i, ++ch) {
    EXPECT_EQ(*ch, *i);
  }
}

TEST(Vector_test, insert_many_back3) {
  s21::Vector<int> vec;
  vec.insert_many_back(1, 2, 3, 4);
  int check = 1;
  for (auto i = 0U; i < vec.size(); ++i, ++check) {
    EXPECT_EQ(vec[i], check);
  }
}
