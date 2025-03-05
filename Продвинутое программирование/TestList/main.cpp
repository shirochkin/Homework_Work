//подключаем макросы catch2
#include <catch2/catch_test_macros.hpp>
#include "List.h"
#include <iostream>


bool emptyCheck() {
    List l;
    return l.Empty();
}

int sizeCheck(int n) {
    List l;
    for (int i = 0; i < n; i++) {
        l.PushBack(rand());
    }

    return l.Size();
}

int clearCheck(int n) {
    List l;
    for (int i = 0; i < n; i++) {
        l.PushBack(rand());
    }
    l.Clear();
    return l.Size();
}

int pushBackCheck(int n) {
    List l;
        l.PushBack(n);
 
        return l.PopBack();
}

int pushFrontCheck(int n) {
    List l;
    l.PushFront(n);

    return l.PopFront();
}

int popBackCheck() {
    List l;

    return l.PopBack();
}

int popFrontCheck() {
    List l;

    return l.PopFront();
}


    //юнит-тест
    TEST_CASE("Empty is OK", "[Empty]") {
        REQUIRE(emptyCheck() == 1);
    }

    TEST_CASE("Size is OK", "[Size]") {
        REQUIRE(sizeCheck(3) == 3);
        REQUIRE(sizeCheck(10) == 10);
        REQUIRE(sizeCheck(27) == 27);
    }

    TEST_CASE("Clear is OK", "[Clear]") {
        REQUIRE(clearCheck(3) == 0);
        REQUIRE(clearCheck(10) == 0);
        REQUIRE(clearCheck(27) == 0);
    }

    TEST_CASE("PushBack is OK", "[PushBack]") {
        REQUIRE(pushBackCheck(3) == 3);
        REQUIRE(pushBackCheck(10) == 10);
        REQUIRE(pushBackCheck(-31) == -31);
    }

    TEST_CASE("PushFront is OK", "[PushFront]") {
        REQUIRE(pushFrontCheck(3) == 3);
        REQUIRE(pushFrontCheck(10) == 10);
        REQUIRE(pushFrontCheck(-31) == -31);
    }

    TEST_CASE("PopFront is OK", "[PopFront]") {
        REQUIRE(popFrontCheck() == 0);

    }

    TEST_CASE("PopBack is OK", "[PopBack]") {
        REQUIRE(popBackCheck() == 0);

    }