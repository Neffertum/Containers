#include <gtest/gtest.h>

#include <map>
#include <stdexcept>
#include <string>
#include <type_traits>

#include "../containers/s21_map.h"

namespace {
TEST(TestingMap, Map) {
  s21::map<int, std::string> tmp;
  s21::map<int, std::string> tmp2;
  tmp2.insert({1, "aboba"});
  tmp2.insert({7, "tmp2"});
  tmp2.insert({8, "tmp2"});
  tmp2.insert({5, "aboba"});
  tmp2.insert({9, "tmp2"});
  tmp2.insert({12, "tmp2"});
  tmp.insert({1, "first"});
  tmp.insert({2, "second"});
  tmp.insert({3, "third"});
  tmp.insert({4, "fourth"});
  tmp.insert({5, "fifth"});
  tmp.insert({6, "sixth"});
  tmp.insert({10, "ten"});
  tmp.insert({11, "eleven"});
  tmp.merge(tmp2);
  s21::map<int, std::string> tmp3 = tmp;
  auto it_tmp = tmp.begin();
  auto it_tmp3 = tmp3.begin();
  for (; it_tmp != tmp.end(); ++it_tmp3, ++it_tmp) {
    EXPECT_EQ((*it_tmp3).first, (*it_tmp).first);
  }
}
TEST(Map, Constructor_Default) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map, Constructor_Initializer_list) {
  s21::map<int, std::string> s21_map = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  std::map<int, std::string> std_map = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map, Constructor_Copy) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  std::map<int, std::string> std_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  s21::map<int, std::string> s21_map_2 = s21_map_1;
  std::map<int, std::string> std_map_2 = std_map_1;

  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
  EXPECT_EQ(std_map_1.size(), std_map_2.size());
  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Map, Constructor_Move) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  std::map<int, std::string> std_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  s21::map<int, std::string> s21_map_2 = std::move(s21_map_1);
  std::map<int, std::string> std_map_2 = std::move(std_map_1);

  EXPECT_EQ(s21_map_2.size(), std_map_2.size());
  EXPECT_EQ(s21_map_1.size(), std_map_1.size());
  EXPECT_EQ(s21_map_1.empty(), std_map_1.empty());
  auto it1 = s21_map_2.begin();
  auto it2 = std_map_2.begin();
  while (it1 != s21_map_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Map, Modifier_Insert) {
  s21::map<char, int> s21_map_1 = {{'b', 228}, {'c', 1337}};
  s21::map<char, int> s21_map_2 = {
      {'b', 228},
      {'c', 1337},
      {'d', 322},
      {'a', 5},
  };

  EXPECT_EQ(s21_map_1.insert('d', 322).second, true);
  EXPECT_EQ(s21_map_1.insert('d', 14).second, false);

  std::pair<char, int> pair1('a', 5);
  std::pair<char, int> pair2('a', 28);

  EXPECT_EQ(s21_map_1.insert(pair1).second, true);
  EXPECT_EQ(s21_map_1.insert(pair2).second, false);

  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
}

