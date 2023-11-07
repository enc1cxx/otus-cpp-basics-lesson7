#include <gtest/gtest.h>

#include "vector.hpp"

// 1 Создание контейнера
TEST(vector, is_created) {
  vector::Vector<int> vector1;
  vector::Vector<int> *ptr = &vector1;
  ASSERT_TRUE(ptr != nullptr);
}

// 2 Вставка элементов в конец
TEST(vector, push_back) {
  vector::Vector<int> vector1;
  for (int i = 1; i <= 3; ++i) {
    vector1.push_back(i);
  }
  ASSERT_TRUE(vector1[0] == 1);
  ASSERT_TRUE(vector1[1] == 2);
  ASSERT_TRUE(vector1[2] == 3);
}

// 3 Вставка элементов в начало
TEST(vector, insert_front) {
  vector::Vector<int> vector1;
  for (int i = 3; i != 0; --i) {
    vector1.insert(vector1.begin(), i);
  }
  ASSERT_TRUE(vector1.size() == 3);
  ASSERT_TRUE(vector1[0] == 1);
  ASSERT_TRUE(vector1[1] == 2);
  ASSERT_TRUE(vector1[2] == 3);
}

// 4 Вставка элементов в середину
TEST(vector, insert_middle) {
  vector::Vector<int> vector1;
  vector1.push_back(1);
  vector1.push_back(3);
  vector1.insert(std::next(vector1.begin()), 2);
  ASSERT_TRUE(vector1.size() == 3);
  ASSERT_TRUE(vector1[0] == 1);
  ASSERT_TRUE(vector1[1] == 2);
  ASSERT_TRUE(vector1[2] == 3);
}

// 5 Удаление элементов из конца
TEST(vector, pop_back) {
  vector::Vector<int> vector1;
  for (int i = 1; i <= 3; ++i) {
    vector1.push_back(i);
  }
  ASSERT_TRUE(vector1.size() == 3);
  vector1.pop_back();
  ASSERT_TRUE(vector1.size() == 2);
  ASSERT_TRUE(vector1[0] == 1);
  ASSERT_TRUE(vector1[1] == 2);
}

// 6 Удаление элементов из начала
TEST(vector, erase_front) {
  vector::Vector<int> vector1;
  for (int i = 1; i <= 3; ++i) {
    vector1.push_back(i);
  }
  ASSERT_TRUE(vector1.size() == 3);
  vector1.erase(vector1.begin());
  ASSERT_TRUE(vector1.size() == 2);
  ASSERT_TRUE(vector1[0] == 2);
  ASSERT_TRUE(vector1[1] == 3);
}

// 7 Удаление элементов из середины
TEST(vector, erase_middle) {
  vector::Vector<int> vector1;
  for (int i = 1; i <= 3; ++i) {
    vector1.push_back(i);
  }
  vector1.erase(std::next(vector1.begin(), 1));
  ASSERT_TRUE(vector1[0] == 1);
  ASSERT_TRUE(vector1[1] == 3);
}

// 8 Получение элементов из контейнера
TEST(vector, get_element) {
  vector::Vector<int> vector1;
  for (int i = 1; i <= 3; ++i) {
    vector1.push_back(i);
  }
  auto it = vector1.begin();
  ASSERT_TRUE(*it == 1);
  std::advance(it, 1);
  ASSERT_TRUE(*it == 2);
  std::advance(it, 1);
  ASSERT_TRUE(*it == 3);
  ASSERT_TRUE(vector1[0] = 1);
  ASSERT_TRUE(vector1[1] = 2);
  ASSERT_TRUE(vector1[2] = 3);
}

// 9 Получение размера контейнера
TEST(vector, size) {
  vector::Vector<int> vector1;
  ASSERT_TRUE(vector1.size() == 0);
  for (int i = 1; i <= 3; ++i) {
    vector1.push_back(i);
  }
  ASSERT_TRUE(vector1.size() == 3);
}

// 10 Копирование контейнера
TEST(vector, copy) {
  vector::Vector<int> vector1;
  for (int i = 1; i <= 3; ++i) {
    vector1.push_back(i);
  }
  vector::Vector<int> vector2 = vector1;
  ASSERT_TRUE(vector1 == vector2);
}

// 11 Перемещение контейнера
TEST(vector, move) {
  vector::Vector<int> full;
  for (int i = 1; i <= 3; ++i) {
    full.push_back(i);
  }

  vector::Vector<int> vector1;
  for (int i = 1; i <= 3; ++i) {
    vector1.push_back(i);
  }
  vector::Vector<int> vector2;

  vector2 = std::move(vector1);

  ASSERT_TRUE(vector2 == full);
}

// Тесты вне задания

TEST(vector, is_equal_empty) {
  vector::Vector<int> vector1;
  vector::Vector<int> vector2;
  ASSERT_TRUE(vector1 == vector2);
}

