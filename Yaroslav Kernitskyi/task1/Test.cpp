#include "StringList.hpp"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <random>
#include <iostream>

using StringVector = std::vector<const char*>;

static StringList StringListFromVector(const StringVector& v)
{
    StringList list;
    StringListInit(&list);
    std::for_each(
        v.rbegin(),
        v.rend(),
        [list_ptr = &list](const char* str){StringListPushFront(list_ptr, str);});

    return list;
}

static bool StringListEqualToVector(StringList head, StringVector& v)
{
    if (StringListSize(head) != v.size()) {
        return false;
    }

    auto i = v.begin();

    while (head) {
        if (!StringEqual(*i, NodeData(head))) {
            return false;
        }
        ++i;
        head = NodeNext(head);
    }

    return true;
}

std::ostream& operator<< (std::ostream& os, StringList head)
{
    os << "(";
    if (head) {
        while (!StringListIsSingleton(head)) {
            os << "\"" << NodeData(head) << "\" ";
            head = NodeNext(head);
        }
        os << "\"" << NodeData(head) << "\"";
    }
    os << ")";

    return os;
}

std::ostream& operator<< (std::ostream& os, const StringVector& v)
{
    os << "(";

    if (!v.empty()) {
        for (auto i = v.begin(); i != std::prev(v.end()); ++i) {
            os << "\"" << *i << "\" ";
        }
        os << "\"" << v.back() << "\"";
    }
    os << ")";

    return os;
}

//--------------------------------------------------------------------------------

TEST_CASE("Push to front of empty list", "[StringListPushFront]") {
    StringList list;
    StringListInit(&list);

    StringListPushFront(&list, "Alice");
    REQUIRE(StringListEqualToVector(list, StringVector {"Alice"}));

    StringListDestroy(&list);
}

TEST_CASE("Push to front of non-empty list", "[StringListPushFront]") {
    StringList list = StringListFromVector(StringVector {"Alice"});

    StringListPushFront(&list, "Bob");
    REQUIRE(StringListEqualToVector(list, StringVector {"Bob", "Alice"}));

    StringListDestroy(&list);
}

TEST_CASE("Try to push empty string to front", "[StringListPushFront]") {
    StringList list = StringListFromVector(StringVector {"Charlie"});

    StringListPushFront(&list, nullptr);
    REQUIRE(StringListEqualToVector(list, StringVector {"Charlie"}));

    StringListDestroy(&list);
}

//--------------------------------------------------------------------------------

TEST_CASE("Push to back of empty list", "[StringListPushBack]") {
    StringList list;
    StringListInit(&list);

    StringListPushBack(&list, "Alice");
    REQUIRE(StringListEqualToVector(list, StringVector {"Alice"}));

    StringListDestroy(&list);
}

TEST_CASE("Push to back of non-empty list", "[StringListPushBack]") {
    StringList list = StringListFromVector(StringVector {"Alice"});

    StringListPushBack(&list, "Bob");
    REQUIRE(StringListEqualToVector(list, StringVector {"Alice", "Bob"}));

    StringListDestroy(&list);
}

TEST_CASE("Try to push empty string to back", "[StringListPushBack]") {
    StringList list = StringListFromVector(StringVector {"Charlie"});

    StringListPushBack(&list, nullptr);
    REQUIRE(StringListEqualToVector(list, StringVector {"Charlie"}));

    StringListDestroy(&list);
}

//--------------------------------------------------------------------------------

TEST_CASE("Remove from empty list", "[StringListRemoveAll]") {
    StringList list;
    StringListInit(&list);

    StringListRemoveAll(&list, "Dan");
    REQUIRE(StringListEqualToVector(list, StringVector {}));

    StringListDestroy(&list);
}

TEST_CASE("Remove missing value from list", "[StringListRemoveAll]") {
    StringList list = StringListFromVector(StringVector {"Dan", "Emily"});

    StringListRemoveAll(&list, "Fiona");
    REQUIRE(StringListEqualToVector(list, StringVector {"Dan", "Emily"}));

    StringListDestroy(&list);
}

TEST_CASE("Remove one present value from list", "[StringListRemoveAll]") {
    StringList list = StringListFromVector(StringVector {"Dan", "Chad", "Emily"});

    StringListRemoveAll(&list, "Chad");
    REQUIRE(StringListEqualToVector(list, StringVector {"Dan", "Emily"}));

    StringListDestroy(&list);
}