TEST(Map, Rehash_And_Insert_In_Collision) {
  s21::map<std::string, int> s21_map;
  s21_map.insert("asd", 0);
  s21_map.insert("asa", 1);
  s21_map.insert("asf", 2);
  s21_map.insert("asg", 3);
  s21_map.insert("ash", 4);
  s21_map.insert("aqw", 5);
  s21_map.insert("fgh", 6);
  s21_map.insert("ghf", 7);
  s21_map.insert("dghfg", 8);
  s21_map.insert("dghfdsg", 9);
  s21_map.insert("dghfgfsadfsd", 10);
  s21_map.insert("dghfgfsadfsdasd", 11);
  s21_map.insert("dghfgfsadfsasdasdd", 12);
  s21_map.insert("dghfgfsadfsdasdasd", 13);
  s21_map.insert("dghfgfdsasadfdsasasdsadsad", 14);
  s21_map.insert("dghdsafgfsadfdsasasdsadsad", 15);
  s21_map.insert("ådsdghfgfsadfdsasasdsadsad", 16);
  s21_map.insert("dghfgfsadfdsasasdsaddsasad", 17);
  s21_map.insert("dghfgfsadfdsasassadadsadsad", 18);
  s21_map.insert("dghfgfsadfdsasdasasdsadsad", 19);
  s21_map.insert("dghasdaasdfgfsadfsasdsadsad", 20);
  s21_map.insert("asddghfgfsadfsasaß∂asdsadsad", 21);
  s21_map.insert("dghfgfsadfasdsasdsadsad", 22);
  s21_map.insert("dghfgfsadfsasdsadsad", 23);
  s21_map.insert("dghfgfsasdadfsasdsadsad", 24);
  s21_map.insert("asdsadadghfgfsadfsasdsadsad", 25);
  std::map<std::string, int> std_map;
  std_map.insert(std::pair<std::string, int>("asd", 0));
  std_map.insert(std::pair<std::string, int>("asa", 1));
  std_map.insert(std::pair<std::string, int>("asf", 2));
  std_map.insert(std::pair<std::string, int>("asg", 3));
  std_map.insert(std::pair<std::string, int>("ash", 4));
  std_map.insert(std::pair<std::string, int>("aqw", 5));
  std_map.insert(std::pair<std::string, int>("fgh", 6));
  std_map.insert(std::pair<std::string, int>("ghf", 7));
  std_map.insert(std::pair<std::string, int>("dghfg", 8));
  std_map.insert(std::pair<std::string, int>("dghfdsg", 9));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsd", 10));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsdasd", 11));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsasdasdd", 12));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsdasdasd", 13));
  std_map.insert(std::pair<std::string, int>("dghfgfdsasadfdsasasdsadsad", 14));
  std_map.insert(std::pair<std::string, int>("dghdsafgfsadfdsasasdsadsad", 15));
  std_map.insert(std::pair<std::string, int>("ådsdghfgfsadfdsasasdsadsad", 16));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfdsasasdsaddsasad", 17));
  std_map.insert(
      std::pair<std::string, int>("dghfgfsadfdsasassadadsadsad", 18));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfdsasdasasdsadsad", 19));
  std_map.insert(
      std::pair<std::string, int>("dghasdaasdfgfsadfsasdsadsad", 20));
  std_map.insert(
      std::pair<std::string, int>("asddghfgfsadfsasaß∂asdsadsad", 21));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfasdsasdsadsad", 22));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsasdsadsad", 23));
  std_map.insert(std::pair<std::string, int>("dghfgfsasdadfsasdsadsad", 24));
  std_map.insert(
      std::pair<std::string, int>("asdsadadghfgfsadfsasdsadsad", 25));
  for (auto i : std_map) {
    EXPECT_EQ(i.second, s21_map[i.first]);
  }
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(Map, Modifier_Get_Value) {
  s21::map<std::string, int> m;
  m["123"] = 5;
  EXPECT_EQ(5, m["123"]);
}

TEST(Map, Const_Map_Test) {
  const s21::map<int, char> M1 = {
      {3, 'c'}, {1, 'a'}, {2, 'b'}, {4, 'd'}, {5, 'e'}};
  const std::map<int, char> M2 = {
      {3, 'c'}, {1, 'a'}, {2, 'b'}, {4, 'd'}, {5, 'e'}};

  EXPECT_EQ(M1.at(4), M2.at(4));
  auto og_it = M2.begin();
  for (auto it = M1.begin(); it != M1.end(); ++it, ++og_it) {
    EXPECT_EQ(*it, *og_it);
  }
}

TEST(Map, Modifier_Insert_or_assign) {
  s21::map<char, int> s21_map_1 = {{'b', 228}, {'c', 1337}};
  s21::map<char, int> s21_map_2 = {
      {'b', 228},
      {'c', 1337},
      {'d', 14},
      {'a', 28},
  };

  EXPECT_EQ(s21_map_1.insert_or_assign('d', 322).second, true);
  EXPECT_EQ(s21_map_1.insert_or_assign('d', 14).second, false);

  EXPECT_EQ(s21_map_1.insert_or_assign('a', 5).second, true);
  EXPECT_EQ(s21_map_1.insert_or_assign('a', 28).second, false);

  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
}

