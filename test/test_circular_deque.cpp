#include <catch2/catch_test_macros.hpp>
#include "circular_deque.hpp"
using namespace hsc_snippets;

TEST_CASE("CircularDeque basic operations", "[CircularDeque]")
{
    CircularDeque<int, 5> deque;

    SECTION("Deque is initially empty")
    {
        REQUIRE(deque.empty());
        REQUIRE(deque.size() == 0);
        REQUIRE_FALSE(deque.full());
    }

    SECTION("Push back elements")
    {
        deque.push_back(1);
        deque.push_back(2);
        deque.push_back(3);

        REQUIRE_FALSE(deque.empty());
        REQUIRE(deque.size() == 3);
        REQUIRE(deque.front() == 1);
        REQUIRE(deque.back() == 3);
    }

    SECTION("Push front elements")
    {
        deque.push_front(1);
        deque.push_front(2);
        deque.push_front(3);

        REQUIRE_FALSE(deque.empty());
        REQUIRE(deque.size() == 3);
        REQUIRE(deque.front() == 3);
        REQUIRE(deque.back() == 1);
    }

    SECTION("Pop front elements")
    {
        deque.push_back(1);
        deque.push_back(2);
        deque.push_back(3);

        deque.pop_front();

        REQUIRE(deque.size() == 2);
        REQUIRE(deque.front() == 2);
        REQUIRE(deque.back() == 3);
    }

    SECTION("Pop back elements")
    {
        deque.push_back(1);
        deque.push_back(2);
        deque.push_back(3);

        deque.pop_back();

        REQUIRE(deque.size() == 2);
        REQUIRE(deque.front() == 1);
        REQUIRE(deque.back() == 2);
    }

    SECTION("Push to full deque")
    {
        deque.push_back(1);
        deque.push_back(2);
        deque.push_back(3);
        deque.push_back(4);
        deque.push_back(5);

        REQUIRE(deque.full());

        REQUIRE_THROWS_AS(deque.push_back(6), std::overflow_error);
        REQUIRE_THROWS_AS(deque.push_front(0), std::overflow_error);
    }

    SECTION("Pop from empty deque")
    {
        REQUIRE(deque.empty());
        REQUIRE_THROWS_AS(deque.pop_back(), std::underflow_error);
        REQUIRE_THROWS_AS(deque.pop_front(), std::underflow_error);
    }

    SECTION("Clear deque")
    {
        deque.push_back(1);
        deque.push_back(2);
        deque.push_back(3);

        deque.clear();

        REQUIRE(deque.empty());
        REQUIRE(deque.size() == 0);
        REQUIRE_THROWS_AS(deque.front(), std::underflow_error);
        REQUIRE_THROWS_AS(deque.back(), std::underflow_error);
    }

    SECTION("Wrap-around behavior")
    {
        deque.push_back(1);
        deque.push_back(2);
        deque.push_back(3);

        deque.pop_front(); // Removes 1
        deque.pop_front(); // Removes 2

        deque.push_back(4);
        deque.push_back(5);
        deque.push_back(6); // Should wrap around

        REQUIRE(deque.size() == 4);
        REQUIRE(deque.front() == 3);
        REQUIRE(deque.back() == 6);

        // Verify the order of elements
        REQUIRE(deque.front() == 3);
        deque.pop_front();
        REQUIRE(deque.front() == 4);
        deque.pop_front();
        REQUIRE(deque.front() == 5);
        deque.pop_front();
        REQUIRE(deque.front() == 6);
        deque.pop_front();

        REQUIRE(deque.empty());
    }

    SECTION("Mix of push and pop operations")
    {
        deque.push_back(1);
        deque.push_front(0);
        deque.push_back(2);
        deque.push_front(-1);

        REQUIRE(deque.size() == 4);
        REQUIRE(deque.front() == -1);
        REQUIRE(deque.back() == 2);

        deque.pop_back();
        REQUIRE(deque.back() == 1);

        deque.pop_front();
        REQUIRE(deque.front() == 0);

        deque.push_back(3);
        REQUIRE(deque.back() == 3);
    }

    SECTION("Exception safety with non-default-constructible types")
    {
        CircularDeque<std::string, 3> stringDeque;

        stringDeque.push_back("hello");
        stringDeque.push_front("world");

        REQUIRE(stringDeque.front() == "world");
        REQUIRE(stringDeque.back() == "hello");

        stringDeque.pop_back();
        REQUIRE(stringDeque.back() == "world");

        stringDeque.pop_front();
        REQUIRE(stringDeque.empty());
    }
}
