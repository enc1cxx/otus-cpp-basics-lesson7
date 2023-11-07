#include <gtest/gtest.h>

#include "double_linked_list.hpp"

// 1 Создание контейнера
TEST(double_linked_list, is_created) {
  double_linked_list::DoubleLinkedList<int> double_linked_list1;
  double_linked_list::DoubleLinkedList<int> *ptr = &double_linked_list1;
  ASSERT_TRUE(ptr != nullptr);
}

// 2 Вставка элементов в конец
TEST(double_linked_list, push_back) {
  double_linked_list::DoubleLinkedList<int> double_linked_list1;
  double_linked_list::DoubleLinkedList<int> double_linked_list2 = {1, 2, 3};
  double_linked_list1.push_back(1);
  double_linked_list1.push_back(2);
  double_linked_list1.push_back(3);
  ASSERT_TRUE(double_linked_list1 == double_linked_list2);
}

// 3 Вставка элементов в начало
TEST(double_linked_list, push_front) {
  double_linked_list::DoubleLinkedList<int> double_linked_list1;
  double_linked_list::DoubleLinkedList<int> double_linked_list2 = {1, 2, 3};
  double_linked_list1.push_front(3);
  double_linked_list1.push_front(2);
  double_linked_list1.push_front(1);
  ASSERT_TRUE(double_linked_list1 == double_linked_list2);
}

// 4 Вставка элементов в середину
TEST(double_linked_list, insert) {
  double_linked_list::DoubleLinkedList<int> double_linked_list1 = {1, 3};
  double_linked_list::DoubleLinkedList<int> double_linked_list2 = {1, 2, 3};
  double_linked_list1.insert(double_linked_list1.begin(), 2);
  ASSERT_TRUE(double_linked_list1 == double_linked_list2);
}

// 5 Удаление элементов из конца
TEST(double_linked_list, erase_last) {
  double_linked_list::DoubleLinkedList<int> double_linked_list1 = {1, 2};
  double_linked_list::DoubleLinkedList<int> double_linked_list2 = {1, 2, 3};
  double_linked_list2.erase(std::next(double_linked_list2.begin(), 1));
  ASSERT_TRUE(double_linked_list1 == double_linked_list2);
}

// 6 Удаление элементов из начала
TEST(double_linked_list, pop_front) {
  double_linked_list::DoubleLinkedList<int> double_linked_list1 = {2, 3};
  double_linked_list::DoubleLinkedList<int> double_linked_list2 = {1, 2, 3};
  double_linked_list2.pop_front();
  ASSERT_TRUE(double_linked_list1 == double_linked_list2);
}

// 7 Удаление элементов из середины
TEST(double_linked_list, erase_middle) {
  double_linked_list::DoubleLinkedList<int> double_linked_list1 = {1, 3};
  double_linked_list::DoubleLinkedList<int> double_linked_list2 = {1, 2, 3};
  double_linked_list2.erase(double_linked_list2.begin());
  ASSERT_TRUE(double_linked_list1 == double_linked_list2);
}

// 8 Получение элементов из контейнера
TEST(double_linked_list, get_element) {
  double_linked_list::DoubleLinkedList<int> double_linked_list1 = {1, 2, 3};
  auto it = double_linked_list1.begin();
  ASSERT_TRUE(*it == 1);
  std::advance(it, 1);
  ASSERT_TRUE(*it == 2);
  std::advance(it, 1);
  ASSERT_TRUE(*it == 3);
  ASSERT_TRUE(double_linked_list1[0] = 1);
  ASSERT_TRUE(double_linked_list1[1] = 2);
  ASSERT_TRUE(double_linked_list1[2] = 3);
}

// 9 Получение размера контейнера
TEST(double_linked_list, size) {
  double_linked_list::DoubleLinkedList<int> double_linked_list1 = {1, 2, 3};
  double_linked_list::DoubleLinkedList<int> double_linked_list2 = {};
  double_linked_list::DoubleLinkedList<int> list3;
  ASSERT_TRUE(double_linked_list1.size() == 3);
  ASSERT_TRUE(double_linked_list2.size() == 0);
  ASSERT_TRUE(list3.size() == 0);
}

// 10 Копирование контейнера
TEST(double_linked_list, copy) {
  double_linked_list::DoubleLinkedList<int> double_linked_list1 = {1, 2, 3};
  double_linked_list::DoubleLinkedList<int> double_linked_list2 =
      double_linked_list1;
  ASSERT_TRUE(double_linked_list1 == double_linked_list2);
}

// 11 Удаление контейнера
TEST(double_linked_list, call_destructors) {
  static int counter = 0;
  class Helper {
  public:
    ~Helper() { ++counter; }
  };

  double_linked_list::DoubleLinkedList<Helper> double_linked_list1;
  Helper h;
  double_linked_list1.push_back(h);
  double_linked_list1.push_back(h);
  double_linked_list1.push_back(h);
  double_linked_list1.~DoubleLinkedList();
  ASSERT_TRUE(counter == 3);
}

// 12 Перемещение контейнера
TEST(double_linked_list, move) {
  double_linked_list::DoubleLinkedList<int> full = {1, 2, 3};
  double_linked_list::DoubleLinkedList<int> empty;

  double_linked_list::DoubleLinkedList<int> double_linked_list1 = {1, 2, 3};
  double_linked_list::DoubleLinkedList<int> double_linked_list2;

  double_linked_list2 = std::move(double_linked_list1);

  ASSERT_TRUE(double_linked_list2 == full);
}

// Тесты вне задания

TEST(double_linked_list, is_empty) {
  double_linked_list::DoubleLinkedList<int> double_linked_list1;
  double_linked_list::DoubleLinkedList<int> double_linked_list2 = {};
  ASSERT_TRUE(double_linked_list1.is_empty());
  ASSERT_TRUE(double_linked_list2.is_empty());
}

TEST(double_linked_list, is_equal_empty) {
  double_linked_list::DoubleLinkedList<int> double_linked_list1;
  double_linked_list::DoubleLinkedList<int> double_linked_list2 = {};
  ASSERT_TRUE(double_linked_list1 == double_linked_list2);
}

TEST(double_linked_list, is_equal_push_back_front) {
  double_linked_list::DoubleLinkedList<int> double_linked_list1;
  double_linked_list::DoubleLinkedList<int> double_linked_list2;
  double_linked_list1.push_back(1);
  double_linked_list2.push_front(1);
  ASSERT_TRUE(double_linked_list1 == double_linked_list2);
}

TEST(double_linked_list, clear) {
  double_linked_list::DoubleLinkedList<int> double_linked_list1 = {};
  double_linked_list::DoubleLinkedList<int> double_linked_list2 = {1, 2, 3};
  double_linked_list2.clear();
  ASSERT_TRUE(double_linked_list1 == double_linked_list2);
}