TEST(Map, Modifier_Erase_1) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  s21::map<int, std::string> s21_map_2 = {
      {1, "aboba"}, {3, "amogus"}, {4, "abobus"}};
  auto it = s21_map_1.begin();
  ++it;
  s21_map_1.erase(it);
  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
}

TEST(Map, Modifier_Erase_2) {
  s21::map<int, std::string> s21_map = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  for (auto it = s21_map.begin(); it != s21_map.end();) {
    auto tmp_it = it;
    ++tmp_it;
    s21_map.erase(it);
    it = tmp_it;
  }

  s21_map.erase(s21_map.end());
  EXPECT_EQ(s21_map.empty(), true);
  EXPECT_EQ(s21_map.size(), size_t(0));

  s21_map.insert(1, "aboba");

  EXPECT_EQ(s21_map.empty(), false);
  EXPECT_EQ(s21_map.size(), size_t(1));
  EXPECT_EQ(s21_map.contains(1), true);
}

TEST(Map, Modifier_Swap) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  s21::map<int, std::string> s21_map_2 = {
      {10, "shtirlits"}, {12, "vovochka"}, {13, "poruchik"}, {14, "chepaev"}};
  s21::map<int, std::string> s21_map_3 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  s21::map<int, std::string> s21_map_4 = {
      {10, "shtirlits"}, {12, "vovochka"}, {13, "poruchik"}, {14, "chepaev"}};

  s21_map_1.swap(s21_map_2);
  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  auto it3 = s21_map_3.begin();
  auto it4 = s21_map_4.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_map_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_4.size());
  EXPECT_EQ(s21_map_2.size(), s21_map_3.size());
}

TEST(Map, Modifier_Mem_Merge) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "diksi"}, {2, "podval so zmeyami"}, {3, "introvskie klouny"}};
  s21::map<int, std::string> s21_map_2 = {
      {3, "introvskie klouny"}, {4, "sbebr platforma"}, {5, "avito"}};
  s21::map<int, std::string> s21_map_3 = {{1, "diksi"},
                                          {2, "podval so zmeyami"},
                                          {3, "introvskie klouny"},
                                          {4, "sbebr platforma"},
                                          {5, "avito"}};
  s21_map_1.merge(s21_map_2);
  auto it1 = s21_map_1.begin();
  auto it3 = s21_map_3.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it3);
    ++it1, ++it3;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_3.size());
}

TEST(Map, Lookup_Contains) {
  s21::map<int, std::string> s21_map;
  s21_map.insert(1, "salamandry");
  s21_map.insert(2, "medoedy");
  s21_map.insert(3, "kapibary");
  s21_map.insert(4, "alpaki");
  EXPECT_EQ(s21_map.contains(1), true);
  EXPECT_EQ(s21_map.contains(2), true);
  EXPECT_EQ(s21_map.contains(3), true);
  EXPECT_EQ(s21_map.contains(4), true);
  EXPECT_EQ(s21_map.contains(7), false);
  EXPECT_EQ(s21_map.contains(-2), false);
  EXPECT_EQ(s21_map.contains(0), false);
}

}  // namespace

bool mapsEqual(s21::map<int, char> M1, std::map<int, char> M2) {
  if (M1.size() != M2.size()) return false;
  s21::map<int, char>::iterator it_M1 = M1.begin();
  std::map<int, char>::iterator it_M2 = M2.begin();
  for (; it_M2 != M2.end(); ++it_M1, ++it_M2) {
    if (*it_M1 != *it_M2) return false;
  }
  return true;
}

TEST(MAP_CONSTRUCTORS, MAP_DEFAULT_CONSTRUCTOR) {
  s21::map<int, char> M1;
  std::map<int, char> M2;
  ASSERT_EQ(mapsEqual(M1, M2), true);
}