TEST_CASE("Remove multiple present values from list", "[StringListRemoveAll]") {
    StringList list = StringListFromVector(StringVector {"Chad", "Dan", "Chad", "Emily", "Chad"});

    StringListRemoveAll(&list, "Chad");
    REQUIRE(StringListEqualToVector(list, StringVector {"Dan", "Emily"}));

    StringListDestroy(&list);
}

//--------------------------------------------------------------------------------

TEST_CASE("Size of empty list", "[StringListSize]") {
    StringList list;
	StringListInit(&list);

    REQUIRE(StringListSize(list) == 0);

    StringListDestroy(&list);
}

TEST_CASE("Size of list after addition of element", "[StringListSize]") {
    StringList list = StringListFromVector(StringVector {"Felix", "Grimmjow", "Harry"});
	
	int size_before = StringListSize(list);
	StringListPushFront(&list, "David");
    REQUIRE(StringListSize(list) == size_before + 1);
	
	size_before = StringListSize(list);
	StringListPushBack(&list, "Ichigo");
    REQUIRE(StringListSize(list) == size_before + 1);
	
	size_before = StringListSize(list);
	StringListPushBack(&list, nullptr);
	REQUIRE(StringListSize(list) == size_before);
	
	size_before = StringListSize(list);
	StringListPushFront(&list, nullptr);
	REQUIRE(StringListSize(list) == size_before);

    StringListDestroy(&list);
}

TEST_CASE("Size of list after removal of element", "[StringListSize]") {
    StringList list = StringListFromVector(StringVector {"Kyle", "John", "Kyle", "Kyle"});
	
	int size_before = StringListSize(list);
	StringListRemoveAll(&list, "Matsumoto");
    REQUIRE(StringListSize(list) == size_before);
	
	size_before = StringListSize(list);
	StringListRemoveAll(&list, nullptr);
    REQUIRE(StringListSize(list) == size_before);
	
	size_before = StringListSize(list);
	StringListRemoveAll(&list, "John");
    REQUIRE(StringListSize(list) == size_before - 1);
	
	size_before = StringListSize(list);
	StringListRemoveAll(&list, "Kyle");
    REQUIRE(StringListSize(list) == size_before - 3);

    StringListDestroy(&list);
}

//--------------------------------------------------------------------------------

TEST_CASE("Index of element in empty list", "[StringListIndexOf]") {
    StringList list;
	StringListInit(&list);
    REQUIRE(StringListIndexOf(list, "Natali") == -1);
    StringListDestroy(&list);
}

TEST_CASE("Index of null string") {
    StringList list = StringListFromVector(StringVector {"Sam", "Thomas"});
    REQUIRE(StringListIndexOf(list, nullptr) == -1);
    StringListDestroy(&list);
}

TEST_CASE("Index of value missing in list", "[StringListIndexOf]") {
    StringList list = StringListFromVector(StringVector {"Oscar", "Patrick", "Quentin"});
    REQUIRE(StringListIndexOf(list, "Noah") == -1);
    StringListDestroy(&list);
}

TEST_CASE("Index of value present in list", "[StringListIndexOf]") {
    StringList list = StringListFromVector(StringVector {"Otto", "Patrick", "Quinn"});
    REQUIRE(StringListIndexOf(list, "Patrick") == 1);
    StringListDestroy(&list);
}

TEST_CASE("Index of value when multiple values are present in list", "[StringListIndexOf]") {
    StringList list = StringListFromVector(StringVector {"Rebecca", "Rose", "Rebecca"});
    REQUIRE(StringListIndexOf(list, "Rebecca") == 0);
    StringListDestroy(&list);
}

//--------------------------------------------------------------------------------

TEST_CASE("Remove duplicates in empty list", "[StringListRemoveDuplicates]") {
    StringList list;
	StringListInit(&list);
	
	StringListRemoveDuplicates(list);
    REQUIRE(StringListEqualToVector(list, StringVector {}));
	
    StringListDestroy(&list);
}

TEST_CASE("Remove duplicates in list with no duplicates", "[StringListRemoveDuplicates]") {
	auto init_vector = StringVector {"Urahara", "Ururu", "Ulquiorra"};
    StringList list = StringListFromVector(init_vector);
	
	StringListRemoveDuplicates(list);
    REQUIRE(StringListEqualToVector(list, init_vector));
	
    StringListDestroy(&list);
}

TEST_CASE("Remove duplicates in list with duplicates", "[StringListRemoveDuplicates]") {
    StringList list = StringListFromVector(StringVector {"Victoria", "Vanessa", "Victoria", "Vanessa"});
	
	StringListRemoveDuplicates(list);
    REQUIRE(StringListEqualToVector(list, StringVector {"Victoria", "Vanessa"}));
	
    StringListDestroy(&list);
}

