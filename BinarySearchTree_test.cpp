#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>
#include <iostream>



TEST(insertTEST) {
    BinarySearchTree<int> testTree;
    testTree.insert(2);
    testTree.insert(3);
    testTree.insert(1);
    auto i = testTree.begin();
    ASSERT_EQUAL(*i, 1);
    ++i;
    ASSERT_EQUAL(*i, 2);
    ++i;
    ASSERT_EQUAL(*i, 3);
}

TEST(findTEST) {
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(75);
    testTree.insert(25);
    testTree.insert(85);
    testTree.insert(65);
    testTree.insert(35);
    testTree.insert(45);
    auto i = testTree.begin();
    auto finder = testTree.find(25);
    ASSERT_EQUAL(*i, *finder);
    finder = testTree.find(35);
    ++i;
    ASSERT_EQUAL(*i, *finder);
    finder = testTree.find(50);
    ++i;
    ++i;
    ASSERT_EQUAL(*i, *finder);
    finder = testTree.find(85);
    ++i;
    ++i;
    ++i;
    ASSERT_EQUAL(*i, *finder);
}

TEST(minGreaterThanTEST) {
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(75);
    testTree.insert(25);
    testTree.insert(85);
    testTree.insert(65);
    testTree.insert(35);
    testTree.insert(45);
    //HEY INSERT IS BROKEN!
    //std::cout << "GOTEM2";
    auto i = testTree.min_greater_than(84);
    ASSERT_EQUAL(*i, 85);
    i = testTree.min_greater_than(50);
    ASSERT_EQUAL(*i, 65);
    i = testTree.min_greater_than(100);
    ASSERT_EQUAL(i, testTree.end());
    i = testTree.min_greater_than(0);
    ASSERT_EQUAL(*i, 25);
    
    //ASSERT_EQUAL(testTree.min_greater_than(100), testTree.end());
}

TEST(HeightAndSizeEvenTEST) {
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(75);
    testTree.insert(25);
    testTree.insert(35);
    testTree.insert(85);
    testTree.insert(65);
    testTree.insert(15);
    ASSERT_EQUAL(testTree.height(), 3);
    ASSERT_EQUAL(testTree.size(), 7);
}

TEST(HeightAndSizeRightTEST) {
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(60);
    testTree.insert(70);
    testTree.insert(80);
    testTree.insert(90);
    testTree.insert(100);
    //std::cout << testTree.to_string() << std::endl;
    ASSERT_EQUAL(testTree.height(), 6);
    ASSERT_EQUAL(testTree.size(), 6);
    ASSERT_EQUAL(testTree.height(), testTree.size());
}

TEST(HeightAndSizeLeftTEST) {
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(40);
    testTree.insert(30);
    testTree.insert(20);
    testTree.insert(10);
    testTree.insert(0); 
    testTree.insert(-10);
    //std::cout << testTree.to_string() << std::endl;
    ASSERT_EQUAL(testTree.height(), 7);
    ASSERT_EQUAL(testTree.size(), 7);
    ASSERT_EQUAL(testTree.height(), testTree.size());
}

TEST(SortingInvariantEvenTreeTEST) {
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(75);
    testTree.insert(25);
    testTree.insert(35);
    testTree.insert(85);
    testTree.insert(65);
    testTree.insert(15);
    //std::cout << testTree.to_string() << std::endl;
    ASSERT_TRUE(testTree.check_sorting_invariant());
}

TEST(SortingInvariantRightTreeTEST) {
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(60);
    testTree.insert(70);
    testTree.insert(80);
    testTree.insert(90);
    testTree.insert(100);
    //std::cout << testTree.to_string() << std::endl;
    ASSERT_TRUE(testTree.check_sorting_invariant());
}

TEST(SortingInvariantLeftTreeTEST) {
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(40);
    testTree.insert(30);
    testTree.insert(20);
    testTree.insert(10);
    testTree.insert(0); 
    testTree.insert(-10);
    //std::cout << testTree.to_string() << std::endl;
    ASSERT_TRUE(testTree.check_sorting_invariant());
}

TEST(minElemTEST) {
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(75);
    testTree.insert(25);
    testTree.insert(35);
    testTree.insert(85);
    testTree.insert(65);
    testTree.insert(15);
    auto i = testTree.min_element();
    ASSERT_EQUAL(*i, 15);
    testTree.insert(-1);
    i = testTree.min_element();
    ASSERT_NOT_EQUAL(*i, 15);
    ASSERT_EQUAL(*i, -1);
}

TEST(maxElemTEST) {
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(75);
    testTree.insert(25);
    testTree.insert(35);
    testTree.insert(85);
    testTree.insert(65);
    testTree.insert(15);
    auto i = testTree.max_element();
    ASSERT_EQUAL(*i, 85);
    testTree.insert(10000);
    i = testTree.max_element();
    ASSERT_NOT_EQUAL(*i, 85);
    ASSERT_EQUAL(*i, 10000);
}

TEST(MinEDGE) {
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(75);
    testTree.insert(25);
    testTree.insert(35);
    testTree.insert(85);
    testTree.insert(65);
    testTree.insert(15);
    auto i = testTree.find(85);
    *i = 1;
    auto j = testTree.min_element();
    ASSERT_NOT_EQUAL(*i, *j);
    ASSERT_FALSE(testTree.check_sorting_invariant());
}

