#include <gtest/gtest.h>

#include <list>
#include <stdexcept>
#include <type_traits>

#include "../containers/s21_list.h"

bool listsEqual(s21::list<int> L1, std::list<int> L2) {
  if (L1.size() != L2.size()) {
    return false;
  }
  s21::list<int>::iterator it_L1 = L1.begin();
  std::list<int>::iterator it_L2 = L2.begin();
  for (; it_L1 != L1.end(); ++it_L1, ++it_L2) {
    if (*it_L1 != *it_L2) {
      return false;
    }
  }
  return true;
}

TEST(CONSTRUCTORS, DEFAULT_CONSTRUCTOR) {
  s21::list<int> L1;
  std::list<int> L2;
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(CONSTRUCTORS, NSIZE_CONSTRUCTOR) {
  s21::list<int> L1(3);
  std::list<int> L2(3);
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(CONSTRUCTORS, LIST_CONSTRUCTOR) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(CONSTRUCTORS, COPY_CONSTRUCTOR) {
  s21::list<int> L1 = {1, 2, 3};
  s21::list<int> L2(L1);
  std::list<int> L3 = {1, 2, 3};
  std::list<int> L4(L3);
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(CONSTRUCTORS, MOVE_CONSTRUCTOR) {
  s21::list<int> L1 = {1, 2, 3};
  s21::list<int> L2(std::move(L1));
  std::list<int> L3 = {1, 2, 3};
  std::list<int> L4(std::move(L3));
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(METHOD_SIZE, SIZE_DEFAULT_CONTRUCTOR) {
  s21::list<int> L1;
  std::list<int> L2;
  ASSERT_EQ(L1.size(), L2.size());
}

TEST(METHOD_SIZE, SIZE_NSIZE_CONSTRUCTOR) {
  s21::list<int> L1(3);
  std::list<int> L2(3);
  ASSERT_EQ(L1.size(), L2.size());
}

TEST(METHOD_SIZE, SIZE_LIST_CONSTRUCTOR) {
  s21::list<int> L1 = {1, 2, 3, 4, 5};
  std::list<int> L2 = {1, 2, 3, 4, 5};
  ASSERT_EQ(L1.size(), L2.size());
}

TEST(METHOD_SIZE, SIZE_COPY_CONSTRUCTOR) {
  s21::list<int> L1 = {1, 2, 3, 4, 5, 6, 7};
  s21::list<int> L2(L1);
  std::list<int> L3 = {1, 2, 3, 4, 5, 6, 7};
  std::list<int> L4(L3);
  ASSERT_EQ(L2.size(), L4.size());
}

TEST(METHOD_SIZE, SIZE_MOVE_CONSTRUCTOR) {
  s21::list<int> L1 = {1, 2, 3, 4, 5};
  s21::list<int> L2(std::move(L1));
  std::list<int> L3 = {1, 2, 3, 4, 5};
  std::list<int> L4(std::move(L3));
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(METHOD_EMPTY, EMPTY_DEFAULT_CONSTRUCTOR) {
  s21::list<int> L1;
  std::list<int> L2;
  ASSERT_EQ(L1.empty(), L2.empty());
}

TEST(METHOD_EMPTY, EMPTY_NSIZE_CONSTRUCTOR) {
  s21::list<int> L1(1);
  std::list<int> L2(1);
  ASSERT_EQ(L1.empty(), L2.empty());

  s21::list<int> L3(0);
  std::list<int> L4(0);
  ASSERT_EQ(L3.empty(), L4.empty());

  s21::list<int> L5(0);
  std::list<int> L6(0);
  L5.push_back(0);
  L6.push_back(0);
  ASSERT_EQ(L5.empty(), L6.empty());
  L5.pop_front();
  L6.pop_front();
  ASSERT_EQ(L5.empty(), L6.empty());
}

TEST(METHOD_EMPTY, EMPTY_LIST_CONSTRUCTOR) {
  s21::list<int> L1 = {};
  std::list<int> L2 = {};
  ASSERT_EQ(L1.empty(), L2.empty());

  s21::list<int> L3 = {1};
  std::list<int> L4 = {1};
  ASSERT_EQ(L3.empty(), L4.empty());

  L1.push_back(1);
  L2.push_back(1);
  ASSERT_EQ(L1.empty(), L2.empty());
}

TEST(METHOD_EMPTY, EMPTY_COPY_CONSTRUCTOR) {
  s21::list<int> L1;
  s21::list<int> L2(L1);
  std::list<int> L3;
  std::list<int> L4(L3);
  ASSERT_EQ(L2.empty(), L4.empty());

  s21::list<int> L5 = {1};
  s21::list<int> L6(L5);
  std::list<int> L7 = {1};
  std::list<int> L8(L7);
  ASSERT_EQ(L6.empty(), L8.empty());
}

TEST(METHOD_EMPTY, EMPTY_MOVE_CONSTRUCTOR) {
  s21::list<int> L1;
  s21::list<int> L2(std::move(L1));
  std::list<int> L3;
  std::list<int> L4(std::move(L3));
  ASSERT_EQ(L1.empty(), L3.empty());
  ASSERT_EQ(L2.empty(), L4.empty());
}

TEST(METHOD_SWAP, SWAP_ONE_LIST_EMPTY1) {
  s21::list<int> L1 = {1, 2, 3};
  s21::list<int> L2 = {};
  std::list<int> L3 = {1, 2, 3};
  std::list<int> L4 = {};
  L1.swap(L2);
  L3.swap(L4);
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(METHOD_SWAP, SWAP_ONE_LIST_EMPTY2) {
  s21::list<int> L1 = {};
  s21::list<int> L2 = {4, 5, 6};
  std::list<int> L3 = {};
  std::list<int> L4 = {4, 5, 6};
  L1.swap(L2);
  L3.swap(L4);
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(METHOD_SWAP, SWAP_EMPTY_LISTS) {
  s21::list<int> L1 = {};
  s21::list<int> L2 = {};
  std::list<int> L3 = {};
  std::list<int> L4 = {};
  L1.swap(L2);
  L3.swap(L4);
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(METHOD_SWAP, SWAP_SAME_NUMBER_OF_ELEMENTS) {
  s21::list<int> L1 = {1, 2, 3};
  s21::list<int> L2 = {4, 5, 6};
  std::list<int> L3 = {1, 2, 3};
  std::list<int> L4 = {4, 5, 6};
  L1.swap(L2);
  L3.swap(L4);
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(METHOD_SWAP, SWAP_DIFFERENT_NUMBER_OF_ELEMENTS1) {
  s21::list<int> L1 = {1, 2, 3, 4, 5};
  s21::list<int> L2 = {4, 5, 6};
  std::list<int> L3 = {1, 2, 3, 4, 5};
  std::list<int> L4 = {4, 5, 6};
  L1.swap(L2);
  L3.swap(L4);
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(METHOD_SWAP, SWAP_DIFFERENT_NUMBER_OF_ELEMENTS2) {
  s21::list<int> L1 = {1, 2, 3};
  s21::list<int> L2 = {4, 5, 6, 128, 40};
  std::list<int> L3 = {1, 2, 3};
  std::list<int> L4 = {4, 5, 6, 128, 40};
  L1.swap(L2);
  L3.swap(L4);
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(METHOD_REVERSE, REVERSE_5_ELEMENTS) {
  s21::list<int> L1 = {1, 2, 3, 4, 5};
  std::list<int> L2 = {1, 2, 3, 4, 5};
  L1.reverse();
  L2.reverse();
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_REVERSE, REVERSE_4_ELEMENTS) {
  s21::list<int> L1 = {1, 2, 3, 4};
  std::list<int> L2 = {1, 2, 3, 4};
  L1.reverse();
  L2.reverse();
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_REVERSE, REVERSE_1_ELEMENTS) {
  s21::list<int> L1 = {1};
  std::list<int> L2 = {1};
  L1.reverse();
  L2.reverse();
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_REVERSE, REVERSE_0_ELEMENTS) {
  s21::list<int> L1 = {};
  std::list<int> L2 = {};
  L1.reverse();
  L2.reverse();
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_INSERT, INSERT_START_OF_THE_LIST_3_ELEMENTS) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::iterator it_L1 = L1.begin();
  std::list<int>::iterator it_L2 = L2.begin();
  L1.insert(it_L1, 128);
  L2.insert(it_L2, 128);
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_INSERT, INSERT_MIDDLE_OF_THE_LIST) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::iterator it_L1 = ++L1.begin();
  std::list<int>::iterator it_L2 = ++L2.begin();
  L1.insert(it_L1, 128);
  L2.insert(it_L2, 128);
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_INSERT, INSERT_START_OF_THE_LIST_1_ELEMENT) {
  s21::list<int> L1 = {1};
  std::list<int> L2 = {1};
  s21::list<int>::iterator it_L1 = L1.begin();
  std::list<int>::iterator it_L2 = L2.begin();
  L1.insert(it_L1, 128);
  L2.insert(it_L2, 128);
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_INSERT, INSERT_END_OF_THE_LIST) {
  s21::list<int> L1 = {1};
  std::list<int> L2 = {1};
  s21::list<int>::iterator it_L1 = L1.begin();
  std::list<int>::iterator it_L2 = L2.begin();
  ++it_L1;
  ++it_L2;
  L1.insert(it_L1, 128);
  L2.insert(it_L2, 128);
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_INSERT, INSERT_CYCLIC_SHIFT) {
  s21::list<int> L1 = {1};
  std::list<int> L2 = {1};
  s21::list<int>::iterator it_L1 = L1.begin();
  std::list<int>::iterator it_L2 = L2.begin();
  ++it_L1;
  ++it_L1;
  ++it_L2;
  ++it_L2;
  L1.insert(it_L1, 128);
  L2.insert(it_L2, 128);
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_INSERT, INSERT_EMPTY_LIST) {
  s21::list<int> L1 = {};
  std::list<int> L2 = {};
  s21::list<int>::iterator it_L1 = L1.begin();
  std::list<int>::iterator it_L2 = L2.begin();
  L1.insert(it_L1, 128);
  L2.insert(it_L2, 128);
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_MAX_SIZE, MAX_SIZE) {
  s21::list<int> L1;
  std::list<int> L2;
  EXPECT_EQ(L1.size(), L2.size());
  EXPECT_GT(L1.max_size(), 0);
}

TEST(METHOD_ERASE, ERASE_FIRST_ELEM) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::iterator it_L1 = L1.begin();
  std::list<int>::iterator it_L2 = L2.begin();
  L1.erase(it_L1);
  L2.erase(it_L2);
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_ERASE, ERASE_LAST_ELEM) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::iterator it_L1 = --L1.end();
  std::list<int>::iterator it_L2 = --L2.end();
  L1.erase(it_L1);
  L2.erase(it_L2);
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_ERASE, ERASE_MIDDLE_ELEM) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::iterator it_L1 = ++L1.begin();
  std::list<int>::iterator it_L2 = ++L2.begin();
  L1.erase(it_L1);
  L2.erase(it_L2);
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_SORT, SORT_1) {
  s21::list<int> L1 = {9, 2, 3, 1, 4};
  std::list<int> L2 = {9, 2, 3, 1, 4};
  L1.sort();
  L2.sort();
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_SORT, SORT_2) {
  s21::list<int> L1 = {1};
  std::list<int> L2 = {1};
  L1.sort();
  L2.sort();
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_SORT, SORT_3) {
  s21::list<int> L1 = {};
  std::list<int> L2 = {};
  L1.sort();
  L2.sort();
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_SORT, SORT_SORTED_LIST) {
  s21::list<int> L1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::list<int> L2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  L1.sort();
  L2.sort();
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_MERGE, MERGE_IDENTICAL_LISTS) {
  s21::list<int> L1 = {1, 2, 3, 4, 5};
  s21::list<int> L2 = {1, 2, 3, 4, 5};
  std::list<int> L3 = {1, 2, 3, 4, 5};
  std::list<int> L4 = {1, 2, 3, 4, 5};
  L1.merge(L2);
  L3.merge(L4);
  ASSERT_EQ(listsEqual(L1, L3), true);
}

TEST(METHOD_MERGE, MERGE_FIRST_LIST_REVERSE) {
  s21::list<int> L1 = {5, 4, 3, 2, 1};
  s21::list<int> L2 = {1, 2, 3, 4, 5};
  std::list<int> L3 = {5, 4, 3, 2, 1};
  std::list<int> L4 = {1, 2, 3, 4, 5};
  L1.merge(L2);
  L3.merge(L4);

  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(METHOD_MERGE, MERGE_SECOND_LIST_REVERSE) {
  s21::list<int> L1 = {1, 2, 3, 4, 5};
  s21::list<int> L2 = {5, 4, 3, 2, 1};
  std::list<int> L3 = {1, 2, 3, 4, 5};
  std::list<int> L4 = {5, 4, 3, 2, 1};
  L1.merge(L2);
  L3.merge(L4);
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(METHOD_MERGE, MERGE_FIRST_LIST_EMPTY) {
  s21::list<int> L1 = {};
  s21::list<int> L2 = {5, 4, 3, 2, 1};
  std::list<int> L3 = {};
  std::list<int> L4 = {5, 4, 3, 2, 1};
  L1.merge(L2);
  L3.merge(L4);
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(METHOD_MERGE, MERGE_SECOND_LIST_EMPTY) {
  s21::list<int> L1 = {1, 2, 3, 4, 5};
  s21::list<int> L2 = {};
  std::list<int> L3 = {1, 2, 3, 4, 5};
  std::list<int> L4 = {};
  L1.merge(L2);
  L3.merge(L4);
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(METHOD_MERGE, MERGE_SORTED_LISTS_1) {
  s21::list<int> L1 = {1, 2, 3, 4, 5};
  s21::list<int> L2 = {6, 7, 8, 9, 10};
  std::list<int> L3 = {1, 2, 3, 4, 5};
  std::list<int> L4 = {6, 7, 8, 9, 10};
  L1.merge(L2);
  L3.merge(L4);
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(METHOD_MERGE, MERGE_SORTED_LISTS_2) {
  s21::list<int> L1 = {1, 3, 5, 7};
  s21::list<int> L2 = {2, 4, 6, 8};
  std::list<int> L3 = {1, 3, 5, 7};
  std::list<int> L4 = {2, 4, 6, 8};
  L1.merge(L2);
  L3.merge(L4);
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(METHOD_UNIQUE, UNIQUE_SORTED_LIST) {
  s21::list<int> L1 = {1, 2, 2, 3, 3, 4, 5, 6, 7, 8, 9, 9, 10};
  std::list<int> L2 = {1, 2, 2, 3, 3, 4, 5, 6, 7, 8, 9, 9, 10};
  L1.unique();
  L2.unique();
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_UNIQUE, UNIQUE_UNSORTED_LIST) {
  s21::list<int> L1 = {1, 3, 3, 1, 1, 1, 5, 6, 128, 128, 4, 1, 1};
  std::list<int> L2 = {1, 3, 3, 1, 1, 1, 5, 6, 128, 128, 4, 1, 1};
  L1.unique();
  L2.unique();
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_UNIQUE, UNIQUE_EMPTY_LIST) {
  s21::list<int> L1 = {};
  std::list<int> L2 = {};
  L1.unique();
  L2.unique();
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_UNIQUE, UNIQUE_ONE_ELEM) {
  s21::list<int> L1 = {1};
  std::list<int> L2 = {1};
  L1.unique();
  L2.unique();
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_SPLICE, SPLICE_FIRST_ELEM) {
  s21::list<int> L1 = {1, 2, 3};
  s21::list<int> L2 = {4, 5, 6};
  std::list<int> empty_list = {};
  std::list<int> result = {4, 5, 6, 1, 2, 3};
  s21::list<int>::const_iterator it = L1.begin();
  L1.splice(it, L2);
  ASSERT_EQ(listsEqual(L1, result), true);
  ASSERT_EQ(listsEqual(L2, empty_list), true);
}

TEST(METHOD_SPLICE, SPLICE_SECOND_ELEM) {
  s21::list<int> L1 = {1, 2};
  s21::list<int> L2 = {4, 5, 6};
  std::list<int> empty_list = {};
  std::list<int> result = {1, 4, 5, 6, 2};
  s21::list<int>::const_iterator it = ++L1.begin();
  L1.splice(it, L2);
  ASSERT_EQ(listsEqual(L1, result), true);
  ASSERT_EQ(listsEqual(L2, empty_list), true);
}

TEST(METHOD_SPLICE, SPLICE_TO_EMPTY_LIST) {
  s21::list<int> L1 = {};
  s21::list<int> L2 = {4, 5, 6};
  std::list<int> empty_list = {};
  std::list<int> result = {4, 5, 6};
  s21::list<int>::const_iterator it = L1.begin();
  L1.splice(it, L2);
  ASSERT_EQ(listsEqual(L1, result), true);
  ASSERT_EQ(listsEqual(L2, empty_list), true);
}

TEST(METHOD_SPLICE, SPLICE_FROM_EMPTY_LIST) {
  s21::list<int> L1 = {1, 2, 3};
  s21::list<int> L2 = {};
  std::list<int> empty_list = {};
  std::list<int> result = {1, 2, 3};
  s21::list<int>::const_iterator it = L1.begin();
  L1.splice(it, L2);
  ASSERT_EQ(listsEqual(L1, result), true);
  ASSERT_EQ(listsEqual(L2, empty_list), true);
}

TEST(METHOD_FRONT, FRONT_EMPTY_LIST) {
  s21::list<int> L1;
  std::list<int> L2;
  ASSERT_EQ(L1.front(), L2.front());
}

TEST(METHOD_FRONT, FRONT_3_ELEMENTS) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  ASSERT_EQ(L1.front(), L2.front());
}

TEST(METHOD_BACK, BACK_EMPTY_LIST) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  ASSERT_EQ(L1.back(), L2.back());
}

TEST(METHOD_BACK, BACK_3_ELEMENTS) {
  s21::list<int> L1;
  std::list<int> L2;
  ASSERT_EQ(L1.back(), L2.back());
}

TEST(METHOD_PUSH_FRONT, PUSH_FRONT) {
  s21::list<int> L1;
  std::list<int> L2;
  L1.push_front(1);
  L2.push_front(1);
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_PUSH_BACK, PUSH_BACK) {
  s21::list<int> L1;
  std::list<int> L2;
  L1.push_back(1);
  L2.push_back(1);
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_POP_FRONT, POP_FRONT) {
  s21::list<int> L1 = {1};
  std::list<int> L2 = {1};
  L1.pop_front();
  L2.pop_front();
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(METHOD_POP_BACK, POP_BACK) {
  s21::list<int> L1 = {1};
  std::list<int> L2 = {1};
  L1.pop_back();
  L2.pop_back();
  ASSERT_EQ(listsEqual(L1, L2), true);
}

TEST(ITERATORS, PLUS_PLUS_OPERATOR) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::iterator it_L1 = ++L1.begin();
  std::list<int>::iterator it_L2 = ++L2.begin();
  ASSERT_EQ(*it_L1, *it_L2);
}

TEST(ITERATORS, OPERATOR_PLUS_PLUS) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::iterator it_L1 = L1.begin()++;
  std::list<int>::iterator it_L2 = L2.begin()++;
  ASSERT_EQ(*it_L1, *it_L2);
}

TEST(ITERATORS, OPERATOR_MINUS_MINUS) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::iterator it_L1 = L1.begin()--;
  std::list<int>::iterator it_L2 = L2.begin()--;
  ASSERT_EQ(*it_L1, *it_L2);
}

TEST(ITERATORS, DEREFERENCE_OPERATOR_EXISTING_LIST_1) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::iterator it_L1 = L1.begin();
  std::list<int>::iterator it_L2 = L2.begin();
  ASSERT_EQ(*it_L1, *it_L2);
}

TEST(ITERATORS, DEREFERENCE_OPERATOR_EXISTING_LIST_2) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::iterator it_L1 = L1.begin();
  std::list<int>::iterator it_L2 = L2.begin();
  *it_L1 = 128;
  *it_L2 = 128;
  ASSERT_EQ(*it_L1, *it_L2);
}

TEST(ITERATORS, DEREFERENCE_OPERATOR_NOT_EXISTING_LIST) {
  try {
    s21::list<int>::iterator it_L1;
    *it_L1;
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Invalid index");
  }
}

TEST(ITERATORS, NOT_EQUAL_OPERATOR) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  ASSERT_EQ(L1.begin() != L1.begin(), L2.begin() != L2.begin());
}

TEST(ITERATORS, EQUAL_OPERATOR) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  ASSERT_EQ(L1.begin() == L1.begin(), L2.begin() == L2.begin());
}

TEST(CONST_ITERATORS, PLUS_PLUS_OPERATOR) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::const_iterator it_L1 = ++L1.begin();
  std::list<int>::const_iterator it_L2 = ++L2.begin();
  ASSERT_EQ(*it_L1, *it_L2);
}

TEST(CONST_ITERATORS, OPERATOR_PLUS_PLUS) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::const_iterator it_L1 = L1.begin()++;
  std::list<int>::const_iterator it_L2 = L2.begin()++;
  ASSERT_EQ(*it_L1, *it_L2);
}

TEST(CONST_ITERATORS, OPERATOR_PLUS_PLUS_) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::const_iterator it_L1 = ++L1.begin();
  std::list<int>::const_iterator it_L2 = ++L2.begin();
  ASSERT_EQ(*it_L1, *it_L2);
}

TEST(CONST_ITERATORS, OPERATOR_MINUS_MINUS) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::const_iterator it_L1 = L1.begin()--;
  std::list<int>::const_iterator it_L2 = L2.begin()--;
  ASSERT_EQ(*it_L1, *it_L2);
}

