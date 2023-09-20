#include <gtest/gtest.h>

#include <array>
#include <stdexcept>
#include <string>
#include <type_traits>

#include "../containers/s21_array.h"

class Array_test : public ::testing::Test {
 protected:
  void SetUp() override {}
  s21::Array<int, 5> s21_arr0_{1, 2, 3, 4, 5};
  const s21::Array<int, 5> s21_arr1_{1, 2, 3, 4, 5};
  s21::Array<std::string, 1> s21_arr2_{"hello"};

  std::array<int, 5> stl_arr0_{1, 2, 3, 4, 5};
  const std::array<int, 5> stl_arr1_{1, 2, 3, 4, 5};
  std::array<std::string, 1> stl_arr2_{"hello"};
};

void init_list_throw() { s21::Array<int, 3> ar = {1, 2, 3, 4}; }

TEST_F(Array_test, initializer_list_constructor) {
  auto stl = stl_arr0_.cbegin();
  for (auto s21 : s21_arr0_) {
    EXPECT_EQ(*stl++, s21);
  }
}

TEST_F(Array_test, initializer_list_constructor_throw) {
  ASSERT_THROW(init_list_throw(), std::out_of_range);
}

TEST_F(Array_test, copy_constructor) {
  s21::Array<int, 5> copied_arr(s21_arr1_);
  auto original = s21_arr1_.cbegin();
  for (auto copy : copied_arr) {
    EXPECT_EQ(*original++, copy);
  }
}

TEST_F(Array_test, move_constructor) {
  s21::Array<int, 4> original_arr;
  original_arr.fill(4);
  s21::Array<int, 4> copied_arr(std::move(original_arr));
  for (auto copy : copied_arr) {
    EXPECT_EQ(copy, 4);
  }
}

TEST_F(Array_test, at_test) { EXPECT_EQ(stl_arr0_.at(2), s21_arr0_.at(2)); }

TEST_F(Array_test, at_test_throw) {
  ASSERT_THROW(s21_arr0_.at(15), std::out_of_range);
}

TEST_F(Array_test, at_const_test) {
  const int s21 = s21_arr1_.at(0);
  const int stl = stl_arr1_.at(0);
  EXPECT_EQ(s21, stl);
}

TEST_F(Array_test, at_const_test_throw) {
  ASSERT_THROW(s21_arr1_.at(150), std::out_of_range);
}

TEST_F(Array_test, square_brackets) { EXPECT_EQ(stl_arr0_[0], s21_arr0_[0]); }

TEST_F(Array_test, const_square_brackets) {
  const int s21 = s21_arr1_[0];
  const int stl = stl_arr1_[0];
  EXPECT_EQ(s21, stl);
}

TEST_F(Array_test, front_test) {
  EXPECT_EQ(stl_arr0_.front(), s21_arr0_.front());
}

TEST_F(Array_test, const_front_test) {
  const int s21 = s21_arr1_.front();
  const int stl = stl_arr1_.front();
  EXPECT_EQ(s21, stl);
}

TEST_F(Array_test, back_test) { EXPECT_EQ(s21_arr0_.back(), stl_arr0_.back()); }

TEST_F(Array_test, const_back_test) {
  const int s21 = s21_arr1_.back();
  const int stl = stl_arr1_.back();
  EXPECT_EQ(s21, stl);
}

TEST_F(Array_test, data_test) {
  EXPECT_EQ(*s21_arr0_.data(), *stl_arr0_.data());
}

TEST_F(Array_test, const_data_test) {
  const int s21 = *s21_arr1_.data();
  const int stl = *stl_arr1_.data();
  EXPECT_EQ(s21, stl);
}

TEST_F(Array_test, begin_test) {
  EXPECT_EQ(*s21_arr0_.begin(), *stl_arr0_.begin());
}

TEST_F(Array_test, cbegin_test) {
  EXPECT_EQ(*s21_arr1_.cbegin(), *stl_arr1_.cbegin());
}

TEST_F(Array_test, end_test) {
  auto s21 = s21_arr0_.end();
  auto stl = stl_arr0_.end();
  --s21;
  --stl;
  EXPECT_EQ(*s21, *stl);
}

TEST_F(Array_test, cend_test) {
  auto s21 = s21_arr0_.cend();
  auto stl = stl_arr0_.cend();
  --s21;
  --stl;
  EXPECT_EQ(*s21, *stl);
}

TEST_F(Array_test, rbegin_test) {
  EXPECT_EQ(*s21_arr0_.rbegin(), *stl_arr0_.rbegin());
}

TEST_F(Array_test, crbegin_test) {
  EXPECT_EQ(*s21_arr1_.crbegin(), *stl_arr1_.crbegin());
}

TEST_F(Array_test, rend_test) {
  auto s21 = s21_arr0_.rend();
  auto stl = stl_arr0_.rend();
  --s21;
  --stl;
  EXPECT_EQ(*s21, *stl);
}

TEST_F(Array_test, crend_test) {
  auto s21 = s21_arr1_.crend();
  auto stl = s21_arr1_.crend();
  --s21;
  --stl;
  EXPECT_EQ(*s21, *stl);
}

TEST_F(Array_test, empty_false_test) { EXPECT_FALSE(s21_arr0_.empty()); }

TEST_F(Array_test, empty_true_test) {
  s21::Array<int, 0> ar;
  EXPECT_TRUE(ar.empty());
  EXPECT_TRUE(ar.data() == nullptr);
}

