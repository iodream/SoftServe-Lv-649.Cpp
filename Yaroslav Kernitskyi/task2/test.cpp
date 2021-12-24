#include "AnyType.hpp"
#include <catch2/catch_test_macros.hpp>

struct DummyType
{
};

TEST_CASE("max_size", "[Utils]")
{
    REQUIRE(max_size<int> == sizeof(int));
    REQUIRE(max_size<int, int> == sizeof(int));
    REQUIRE(max_size<bool, int> == sizeof(int));
}

TEST_CASE("get_type_index", "[Utils]")
{
    REQUIRE(get_type_index<int, int> == 0);
    REQUIRE(get_type_index<int, float, int> == 1);
    REQUIRE(get_type_index<int, int, int> == 0);
}

TEST_CASE("is_in_list", "[Utils]")
{
    REQUIRE_FALSE(is_in_list<int>);
    REQUIRE(is_in_list<int, int>);
    REQUIRE(is_in_list<int, float, int>);
}

TEST_CASE("distinct", "[Utils]")
{
    REQUIRE(distinct<int>);
    REQUIRE_FALSE(distinct<int, int>);
    REQUIRE(distinct<int, float>);
}

TEST_CASE("AnyType constructor", "[AnyType]")
{
    int num = 12345;
    AnyType x(num);
    REQUIRE(x.contains<int>());
    REQUIRE(x.to<int>() == num);
}

TEST_CASE("AnyType assignment", "[AnyType]")
{
    int num = 12345;
    AnyType x(true);
    x = num;
    REQUIRE(x.contains<int>());
    REQUIRE(x.to<int>() == num);
}

TEST_CASE("AnyType copy constructor", "[AnyType]")
{
    AnyType y(12345);
    AnyType x(y);

    REQUIRE(x.contains<int>());
    REQUIRE(x.to<int>() == y.to<int>());
}

TEST_CASE("AnyType copy assignment", "[AnyType]")
{
    AnyType y(12345);
    AnyType x(false);
    x = y;

    REQUIRE(x.contains<int>());
    REQUIRE(x.to<int>() == y.to<int>());
}

TEST_CASE("AnyType move constructor", "[AnyType]")
{
    int num = 12345;
    AnyType y(num);
    AnyType x(std::move(y));

    REQUIRE(x.contains<int>());
    REQUIRE(x.to<int>() == num);
}

TEST_CASE("AnyType move assignment", "[AnyType]")
{
    int num = 12345;
    AnyType y(num);
    AnyType x(false);
    x = std::move(y);

    REQUIRE(x.contains<int>());
    REQUIRE(x.to<int>() == num);
}

TEST_CASE("AnyType swap", "[AnyType]")
{
    int a = 12345;
    float b = 0.12345f;
    AnyType x(a);
    AnyType y(b);

    x.swap(y);

    REQUIRE(x.contains<float>());
    REQUIRE(x.to<float>() == b);

    REQUIRE(y.contains<int>());
    REQUIRE(y.to<int>() == a);
}

TEST_CASE("Empty AnyType contains", "[AnyType]")
{
    AnyType x;
    REQUIRE_FALSE(x.contains<bool>());
    REQUIRE_FALSE(x.contains<int>());
    REQUIRE_FALSE(x.contains<float>());
}

TEST_CASE("AnyType contains dummy type", "[AnyType]")
{
    AnyType x(12345);
    REQUIRE_FALSE(x.contains<DummyType>());
}

TEST_CASE("AnyType destroy", "[AnyType]")
{
    AnyType x(12345);
    REQUIRE(x.contains<int>());
    x.destroy();
    REQUIRE_FALSE(x.contains<int>());
}

TEST_CASE("AnyType cast exception", "[AnyType]")
{
    AnyType x(12345);
    REQUIRE(x.contains<int>());
    REQUIRE_THROWS_AS(x.to<float>(), BadAnyTypeAccess);
}