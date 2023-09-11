#include <gtest/gtest.h>

#include <vector>

TEST(vector, is_created) {
  std::vector<int> vector1;
  std::vector<int> *ptr = &vector1;
  ASSERT_FALSE(ptr == nullptr);
}

TEST(vector, is_empty) {
  std::vector<int> vector1;
  std::vector<int> vector2 = {};
  ASSERT_TRUE(vector1.empty());
  ASSERT_TRUE(vector2.empty());
}

TEST(vector, is_equal_empty) {
  std::vector<int> vector1;
  std::vector<int> vector2 = {};
  ASSERT_TRUE(vector1 == vector2);
}

TEST(vector, is_equal_push_back_insert) {
  std::vector<int> vector1;
  std::vector<int> vector2;
  vector1.push_back(1);
  vector2.insert(vector2.begin(), 1);
  ASSERT_TRUE(vector1 == vector2);
}

TEST(vector, push_back) {
  std::vector<int> vector1;
  std::vector<int> vector2 = {1, 2, 3};
  vector1.push_back(1);
  vector1.push_back(2);
  vector1.push_back(3);
  ASSERT_TRUE(vector1 == vector2);
}

TEST(vector, push_front) {
  std::vector<int> vector1;
  std::vector<int> vector2 = {1, 2, 3};
  vector1.insert(vector1.begin(), 3);
  vector1.insert(vector1.begin(), 2);
  vector1.insert(vector1.begin(), 1);
  ASSERT_TRUE(vector1 == vector2);
}

TEST(vector, middle_insert) {
  std::vector<int> vector1 = {1, 3};
  std::vector<int> vector2 = {1, 2, 3};
  vector1.insert(std::next(vector1.begin(), 1), 2);
  ASSERT_TRUE(vector1 == vector2);
}

TEST(vector, pop_back) {
  std::vector<int> vector1 = {1, 2};
  std::vector<int> vector2 = {1, 2, 3};
  vector2.pop_back();
  ASSERT_TRUE(vector1 == vector2);
}

TEST(vector, erase) {
  std::vector<int> vector1 = {2, 3};
  std::vector<int> vector2 = {1, 2, 3};
  vector2.erase(vector2.begin());
  ASSERT_TRUE(vector1 == vector2);
}

TEST(vector, size) {
  std::vector<int> vector1 = {1, 2, 3};
  std::vector<int> vector2 = {};
  std::vector<int> vector3;
  ASSERT_TRUE(vector1.size() == 3);
  ASSERT_TRUE(vector2.size() == 0);
  ASSERT_TRUE(vector3.size() == 0);
}

TEST(vector, clear) {
  std::vector<int> vector1 = {1, 2, 3};
  std::vector<int> vector2 = {};
  vector1.clear();
  ASSERT_TRUE(vector1 == vector2);
}

TEST(vector, get_element) {
  std::vector<int> vector1 = {1, 2, 3};
  auto it = vector1.begin();
  ASSERT_TRUE(*it == 1);
  std::advance(it, 1);
  ASSERT_TRUE(*it == 2);
  std::advance(it, 1);
  ASSERT_TRUE(*it == 3);
}

TEST(vector, copy) {
  std::vector<int> vector1 = {1, 2, 3};
  std::vector<int> vector2 = vector1;
  ASSERT_TRUE(vector1 == vector2);
}

TEST(vector, move) {
  std::vector<int> full = {1, 2, 3};
  std::vector<int> empty;

  std::vector<int> vector1 = {1, 2, 3};
  std::vector<int> vector2;

  vector2 = std::move(vector1);

  ASSERT_TRUE(vector1 == empty);
  ASSERT_TRUE(vector2 == full);
}