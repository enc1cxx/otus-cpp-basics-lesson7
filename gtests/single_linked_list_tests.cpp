#include <gtest/gtest.h>

#include "single_linked_list.hpp"

// 1 Создание контейнера
TEST(single_linked_list, is_created) {
  single_linked_list::SingleLinkedList<int> single_linked_list1;
  single_linked_list::SingleLinkedList<int> *ptr = &single_linked_list1;
  ASSERT_TRUE(ptr != nullptr);
}

// 2 Вставка элементов в конец
TEST(single_linked_list, push_back) {
  single_linked_list::SingleLinkedList<int> single_linked_list1;
  single_linked_list::SingleLinkedList<int> single_linked_list2 = {1, 2, 3};
  single_linked_list1.push_back(1);
  single_linked_list1.push_back(2);
  single_linked_list1.push_back(3);
  ASSERT_TRUE(single_linked_list1 == single_linked_list2);
}

// 3 Вставка элементов в начало
TEST(single_linked_list, push_front) {
  single_linked_list::SingleLinkedList<int> single_linked_list1;
  single_linked_list::SingleLinkedList<int> single_linked_list2 = {1, 2, 3};
  single_linked_list1.push_front(3);
  single_linked_list1.push_front(2);
  single_linked_list1.push_front(1);
  ASSERT_TRUE(single_linked_list1 == single_linked_list2);
}

// 4 Вставка элементов в середину
TEST(single_linked_list, insert) {
  single_linked_list::SingleLinkedList<int> single_linked_list1 = {1, 3};
  single_linked_list::SingleLinkedList<int> single_linked_list2 = {1, 2, 3};
  single_linked_list1.insert(single_linked_list1.begin(), 2);
  ASSERT_TRUE(single_linked_list1 == single_linked_list2);
}

// 5 Удаление элементов из конца
TEST(single_linked_list, erase_last) {
  single_linked_list::SingleLinkedList<int> single_linked_list1 = {1, 2};
  single_linked_list::SingleLinkedList<int> single_linked_list2 = {1, 2, 3};
  single_linked_list2.erase(std::next(single_linked_list2.begin(), 1));
  ASSERT_TRUE(single_linked_list1 == single_linked_list2);
}

// 6 Удаление элементов из начала
TEST(single_linked_list, pop_front) {
  single_linked_list::SingleLinkedList<int> single_linked_list1 = {2, 3};
  single_linked_list::SingleLinkedList<int> single_linked_list2 = {1, 2, 3};
  single_linked_list2.pop_front();
  ASSERT_TRUE(single_linked_list1 == single_linked_list2);
}

// 7 Удаление элементов из середины
TEST(single_linked_list, erase_middle) {
  single_linked_list::SingleLinkedList<int> single_linked_list1 = {1, 3};
  single_linked_list::SingleLinkedList<int> single_linked_list2 = {1, 2, 3};
  single_linked_list2.erase(single_linked_list2.begin());
  ASSERT_TRUE(single_linked_list1 == single_linked_list2);
}

// 8 Получение элементов из контейнера
TEST(single_linked_list, get_element) {
  single_linked_list::SingleLinkedList<int> single_linked_list1 = {1, 2, 3};
  auto it = single_linked_list1.begin();
  ASSERT_TRUE(*it == 1);
  std::advance(it, 1);
  ASSERT_TRUE(*it == 2);
  std::advance(it, 1);
  ASSERT_TRUE(*it == 3);
  ASSERT_TRUE(single_linked_list1[0] = 1);
  ASSERT_TRUE(single_linked_list1[1] = 2);
  ASSERT_TRUE(single_linked_list1[2] = 3);
}

// 9 Получение размера контейнера
TEST(single_linked_list, size) {
  single_linked_list::SingleLinkedList<int> single_linked_list1 = {1, 2, 3};
  single_linked_list::SingleLinkedList<int> single_linked_list2 = {};
  single_linked_list::SingleLinkedList<int> list3;
  ASSERT_TRUE(single_linked_list1.size() == 3);
  ASSERT_TRUE(single_linked_list2.size() == 0);
  ASSERT_TRUE(list3.size() == 0);
}

// 10 Копирование контейнера
TEST(single_linked_list, copy) {
  single_linked_list::SingleLinkedList<int> single_linked_list1 = {1, 2, 3};
  single_linked_list::SingleLinkedList<int> single_linked_list2 =
      single_linked_list1;
  ASSERT_TRUE(single_linked_list1 == single_linked_list2);
}

// 11 Удаление контейнера
TEST(single_linked_list, call_destructors) {
  static int counter = 0;
  class Helper {
  public:
    ~Helper() { ++counter; }
  };

  single_linked_list::SingleLinkedList<Helper> single_linked_list1;
  Helper h;
  single_linked_list1.push_back(h);
  single_linked_list1.push_back(h);
  single_linked_list1.push_back(h);
  single_linked_list1.~SingleLinkedList();
  ASSERT_TRUE(counter == 3);
}

// 12 Перемещение контейнера
TEST(single_linked_list, move) {
  single_linked_list::SingleLinkedList<int> full = {1, 2, 3};
  single_linked_list::SingleLinkedList<int> empty;

  single_linked_list::SingleLinkedList<int> single_linked_list1 = {1, 2, 3};
  single_linked_list::SingleLinkedList<int> single_linked_list2;

  single_linked_list2 = std::move(single_linked_list1);

  ASSERT_TRUE(single_linked_list2 == full);
}

// Тесты вне задания

TEST(single_linked_list, is_empty) {
  single_linked_list::SingleLinkedList<int> single_linked_list1;
  single_linked_list::SingleLinkedList<int> single_linked_list2 = {};
  ASSERT_TRUE(single_linked_list1.is_empty());
  ASSERT_TRUE(single_linked_list2.is_empty());
}

TEST(single_linked_list, is_equal_empty) {
  single_linked_list::SingleLinkedList<int> single_linked_list1;
  single_linked_list::SingleLinkedList<int> single_linked_list2 = {};
  ASSERT_TRUE(single_linked_list1 == single_linked_list2);
}

TEST(single_linked_list, is_equal_push_back_front) {
  single_linked_list::SingleLinkedList<int> single_linked_list1;
  single_linked_list::SingleLinkedList<int> single_linked_list2;
  single_linked_list1.push_back(1);
  single_linked_list2.push_front(1);
  ASSERT_TRUE(single_linked_list1 == single_linked_list2);
}

TEST(single_linked_list, clear) {
  single_linked_list::SingleLinkedList<int> single_linked_list1 = {};
  single_linked_list::SingleLinkedList<int> single_linked_list2 = {1, 2, 3};
  single_linked_list2.clear();
  ASSERT_TRUE(single_linked_list1 == single_linked_list2);
}