//--------------------------------------------------------------------------------

TEST_CASE("Replace with empty list", "[StringListReplaceInStrings]") {
    StringList list;
	StringListInit(&list);
	
	StringListReplaceInStrings(list, "William", "Walter");
    REQUIRE(StringListEqualToVector(list, StringVector {}));
	
    StringListDestroy(&list);
}

TEST_CASE("Replace with null strings", "[StringListReplaceInStrings]") {
	auto init_vector = StringVector {"Yuri", "Yakov"};
    StringList list = StringListFromVector(init_vector);
	
	StringListReplaceInStrings(list, nullptr, "Xavier");
    REQUIRE(StringListEqualToVector(list, init_vector));
	
	StringListReplaceInStrings(list, "Xavier", nullptr);
    REQUIRE(StringListEqualToVector(list, init_vector));
	
    StringListDestroy(&list);
}

TEST_CASE("Replace string with no occurences in list", "[StringListReplaceInStrings]") {
	auto init_vector = StringVector {"Zoey", "Alexander"};
    StringList list = StringListFromVector(init_vector);
	
	StringListReplaceInStrings(list, "Beatrice", "Bea");
    REQUIRE(StringListEqualToVector(list, init_vector));
	
    StringListDestroy(&list);
}

TEST_CASE("Replace with empty string", "[StringListReplaceInStrings]") {
    StringList list = StringListFromVector(StringVector {"Columbus", "Christopher", "Christopher Columbus", "Christopher Columbus and Christopher Magellan are famous explorers"});
	
	StringListReplaceInStrings(list, "Christopher", "");
	
    REQUIRE(StringListEqualToVector(list, StringVector {"Columbus", "", " Columbus", " Columbus and  Magellan are famous explorers"}));
	
    StringListDestroy(&list);
}

TEST_CASE("Replace with longer string", "[StringListReplaceInStrings]") {
    StringList list = StringListFromVector(StringVector {"Columbus", "Fernand", "Fernand Columbus", "Fernand Columbus and Fernand Magellan are famous explorers"});
	
	StringListReplaceInStrings(list, "Fernand", "Christopher");
	
    REQUIRE(StringListEqualToVector(list, StringVector {"Columbus", "Christopher", "Christopher Columbus", "Christopher Columbus and Christopher Magellan are famous explorers"}));
	
    StringListDestroy(&list);
}

TEST_CASE("Replace with shorter string", "[StringListReplaceInStrings]") {
    StringList list = StringListFromVector(StringVector {"Columbus", "Christopher", "Christopher Columbus", "Christopher Columbus and Christopher Magellan are famous explorers"});
	
	StringListReplaceInStrings(list, "Christopher", "Fernand");
	
    REQUIRE(StringListEqualToVector(list, StringVector {"Columbus", "Fernand", "Fernand Columbus", "Fernand Columbus and Fernand Magellan are famous explorers"}));
	
    StringListDestroy(&list);
}

//--------------------------------------------------------------------------------

TEST_CASE("Sort empty list", "[StringListSort]") {
    StringList list;
	StringListInit(&list);
	
	StringListSort(list);
    REQUIRE(StringListEqualToVector(list, StringVector {}));
	
    StringListDestroy(&list);
}

TEST_CASE("Sort ordered list", "[StringListSort]") {
    auto ordered_vector = StringVector {"Aizen Sousuke", "Bartolomeo", "Connor"};
	StringList list = StringListFromVector(ordered_vector);
	
	StringListSort(list);
    REQUIRE(StringListEqualToVector(list, ordered_vector));
	
    StringListDestroy(&list);
}

TEST_CASE("Sort reverse ordered list", "[StringListSort]") {
	StringList list = StringListFromVector(StringVector {"Charlotte", "Barbara", "Adam"});
	
	StringListSort(list);
    REQUIRE(StringListEqualToVector(list, StringVector {"Adam", "Barbara", "Charlotte"}));
	
    StringListDestroy(&list);
}

TEST_CASE("Sort shuffled list", "[StringListSort]") {
	auto vec = StringVector {"Judas", "Isaac", "Azazel"};
	StringList list = StringListFromVector(vec);
	
	StringListSort(list);
	std::sort(std::begin(vec), std::end(vec), StringLess);
	
    REQUIRE(StringListEqualToVector(list, vec));
	
    StringListDestroy(&list);
}