TEST(MaxEDGE) {
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(75);
    testTree.insert(25);
    testTree.insert(35);
    testTree.insert(85);
    testTree.insert(65);
    testTree.insert(15);
    auto i = testTree.find(15);
    *i = 100;
    auto j = testTree.max_element();
    ASSERT_NOT_EQUAL(*i, *j);
    ASSERT_FALSE(testTree.check_sorting_invariant());
}

TEST(noNodesEDGE) {
    BinarySearchTree<int> testTree;
    auto a = testTree.max_element();
    //std::cout << 'a' << std:: endl;
    auto b = testTree.min_element();
    //std::cout << 'b' << std:: endl;
    auto c = testTree.find(0);
    //std::cout << 'c' << std:: endl;
    auto d = testTree.min_greater_than(0);
    //std::cout << 'd' << std:: endl;

    ASSERT_EQUAL(testTree.end(), a);
    ASSERT_EQUAL(testTree.end(), b);
    ASSERT_EQUAL(testTree.end(), c);
    ASSERT_EQUAL(testTree.end(), d);
    ASSERT_EQUAL(0, testTree.height());
    ASSERT_EQUAL(0, testTree.size());
    //std::cout << "ERROR IN EMPTY()" << std:: endl;
    ASSERT_TRUE(testTree.empty());
}

TEST(oneNodeEDGE) {
    BinarySearchTree<int> testTree;
    testTree.insert(1);
    auto a = testTree.min_element();
    auto b = testTree.max_element();
    auto c = testTree.find(1000);
    ASSERT_EQUAL(*a, *b);
    ASSERT_EQUAL(*a, 1);
    ASSERT_EQUAL(*b, 1);
    ASSERT_EQUAL(a, b);
    ASSERT_EQUAL(c, testTree.end());
    ++a;
    ASSERT_EQUAL(a, testTree.end());
    ASSERT_EQUAL(testTree.height(), 1);
    ASSERT_EQUAL(testTree.size(), 1);
}

TEST(assignmentTEST) {
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(75);
    testTree.insert(25);
    testTree.insert(35);
    testTree.insert(85);
    testTree.insert(65);
    testTree.insert(15);
    BinarySearchTree<int> assignmentTree;
    ASSERT_TRUE(assignmentTree.empty());
    assignmentTree = testTree;
    ASSERT_FALSE(assignmentTree.empty());
    auto i = testTree.begin();
    auto j = assignmentTree.begin();
    //int count = 0;
    while(i != testTree.end() && j != assignmentTree.end()) {
        ASSERT_EQUAL(*i, *j);
        ASSERT_NOT_EQUAL(i, j);
        //count++;
        //std::cout << count << std:: endl;
        ++i, ++j;
    }
    BinarySearchTree<int> copyTree(testTree);
    auto b = testTree.begin();
    auto c = copyTree.begin();
        while(i != testTree.end() && j != copyTree.end()) {
        ASSERT_EQUAL(*i, *j);
        ASSERT_NOT_EQUAL(i, j);
        //count++;
        //std::cout << count << std:: endl;
        ++i, ++j;
    }
    b = testTree.begin();
    c = copyTree.begin();
    *c = 51;
    ASSERT_NOT_EQUAL(*b, *c);
}

TEST(inOrderTEST) {
    std::string expectedOut = "15 25 35 50 65 75 85 ";
    std::ostringstream ss;
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(75);
    testTree.insert(25);
    testTree.insert(35);
    testTree.insert(85);
    testTree.insert(65);
    testTree.insert(15);
    testTree.traverse_inorder(ss);
    std::string output = ss.str();
    //std::cout << output << std::endl;
    ASSERT_EQUAL(output, expectedOut);
}

TEST(preOrderTEST) {
    std::string expectedOut = "50 25 15 35 75 65 85 ";
    std::ostringstream ss;
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(75);
    testTree.insert(25);
    testTree.insert(35);
    testTree.insert(85);
    testTree.insert(65);
    testTree.insert(15);
    testTree.traverse_preorder(ss);
    std::string output = ss.str();
    //std::cout << output << std::endl;
    ASSERT_EQUAL(output, expectedOut);
}

TEST(breakingInvariantEDGE) {
    BinarySearchTree<int> testTree;
    testTree.insert(50);
    testTree.insert(75);
    testTree.insert(25);
    ASSERT_TRUE(testTree.check_sorting_invariant());
    auto i = testTree.begin();
    *i = 50;
    //std::cout << testTree.to_string() << std::endl;
    ASSERT_FALSE(testTree.check_sorting_invariant());
    *i = 100;
    ASSERT_FALSE(testTree.check_sorting_invariant());
    *i = 25;
    ASSERT_TRUE(testTree.check_sorting_invariant());
    ++i;
    *i = 50000;
    ASSERT_FALSE(testTree.check_sorting_invariant());
    *i = -50000;
    ASSERT_FALSE(testTree.check_sorting_invariant());
    *i = 50;
    ASSERT_TRUE(testTree.check_sorting_invariant());
    ++i;
    *i = 50;
    ASSERT_FALSE(testTree.check_sorting_invariant());
    *i = 0;
    ASSERT_FALSE(testTree.check_sorting_invariant());
    *i = 75;
    ASSERT_TRUE(testTree.check_sorting_invariant());
}

TEST_MAIN()