TEST(CONST_ITERATORS, UNARY_OPERATORS) {
  s21::list<int> L1 = {1, 2, 3, 4, 5, 6};
  std::list<int> L2 = {1, 2, 3, 4, 5, 6};
  s21::list<int>::const_iterator it_L1 = L1.begin();
  std::list<int>::const_iterator it_L2 = L2.begin();
  s21::list<int>::const_iterator it_cpy = L1.begin();
  it_L1++;
  it_L2++;
  ASSERT_EQ(*it_L1, *it_L2);
  it_L1--;
  it_L2--;
  ASSERT_EQ(*it_L1, *it_L2);
  EXPECT_EQ(it_cpy == it_L1, true);
  it_L1 = it_L1 + 3;
  for (int i = 0; i < 3; ++i) {
    ++it_L2;
  }
  ASSERT_EQ(*it_L1, *it_L2);
  it_L1 = it_L1 - 3;
  for (int i = 0; i < 3; ++i) {
    --it_L2;
  }
  ASSERT_EQ(*it_L1, *it_L2);
}

TEST(CONST_ITERATORS, DEREFERENCE_OPERATOR_EXISTING_LIST) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::const_iterator it_L1 = L1.begin();
  std::list<int>::const_iterator it_L2 = L2.begin();
  ASSERT_EQ(*it_L1, *it_L2);
}

