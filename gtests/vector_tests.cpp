#include <gtest/gtest.h>

#include <vector>

TEST(vector, is_created) {
    std::vector<int> list1;
    std::vector<int> *ptr = &list1;
    ASSERT_FALSE(ptr == nullptr);
}

TEST(vector, is_empty) {
    std::vector<int> list1;
    std::vector<int> list2 = {};
    ASSERT_TRUE(list1.empty());
    ASSERT_TRUE(list2.empty());
}

TEST(vector, is_equal_empty) {
    std::vector<int> list1;
    std::vector<int> list2 = {};
    ASSERT_TRUE(list1 == list2);
}

TEST(vector, is_equal_push_back_insert) {
    std::vector<int> list1;
    std::vector<int> list2;
    list1.push_back(1);
    list2.insert(list2.begin(), 1);
    ASSERT_TRUE(list1 == list2);
}

TEST(vector, push_back) {
    std::vector<int> list1;
    std::vector<int> list2 = {1, 2, 3};
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    ASSERT_TRUE(list1 == list2);
}

TEST(vector, push_front) {
    std::vector<int> list1;
    std::vector<int> list2 = {1, 2, 3};
    list1.insert(list1.begin(), 3);
    list1.insert(list1.begin(), 2);
    list1.insert(list1.begin(), 1);
    ASSERT_TRUE(list1 == list2);
}

TEST(vector, middle_insert) {
    std::vector<int> list1 = {1, 3};
    std::vector<int> list2 = {1, 2, 3};
    list1.insert(std::next(list1.begin(), 1), 2);
    ASSERT_TRUE(list1 == list2);
}

TEST(vector, pop_back) {
    std::vector<int> list1 = {1, 2};
    std::vector<int> list2 = {1, 2, 3};
    list2.pop_back();
    ASSERT_TRUE(list1 == list2);
}

TEST(vector, erase) {
    std::vector<int> list1 = {2, 3};
    std::vector<int> list2 = {1, 2, 3};
    list2.erase(list2.begin());
    ASSERT_TRUE(list1 == list2);
}

TEST(vector, size) {
    std::vector<int> list1 = {1, 2, 3};
    std::vector<int> list2 = {};
    std::vector<int> list3;
    ASSERT_TRUE(list1.size() == 3);
    ASSERT_TRUE(list2.size() == 0);
    ASSERT_TRUE(list3.size() == 0);
}

TEST(vector, clear) {
    std::vector<int> list1 = {1, 2, 3};
    std::vector<int> list2 = {};
    list1.clear();
    ASSERT_TRUE(list1 == list2);
}

TEST(vector, get_element) {
    std::vector<int> list1 = {1, 2, 3};
    auto it = list1.begin();
    ASSERT_TRUE(*it == 1);
    std::advance(it, 1);
    ASSERT_TRUE(*it == 2);
    std::advance(it, 1);
    ASSERT_TRUE(*it == 3);
}