TEST(MAP_CONSTRUCTORS, MAP_LIST_CONSTRUCTOR) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  ASSERT_EQ(mapsEqual(M1, M2), true);
}

TEST(MAP_CONSTRUCTORS, MAP_COPY_CONSTRUCTOR) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> M2(M1);
  std::map<int, char> M3 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M4(M3);
  ASSERT_EQ(mapsEqual(M2, M4), true);
  ASSERT_EQ(mapsEqual(M1, M3), true);
}

TEST(MAP_CONSTRUCTORS, MAP_MOVE_CONSTRUCTOR) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> M2(std::move(M1));
  std::map<int, char> M3 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M4(std::move(M3));
  ASSERT_EQ(mapsEqual(M2, M4), true);
  ASSERT_EQ(mapsEqual(M1, M3), true);
}

TEST(MAP_METHOD_AT, MAP_AT_IN_BOUNDS1) {
  s21::map<int, char> M1 = {{3, 'a'}, {2, 'b'}, {1, 'c'}};
  std::map<int, char> M2 = {{3, 'a'}, {2, 'b'}, {1, 'c'}};
  ASSERT_EQ(M1.at(2), M2.at(2));
}

TEST(MAP_METHOD_AT, MAP_AT_IN_BOUNDS2) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  ASSERT_EQ(M1.at(2), M2.at(2));
}

TEST(MAP_METHOD_AT, MAP_AT_OUT_OF_BOUNDS) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  ASSERT_THROW(M2.at(36), std::out_of_range);
  ASSERT_THROW(M1.at(36), std::out_of_range);
}

TEST(MAP_METHOD_AT, MAP_AT_ENTERING_VALUE) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  M1.at(2) = 'q';
  M2.at(2) = 'q';
  ASSERT_EQ(mapsEqual(M1, M2), true);
}

TEST(MAP_METHOD_EMPTY, MAP_EMPTY_DEFAULT_CONSTRUCTOR) {
  s21::map<int, char> M1;
  std::map<int, char> M2;
  ASSERT_EQ(M1.empty(), M2.empty());
}

TEST(MAP_METHOD_EMPTY, MAP_EMPTY_LIST_CONSTRUCTOR) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  ASSERT_EQ(M1.empty(), M2.empty());
  s21::map<int, char> M3 = {};
  std::map<int, char> M4 = {};
  ASSERT_EQ(M3.empty(), M4.empty());
  s21::map<int, char> M5 = {{1, 'a'}};
  std::map<int, char> M6 = {{1, 'a'}};
  ASSERT_EQ(M5.empty(), M6.empty());
}

TEST(MAP_METHOD_EMPTY, MAP_EMPTY_COPY_CONSTRUCTOR) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> M2(M1);
  std::map<int, char> M3 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M4(M3);
  ASSERT_EQ(M1.empty(), M3.empty());
  ASSERT_EQ(M2.empty(), M4.empty());
  s21::map<int, char> M5;
  s21::map<int, char> M6(M5);
  std::map<int, char> M7;
  std::map<int, char> M8(M7);
  ASSERT_EQ(M5.empty(), M7.empty());
  ASSERT_EQ(M6.empty(), M8.empty());
}

TEST(MAP_METHOD_EMPTY, MAP_EMPTY_MOVE_CONSTRUCTOR) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> M2(std::move(M1));
  std::map<int, char> M3 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M4(std::move(M3));
  ASSERT_EQ(M1.empty(), M3.empty());
  ASSERT_EQ(M2.empty(), M4.empty());
  s21::map<int, char> M5;
  s21::map<int, char> M6(std::move(M5));
  std::map<int, char> M7;
  std::map<int, char> M8(std::move(M7));
  ASSERT_EQ(M5.empty(), M7.empty());
  ASSERT_EQ(M6.empty(), M8.empty());
}