TEST(CONST_ITERATORS, DEREFERENCE_OPERATOR_NOT_EXISTING_LIST) {
  try {
    s21::list<int>::const_iterator it_L1;
    *it_L1;
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Invalid index");
  }
}

TEST(CONST_ITERATORS, NOT_EQUAL_OPERATOR) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  ASSERT_EQ(L1.begin() != L1.begin(), L2.begin() != L2.begin());
}

TEST(CONST_ITERATORS, EQUAL_OPERATOR) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  ASSERT_EQ(L1.begin() == L1.begin(), L2.begin() == L2.begin());
}

TEST(LIST, OPERATOR_EQUAL_COPY) {
  s21::list<int> L1 = {1, 2, 3};
  s21::list<int> L2 = {4, 5, 6};
  std::list<int> L3 = {1, 2, 3};
  std::list<int> L4 = {4, 5, 6};
  L1 = L2;
  L3 = L4;
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}

TEST(LIST, OPERATOR_EQUAL_CPY) {
  s21::list<int> L1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::list<int> L2 = {1, 2, 3};
  s21::list<int> L3 = {1, 2, 3, 4, 5, 6};
  std::list<int> std_L1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int> std_L2 = {1, 2, 3};
  std::list<int> std_L3 = {1, 2, 3, 4, 5, 6};
  L2 = L3;
  std_L2 = std_L3;
  ASSERT_EQ(listsEqual(L2, std_L2), true);
  L1 = L2;
  std_L1 = std_L2;
  ASSERT_EQ(listsEqual(L1, std_L1), true);
  ASSERT_EQ(listsEqual(L3, std_L3), true);
}

TEST(LIST, FRONT_BACK_CONST_METHODS) {
  const s21::list<int> L1 = {1, 2, 3, 4, 5};
  const std::list<int> L2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(L1.front(), L2.front());
  EXPECT_EQ(L1.back(), L2.back());
}

TEST(LIST, OPERATOR_EQUAL_MOVE) {
  s21::list<int> L1 = {1, 2, 3};
  s21::list<int> L2 = {4, 5, 6};
  std::list<int> L3 = {1, 2, 3};
  std::list<int> L4 = {4, 5, 6};
  L1 = std::move(L2);
  L3 = std::move(L4);
  ASSERT_EQ(listsEqual(L1, L3), true);
  ASSERT_EQ(listsEqual(L2, L4), true);
}
