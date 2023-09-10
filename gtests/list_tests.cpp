#include <gtest/gtest.h>

#include <list>

TEST(list, is_created) {
    std::list<int> list1;
    std::list<int> *ptr = &list1;
    ASSERT_FALSE(ptr == nullptr);
}

TEST(list, is_empty) {
    std::list<int> list1;
    std::list<int> list2 = {};
    ASSERT_TRUE(list1.empty());
    ASSERT_TRUE(list2.empty());
}

TEST(list, is_equal_empty) {
    std::list<int> list1;
    std::list<int> list2 = {};
    ASSERT_TRUE(list1 == list2);
}

TEST(list, is_equal_push_back_front) {
    std::list<int> list1;
    std::list<int> list2;
    list1.push_back(1);
    list2.push_front(1);
    ASSERT_TRUE(list1 == list2);
}

TEST(list, push_back) {
    std::list<int> list1;
    std::list<int> list2 = {1, 2, 3};
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    ASSERT_TRUE(list1 == list2);
}

TEST(list, push_front) {
    std::list<int> list1;
    std::list<int> list2 = {1, 2, 3};
    list1.push_front(3);
    list1.push_front(2);
    list1.push_front(1);
    ASSERT_TRUE(list1 == list2);
}

TEST(list, insert) {
    std::list<int> list1 = {1, 3};
    std::list<int> list2 = {1, 2, 3};
    list1.insert(std::next(list1.begin(), 1), 2);
    ASSERT_TRUE(list1 == list2);
}

TEST(list, pop_back) {
    std::list<int> list1 = {1, 2};
    std::list<int> list2 = {1, 2, 3};
    list2.pop_back();
    ASSERT_TRUE(list1 == list2);
}

TEST(list, pop_front) {
    std::list<int> list1 = {2, 3};
    std::list<int> list2 = {1, 2, 3};
    list2.pop_front();
    ASSERT_TRUE(list1 == list2);
}

TEST(list, clear) {
    std::list<int> list1 = {};
    std::list<int> list2 = {1, 2, 3};
    list2.clear();
    ASSERT_TRUE(list1 == list2);
}

TEST(list, size) {
    std::list<int> list1 = {1, 2, 3};
    std::list<int> list2 = {};
    std::list<int> list3;
    ASSERT_TRUE(list1.size() == 3);
    ASSERT_TRUE(list2.size() == 0);
    ASSERT_TRUE(list3.size() == 0);
}

TEST(list, get_element) {
    std::list<int> list1 = {1, 2, 3};
    auto it = list1.begin();
    ASSERT_TRUE(*it == 1);
    std::advance(it, 1);
    ASSERT_TRUE(*it == 2);
    std::advance(it, 1);
    ASSERT_TRUE(*it == 3);
}