TEST(MAP_METHOD_SIZE, MAP_SIZE_DEFAULT_CONSTRUCTOR) {
  s21::map<int, char> M1;
  std::map<int, char> M2;
  ASSERT_EQ(M1.size(), M2.size());
}

TEST(MAP_METHOD_SIZE, MAP_SIZE_LIST_CONSTRUCTOR) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  ASSERT_EQ(M1.size(), M2.size());
}

TEST(MAP_METHOD_SIZE, MAP_SIZE_COPY_CONSTRUCTOR) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> M2(M1);
  std::map<int, char> M3 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M4(M3);
  ASSERT_EQ(M1.size(), M3.size());
  ASSERT_EQ(M2.size(), M4.size());
}

TEST(MAP_METHOD_SIZE, MAP_SIZE_MOVE_CONSTRUCTOR) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> M2(std::move(M1));
  std::map<int, char> M3 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M4(std::move(M3));
  ASSERT_EQ(M1.size(), M3.size());
  ASSERT_EQ(M2.size(), M4.size());
}

TEST(MAP_METHOD_MAX_SIZE, MAP_MAX_SIZE) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_EQ(M1.size(), M2.size());
  EXPECT_GT(M1.max_size(), 0);
}

TEST(MAP_METHOD_CLEAR, MAP_CLEAR) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  M1.clear();
  M2.clear();
  ASSERT_EQ(mapsEqual(M1, M2), true);
}

TEST(MAP_METHOD_INSERT, MAP_INSERT_BY_PAIR_EXISTING_ELEMENT) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  M1.insert(std::pair<int, char>(3, 'c'));
  M2.insert(std::pair<int, char>(3, 'c'));
  ASSERT_EQ(mapsEqual(M1, M2), true);
}

TEST(MAP_METHOD_INSERT, MAP_INSERT_BY_VALUE_SEPARATED_EXISTING_ELEMENT) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  M1.insert(3, 'c');
  M2.insert(std::pair<int, char>(3, 'c'));
  ASSERT_EQ(mapsEqual(M1, M2), true);
}

TEST(MAP_METHOD_INSERT, MAP_INSERT_0_ELEMENTS) {
  s21::map<int, char> M1 = {};
  std::map<int, char> M2 = {};
  M1.insert(std::pair<int, char>(3, 'c'));
  M2.insert(std::pair<int, char>(3, 'c'));
  ASSERT_EQ(mapsEqual(M1, M2), true);
}

TEST(MAP_METHOD_INSERT, MAP_INSERT_MIDDLE_ELEMENT) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {4, 'd'}};
  std::map<int, char> M2 = {{1, 'a'}, {2, 'b'}, {4, 'd'}};
  M1.insert(std::pair<int, char>(3, 'c'));
  M2.insert(std::pair<int, char>(3, 'c'));
  ASSERT_EQ(mapsEqual(M1, M2), true);
}

TEST(MAP_METHOD_INSERT_OR_ASSIGN, MAP_INSERT_MIDDLE_ELEMENT_DOES_NOT_CONTAIN) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {4, 'd'}};
  auto res = M1.insert_or_assign(3, 'c');

  ASSERT_EQ(res.second, true);
}

TEST(MAP_METHOD_INSERT_OR_ASSIGN, MAP_INSERT_MIDDLE_ELEMENT_CONTAINS) {
  s21::map<int, char> M1 = {{1, 'a'}, {3, 'c'}, {4, 'd'}};
  auto res = M1.insert_or_assign(3, 'c');
  ASSERT_EQ(res.second, false);
}