TEST_F(Array_test, size_test) { EXPECT_EQ(s21_arr1_.size(), stl_arr1_.size()); }

TEST_F(Array_test, max_size_test) {
  EXPECT_EQ(s21_arr0_.size(), stl_arr0_.size());
  EXPECT_GT(s21_arr0_.max_size(), 0);
}

TEST_F(Array_test, copy_assign_operator) {
  s21::Array<int, 5> ar;
  ar = s21_arr0_;
  auto original = s21_arr0_.cbegin();
  for (auto it : ar) {
    EXPECT_EQ(*original++, it);
  }
}

TEST_F(Array_test, move_assign_operator) {
  s21::Array<int, 3> original = {1, 1, 1};
  s21::Array<int, 3> copy;
  copy = std::move(original);
  for (auto it : copy) {
    EXPECT_EQ(it, 1);
  }
}

TEST_F(Array_test, eq_operator_true) {
  s21::Array<int, 5> copy;
  copy = s21_arr0_;
  EXPECT_TRUE(copy == s21_arr0_);
}

TEST_F(Array_test, eq_operator_false) {
  s21::Array<int, 5> ar = {5, 4, 3, 2, 1};
  EXPECT_FALSE(ar == s21_arr0_);
}

TEST_F(Array_test, neq_operator_true) {
  s21::Array<int, 5> ar = {5, 4, 3, 2, 1};
  EXPECT_TRUE(ar != s21_arr0_);
}

TEST_F(Array_test, neq_operator_false) {
  s21::Array<int, 5> ar;
  ar = s21_arr0_;
  EXPECT_FALSE(ar != s21_arr0_);
}

TEST_F(Array_test, less_than_true) {
  s21::Array<int, 5> ar = {1, 1, 1, 1, 1};
  std::array<int, 5> stl_ar = {1, 1, 1, 1, 1};
  bool s21 = (ar < s21_arr0_);
  bool stl = (stl_ar < stl_arr0_);
  EXPECT_TRUE(s21 == stl);
}

TEST_F(Array_test, less_than_false) {
  s21::Array<int, 5> s21_ar = {6, 7, 8, 9, 10};
  std::array<int, 5> stl_ar = {6, 7, 8, 9, 10};
  bool s21 = (s21_ar < s21_arr0_);
  bool stl = (stl_ar < stl_arr0_);
  EXPECT_TRUE(s21 == stl);
}

TEST_F(Array_test, less_or_eq_true) {
  s21::Array<int, 5> ar = {1, 1, 1, 1, 1};
  std::array<int, 5> stl_ar = {1, 1, 1, 1, 1};
  bool s21 = (ar <= s21_arr0_);
  bool stl = (stl_ar <= stl_arr0_);
  EXPECT_TRUE(s21 == stl);
}

TEST_F(Array_test, less_or_eq_true2) {
  s21::Array<int, 5> ar = {1, 2, 3, 4, 5};
  std::array<int, 5> stl_ar = {1, 2, 3, 4, 5};
  bool s21 = (ar <= s21_arr0_);
  bool stl = (stl_ar <= stl_arr0_);
  EXPECT_TRUE(s21 == stl);
}

TEST_F(Array_test, less_or_eq_false) {
  s21::Array<int, 5> s21_ar = {6, 7, 8, 9, 10};
  std::array<int, 5> stl_ar = {6, 7, 8, 9, 10};
  bool s21 = (s21_ar <= s21_arr0_);
  bool stl = (stl_ar <= stl_arr0_);
  EXPECT_TRUE(s21 == stl);
}

TEST_F(Array_test, greater_than_true) {
  s21::Array<int, 5> s21_ar = {5, 6, 7, 8, 9};
  std::array<int, 5> stl_ar = {5, 6, 7, 8, 9};
  bool s21 = (s21_ar > s21_arr0_);
  bool stl = (stl_ar > stl_arr0_);
  EXPECT_TRUE(s21 == stl);
}

TEST_F(Array_test, greater_than_false) {
  s21::Array<int, 5> s21_ar = {1, 2, 3, 4, 5};
  std::array<int, 5> stl_ar = {1, 2, 3, 4, 5};
  bool s21 = (s21_ar > s21_arr0_);
  bool stl = (stl_ar > stl_arr0_);
  EXPECT_TRUE(s21 == stl);
}

TEST_F(Array_test, greater_or_eq_true) {
  s21::Array<int, 5> s21_ar = {5, 6, 7, 8, 9};
  std::array<int, 5> stl_ar = {5, 6, 7, 8, 9};
  bool s21 = (s21_ar >= s21_arr0_);
  bool stl = (stl_ar >= stl_arr0_);
  EXPECT_TRUE(s21 == stl);
}

TEST_F(Array_test, greater_or_eq_true2) {
  s21::Array<int, 5> s21_ar = {1, 2, 3, 4, 5};
  std::array<int, 5> stl_ar = {1, 2, 3, 4, 5};
  bool s21 = (s21_ar >= s21_arr0_);
  bool stl = (stl_ar >= stl_arr0_);
  EXPECT_TRUE(s21 == stl);
}

TEST_F(Array_test, greater_or_eq_false) {
  s21::Array<int, 5> s21_ar = {1, 1, 1, 1, 1};
  std::array<int, 5> stl_ar = {1, 1, 1, 1, 1};
  bool s21 = (s21_ar >= s21_arr0_);
  bool stl = (stl_ar >= stl_arr0_);
  EXPECT_TRUE(s21 == stl);
}