TEST(MAP_METHOD_ERASE, MAP_ERASE_NO_CHILD) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char>::iterator it_M1 = M1.begin();
  std::map<int, char>::iterator it_M2 = M2.begin();
  M1.erase(it_M1);
  M2.erase(it_M2);
  ASSERT_EQ(mapsEqual(M1, M2), true);
}
// aboba
struct EraseTest : testing::Test {
  s21::map<int, int> EraseMap = {
      {20, 1},  {25, 1},  {10, 1},  {4, 1},   {16, 1},  {23, 1},  {30, 1},
      {14, 1},  {17, 1},  {19, 1},  {12, 1},  {15, 1},  {11, 1},  {2, 1},
      {5, 1},   {3, 1},   {35, 1},  {40, 1},  {45, 1},  {50, 1},  {55, 1},
      {60, 1},  {65, 1},  {70, 1},  {75, 1},  {80, 1},  {85, 1},  {90, 1},
      {95, 1},  {100, 1}, {105, 1}, {110, 1}, {115, 1}, {120, 1}, {125, 1},
      {130, 1}, {135, 1}, {140, 1}, {145, 1}, {150, 1}, {155, 1}};
};
// родитель красный, другой ребёнок чёрный с чёрными внуками
TEST_F(EraseTest, RED_PARENT_BLACK_CHILD_BLACK_GRAND) {
  auto it = EraseMap.find(30);
  EraseMap.erase(it);
  EXPECT_EQ(EraseMap.contains(30), false);
}

// родитель красный, левый ребёнок чёрный с левым красным внуком.
TEST_F(EraseTest, RED_PARENT_BLACK_CHILD_LEFT_RED_GRAND) {
  auto it = EraseMap.find(15);
  EraseMap.erase(it);
  EXPECT_EQ(EraseMap.contains(15), false);
}

TEST_F(EraseTest, RED_PARENT_BLACK_CHILD_RIGHT_RED_GRAND) {
  auto it = EraseMap.find(140);
  EraseMap.erase(it);
  EXPECT_EQ(EraseMap.contains(140), false);
}
// родитель чёрный, левый сын красный, у правого внука чёрные правнуки
TEST_F(EraseTest, RED_PARENT_RED_CHILD_RIGHT_BLACK_GRAND) {
  auto it = EraseMap.find(130);
  EraseMap.erase(it);
  EXPECT_EQ(EraseMap.contains(130), false);
}
TEST_F(EraseTest, RED_PARENT_RED_CHILD_RIGHT_RED_GRAND) {
  EraseMap.insert({142, 1});
  auto it = EraseMap.find(130);
  EraseMap.erase(it);
  EXPECT_EQ(EraseMap.contains(130), false);
}
TEST_F(EraseTest, MAP_RED_PARENT_BLACK_BROTHER) {
  auto it = EraseMap.find(11);
  EraseMap.erase(it);
  it = EraseMap.find(15);
  EraseMap.erase(it);
  EXPECT_EQ(EraseMap.contains(15), false);
}
TEST_F(EraseTest, MAP_BLACK_PARENT_BLACK_BROTHER) {
  auto it = EraseMap.find(30);
  auto it_tmp = it;
  --it_tmp;
  --it_tmp;
  EraseMap.erase(it);
  it = it_tmp;
  ++it_tmp;
  EraseMap.erase(it);
  EraseMap.erase(it_tmp);
  EXPECT_EQ(EraseMap.contains(25), false);
}

TEST(MAP_METHOD_ERASE, MAP_ERASE_TWO_CHILDREN) {
  s21::map<int, char> M1 = {{3, 'c'}, {1, 'a'}, {2, 'b'}, {4, 'd'}, {5, 'e'}};
  std::map<int, char> M2 = {{3, 'c'}, {1, 'a'}, {2, 'b'}, {4, 'd'}, {5, 'e'}};
  s21::map<int, char>::iterator it_M1 = ++M1.begin();
  std::map<int, char>::iterator it_M2 = ++M2.begin();
  ++it_M1;
  ++it_M2;
  M1.erase(it_M1);
  M2.erase(it_M2);
  ASSERT_EQ(mapsEqual(M1, M2), true);
}

TEST(MAP_METHOD_SWAP, MAP_SWAP_ONE_LIST_EMPTY1) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> M2 = {};
  std::map<int, char> M3 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M4 = {};
  M1.swap(M2);
  M3.swap(M4);
  ASSERT_EQ(mapsEqual(M1, M3), true);
  ASSERT_EQ(mapsEqual(M2, M4), true);
}

TEST(MAP_METHOD_SWAP, MAP_SWAP_ONE_LIST_EMPTY2) {
  s21::map<int, char> M1 = {};
  s21::map<int, char> M2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M3 = {};
  std::map<int, char> M4 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  M1.swap(M2);
  M3.swap(M4);
  ASSERT_EQ(mapsEqual(M1, M3), true);
  ASSERT_EQ(mapsEqual(M2, M4), true);
}

TEST(MAP_METHOD_SWAP, MAP_SWAP_NUMBER_OF_ELEMENTS) {
  s21::map<int, char> M1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> M2 = {{4, 'd'}, {5, 'e'}, {6, 'f'}};
  std::map<int, char> M3 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> M4 = {{4, 'd'}, {5, 'e'}, {6, 'f'}};
  M1.swap(M2);
  M3.swap(M4);
  ASSERT_EQ(mapsEqual(M1, M3), true);
  ASSERT_EQ(mapsEqual(M2, M4), true);
}

TEST(MAP_METHOD_MERGE, MAP_MERGE_DIFFERENT_ELEMENTS) {
  s21::map<int, char> M1 = {{1, 'a'}, {3, 'c'}, {5, 'e'}};
  s21::map<int, char> M2 = {{2, 'b'}, {4, 'd'}, {6, 'f'}};
  std::map<int, char> M3 = {{1, 'a'}, {3, 'c'}, {5, 'e'},
                            {2, 'b'}, {4, 'd'}, {6, 'f'}};
  std::map<int, char> empty;
  M1.merge(M2);
  ASSERT_EQ(mapsEqual(M1, M3), true);
  ASSERT_EQ(mapsEqual(M2, empty), true);
}

TEST(MAP_METHOD_CONTAINS, MAP_CONTAINS_EXISTING_ELEMENT) {
  s21::map<int, char> M1 = {{50, 'a'}, {25, 'b'}, {75, 'c'},
                            {10, 'd'}, {40, 'e'}, {51, 'f'}};
  EXPECT_EQ(M1.contains(10), true);
}

TEST(MAP_OPERATOR_OVERLOADS, MAP_OPERATOR_ASSIGNMENT_COPY_SAME_SET) {
  s21::map<int, char> M;
  s21::map<int, char> M1 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  std::map<int, char> M2 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  M = M1;
  ASSERT_EQ(mapsEqual(M, M2), true);
}

TEST(MAP_OPERATOR_OVERLOADS, MAP_OPERATOR_ASSIGNMENT_COPY) {
  s21::map<int, char> M1 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  s21::map<int, char> M2 = {{10, 'q'}, {20, 'w'}, {30, 'e'}, {40, 'r'}};
  std::map<int, char> M3 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  std::map<int, char> M4 = {{10, 'q'}, {20, 'w'}, {30, 'e'}, {40, 'r'}};
  M1 = M2;
  M3 = M4;
  ASSERT_EQ(mapsEqual(M1, M3), true);
  ASSERT_EQ(mapsEqual(M2, M4), true);
}

TEST(MAP_OPERATOR_OVERLOADS, MAP_OPERATOR_ASSIGNMENT_MOVE_SAME_SET) {
  s21::map<int, char> M;
  s21::map<int, char> M1 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  std::map<int, char> M2 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  M = std::move(M1);
  // M2 = std::move(M2);
  ASSERT_EQ(mapsEqual(M, M2), true);
}

TEST(MAP_OPERATOR_OVERLOADS, MAP_OPERATOR_ACCESS) {
  s21::map<int, char> M1 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  std::map<int, char> M2 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  ASSERT_EQ(M1[75], M2[75]);
}

TEST(MAP_OPERATOR_OVERLOADS, MAP_OPERATOR_INSERT) {
  s21::map<int, char> M1 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  std::map<int, char> M2 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  ASSERT_EQ(mapsEqual(M1, M2), true);
}

TEST(MAP_ITERATORS, MAP_PLUS_PLUS_OPERATOR) {
  s21::map<int, char> M1 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  std::map<int, char> M2 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  s21::map<int, char>::iterator it_M1 = ++M1.begin();
  std::map<int, char>::iterator it_M2 = ++M2.begin();
  ASSERT_EQ((*it_M1).first, (*it_M2).first);
  ASSERT_EQ((*it_M1).second, (*it_M2).second);
}

TEST(MAP_ITERATORS, CONST_ITERATOR) {
  const s21::map<int, char> M1 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  const std::map<int, char> M2 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  s21::map<int, char>::const_iterator it_M1 = ++M1.begin();
  auto it_M2 = ++M2.begin();
  ASSERT_EQ((*it_M1).first, (*it_M2).first);
  ASSERT_EQ((*it_M1).second, (*it_M2).second);
  it_M1++;
  it_M2++;
  ASSERT_EQ((*it_M1).first, (*it_M2).first);
  ASSERT_EQ((*it_M1).second, (*it_M2).second);
  it_M1--;
  it_M2--;
  ASSERT_EQ((*it_M1).first, (*it_M2).first);
  ASSERT_EQ((*it_M1).second, (*it_M2).second);
  --it_M1;
  --it_M2;
  ASSERT_EQ((*it_M1).first, (*it_M2).first);
  ASSERT_EQ((*it_M1).second, (*it_M2).second);
  auto it_cpy = M1.begin();
  EXPECT_EQ(it_cpy == it_M1, true);
}

TEST(MAP_ITERATORS, MAP_MINUS_MINUS_OPERATOR) {
  s21::map<int, char> M1 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  std::map<int, char> M2 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  s21::map<int, char>::iterator it_M1 = --M1.end();
  std::map<int, char>::iterator it_M2 = --M2.end();
  ASSERT_EQ((*it_M1).first, (*it_M2).first);
  ASSERT_EQ((*it_M1).second, (*it_M2).second);
}

TEST(MAP_ITERATORS, MAP_OPERATOR_PLUS_PLUS) {
  s21::map<int, char> M1 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  std::map<int, char> M2 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  s21::map<int, char>::iterator it_M1 = M1.begin();
  std::map<int, char>::iterator it_M2 = M2.begin();
  it_M1++;
  it_M2++;
  ASSERT_EQ((*it_M1).first, (*it_M2).first);
  ASSERT_EQ((*it_M1).second, (*it_M2).second);
}

TEST(MAP_ITERATORS, MAP_OPERATOR_MINUS_MINUS) {
  s21::map<int, char> M1 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  std::map<int, char> M2 = {
      {50, 'a'},
      {25, 'b'},
      {75, 'c'},
      {10, 'd'},
  };
  s21::map<int, char>::iterator it_M1 = M1.end();
  std::map<int, char>::iterator it_M2 = M2.end();
  it_M1--;
  it_M2--;
  ASSERT_EQ(*it_M1, *it_M2);
}

TEST(MAP_ITERATORS, MAP_DEREFERENCE_OPERATOR_EXISTING_LIST) {
  s21::map<int, char> M1 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  std::map<int, char> M2 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  ASSERT_EQ((*(M1.begin())).first, ((*M2.begin())).first);
  ASSERT_EQ((*(M1.begin())).second, ((*M2.begin())).second);
}

TEST(MAP_ITERATORS, MAP_NOT_EQUAL_OPERATOR) {
  s21::map<int, char> M1 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  std::map<int, char> M2 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  ASSERT_EQ(M1.begin() != M1.begin(), M2.begin() != M2.begin());
}

TEST(MAP_ITERATORS, MAP_EQUAL_OPERATOR) {
  s21::map<int, char> M1 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  std::map<int, char> M2 = {{50, 'a'}, {25, 'b'}, {75, 'c'}, {10, 'd'}};
  ASSERT_EQ(M1.begin() == M1.begin(), M2.begin() == M2.begin());
}
