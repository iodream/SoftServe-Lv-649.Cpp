#include "StringList.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

static char* new_c_str(const char* str)
{
	size_t slen = strlen(str) + 1;
	char* res = reinterpret_cast<char*>(malloc(sizeof(char) * slen));
	return reinterpret_cast<char*>(memcpy(res, str, slen));
}

static string to_string(bool val)
{
	if (val)
		return string("true");
	return string("false");
}

static bool handle_test(const char* name, bool (*fn)())
{
	string line{" ------------- "};
	cout << "\n" << line << "testing: " << name << line << "\n";
	auto res = fn();
	cout << "\n" << line << "test passed: " << to_string(res) << line << "\n";
	return res;
}

static void print_list(StringList list)
{
	cout << "[";
	for (; StringListGetNxt(list); list = StringListGetNxt(list)) {
		cout << StringListGetVal(list) << ", ";
	}
	if (list)
		cout << StringListGetVal(list);
	cout << "]\n";
}

static bool cmp(StringList list, vector<string> tmpl)
{
	StringList node = list;
	if (static_cast<vector<string>::size_type>(StringListSize(list))
	 	!= tmpl.size()) {
			return false;
		}

	for (int i = 0; node; node = StringListGetNxt(node), i++) {
		if (string(StringListGetVal(node)) != tmpl[i]) {
			cout << "\"" << string(StringListGetVal(node)) << "\"";
			cout << " != " << "\"" << tmpl[i] << "\"";
			cout << " at index: " << i << "\n";
			return false;
		}
	}
	return true;
}

bool test_list_add()
{
	StringList list{nullptr};
	bool res{true};
	bool tmp;
	char* val;
	char** nxt;
	int size;

	cout << "List at the beginning:\n";
	print_list(list);

	res &= !( tmp = StringListAdd(&list, nullptr) );
	cout << "null string added to list: " << to_string(tmp) << "\n";
	res &= ( (size = StringListSize(list)) == 0 );
	cout << "list size: " << size << "\n\n";

	res &= ( tmp = StringListAdd(&list, new_c_str("string 1")) );
	cout << "valid string added to list: " << to_string(tmp) << "\n";
	res &= ( (size = StringListSize(list)) == 1 );
	cout << "list size: " << size << "\n";
	res &= ( string(val = StringListGetVal(list)) == string("string 1"));
	cout << "head node value: " << val << "\n";
	res &= !( nxt = StringListGetNxt(list) );
	cout << "head node next is null: " << to_string(!nxt) << "\n\n";

	res &= ( tmp = StringListAdd(&list, new_c_str("string 2")) );
	cout << "valid string added to list: " << to_string(tmp) << "\n";
	res &= ( (size = StringListSize(list)) == 2 );
	cout << "list size: " << size << "\n";
	res &= bool( nxt = StringListGetNxt(list) );
	cout << "head node next is null: " << to_string(!nxt) << "\n\n";

	cout << "list after insertions:\n";
	print_list(list);

	StringListDestroy(&list);
	cout << "list value after delteion is null: " << to_string(!list) << "\n";
	return res;
}

bool test_list_indexes()
{
	StringList list{nullptr};
	bool res{true};
	char*  val;
	char** tmp;
	int size;
	int idx;

	StringListAdd(&list, new_c_str("string 1"));
	StringListAdd(&list, new_c_str("string 2"));
	StringListAdd(&list, new_c_str("string 3"));
	StringListAdd(&list, new_c_str("string 4"));
	StringListAdd(&list, new_c_str("string 5"));
	cout << "list:\n";
	print_list(list);
	res &= ( (size = StringListSize(list)) == 5 );
	cout << "list size: " << size << "\n\n";

	res &= (( idx = StringListIndexOf(list, "string 1") ) == 0 );
	cout << "index of \"string 1\": " << idx << "\n";
	res &= (( idx = StringListIndexOf(list, "string 5") ) == 4 );
	cout << "index of \"string 5\": " << idx << "\n";
	res &= (( idx = StringListIndexOf(list, "string 6") ) == -1 );
	cout << "index of \"string 6\": " << idx << "\n\n";

	res &= (( tmp = StringListAtIndex(list, 1) )  != nullptr );
	cout << "node with index 1 exists: " << to_string(tmp) << "\n";
	res &= ( string(val = StringListGetVal(tmp)) == string("string 2"));
	cout << "value: " << val << "\n";

	res &= (( tmp = StringListAtIndex(list, 3) )  != nullptr );
	cout << "node with index 3 exists: " << to_string(tmp) << "\n";
	res &= ( string(val = StringListGetVal(tmp)) == string("string 4"));
	cout << "value: " << val << "\n";

	res &= (( tmp = StringListAtIndex(list, 10) ) == nullptr );
	cout << "node with index 10 exists: " << to_string(tmp) << "\n";

	StringListDestroy(&list);
	return res;
}

bool test_list_remove()
{
	StringList list{nullptr};
	bool res{true};
	int size;

	StringListAdd(&list, new_c_str("string 1"));
	StringListAdd(&list, new_c_str("string 2"));
	StringListAdd(&list, new_c_str("string 2"));
	StringListAdd(&list, new_c_str("string 3"));
	StringListAdd(&list, new_c_str("string 3"));
	StringListAdd(&list, new_c_str("string 4"));
	StringListAdd(&list, new_c_str("string 5"));
	StringListAdd(&list, new_c_str("string 5"));
	cout << "list:\n";
	print_list(list);
	res &= ( (size = StringListSize(list)) == 8 );
	cout << "list size: " << size << "\n\n";

	StringListRemove(&list, "string 4");
	cout << "list after removing \"string 4\":\n";
	print_list(list);
	res &= ( (size = StringListSize(list)) == 7 );
	cout << "list size: " << size << "\n\n";

	StringListRemove(&list, "string 1");
	cout << "list after removing \"string 1\":\n";
	print_list(list);
	res &= ( (size = StringListSize(list)) == 6 );
	cout << "list size: " << size << "\n\n";

	StringListRemoveDuplicates(list);
	cout << "list after removing duplicates:\n";
	print_list(list);
	res &= ( (size = StringListSize(list)) == 3 );
	cout << "list size: " << size << "\n\n";

	StringListAdd(&list, new_c_str("string 3"));
	cout << "list after adding \"string 3\":\n";
	print_list(list);
	res &= ( (size = StringListSize(list)) == 4 );
	cout << "list size: " << size << "\n\n";

	StringListDestroy(&list);
	return res;
}


bool test_list_replace()
{
	StringList list{nullptr};
	bool res{true};
	int size;

	StringListAdd(&list, new_c_str("string 1"));
	StringListAdd(&list, new_c_str("string 2"));
	StringListAdd(&list, new_c_str("string 3"));
	StringListAdd(&list, new_c_str("string 4"));
	StringListAdd(&list, new_c_str("string 5"));
	cout << "list:\n";
	print_list(list);
	res &= ( (size = StringListSize(list)) == 5 );
	cout << "list size: " << size << "\n\n";

	StringListReplaceInStrings(list, "string", "str");
	cout << "list after replacing \"string\" with \"str\":\n";
	print_list(list);

	StringListReplaceInStrings(list, "", "str");
	cout << "list after replacing \"\" with \"str\":\n";
	print_list(list);

	StringListReplaceInStrings(list, " ", "_");
	cout << "list after replacing \" \" with \"_\":\n";
	print_list(list);

	StringListDestroy(&list);
	return res;
}

bool test_list_sort_1()
{
	StringList list{nullptr};
	bool res{true};
	int size;

	StringListAdd(&list, new_c_str("5"));
	StringListAdd(&list, new_c_str("1"));
	StringListAdd(&list, new_c_str("2"));
	StringListAdd(&list, new_c_str("3"));
	StringListAdd(&list, new_c_str("4"));
	StringListAdd(&list, new_c_str("5"));
	StringListAdd(&list, new_c_str("1"));
	StringListAdd(&list, new_c_str("2"));
	StringListAdd(&list, new_c_str("3"));
	StringListAdd(&list, new_c_str("4"));
	StringListAdd(&list, new_c_str("5"));
	cout << "list:\n";
	print_list(list);
	size = StringListSize(list);
	cout << "list size: " << size << "\n\n";

	StringListSort(list);
	cout << "list after sotring:\n";
	print_list(list);

	res &= cmp(list,
			   vector<string>{
				   "1", "1", "2", "2", "3", "3", "4", "4", "5", "5", "5"});

	StringListDestroy(&list);
	return res;
}

bool test_list_sort_2()
{
	StringList list{nullptr};
	bool res{true};
	int size;

	StringListAdd(&list, new_c_str("b"));
	StringListAdd(&list, new_c_str("B"));
	StringListAdd(&list, new_c_str("2"));
	StringListAdd(&list, new_c_str("n"));
	StringListAdd(&list, new_c_str("4f"));
	StringListAdd(&list, new_c_str("L3"));
	StringListAdd(&list, new_c_str("."));
	StringListAdd(&list, new_c_str("d"));
	StringListAdd(&list, new_c_str("Z"));
	StringListAdd(&list, new_c_str("z"));
	StringListAdd(&list, new_c_str("0"));
	StringListAdd(&list, new_c_str(""));
	StringListAdd(&list, new_c_str("A"));
	StringListAdd(&list, new_c_str("a"));
	cout << "list:\n";
	print_list(list);
	size = StringListSize(list);
	cout << "list size: " << size << "\n\n";

	StringListSort(list);
	cout << "list after sotring:\n";
	print_list(list);

	res &= cmp(list,
			   vector<string>{
				   "", ".", "0", "2", "4f", "A", "B", "L3",
				   "Z", "a", "b", "d", "n", "z"});

	StringListDestroy(&list);
	return res;
}

bool test_list_sort_3()
{
	StringList list{nullptr};
	bool res{true};
	int size;

	StringListAdd(&list, new_c_str("5"));
	StringListAdd(&list, new_c_str("4"));
	StringListAdd(&list, new_c_str("3"));
	StringListAdd(&list, new_c_str("2"));
	StringListAdd(&list, new_c_str("1"));
	StringListAdd(&list, new_c_str("-1"));
	cout << "list:\n";
	print_list(list);
	size = StringListSize(list);
	cout << "list size: " << size << "\n\n";

	StringListSort(list);
	cout << "list after sotring:\n";
	print_list(list);

	res &= cmp(list, vector<string>{"-1", "1", "2", "3", "4", "5"});

	StringListDestroy(&list);
	return res;
}

bool test_list_remove_all()
{
	StringList list{nullptr};
	bool res{true};
	int size;

	StringListAdd(&list, new_c_str("Some string 1"));
	StringListAdd(&list, new_c_str("Some string 2"));
	StringListAdd(&list, new_c_str("Some string 3"));
	StringListAdd(&list, new_c_str("Some string 4"));
	StringListAdd(&list, new_c_str("Some string 5"));
	cout << "Before:\n";
	print_list(list);
	cout << "Size: " << StringListSize(list) << "\n";
	StringListRemove(&list, "Some string 1");
	StringListRemove(&list, "Some string 2");
	StringListRemove(&list, "Some string 3");
	StringListRemove(&list, "Some string 4");
	StringListRemove(&list, "Some string 5");
	StringListRemove(&list, "Some string 1");
	StringListRemove(&list, "");
	cout << "After:\n";
	print_list(list);
	res &= ( (size = StringListSize(list)) == 0);
	cout << "Size: " << size << "\n";
	res &= !list;
	cout << "list value after removing is null: " << to_string(!list) << "\n";
	StringListDestroy(&list);
	return res;
}

int main() {
	bool res{true};
	res &= handle_test("add", test_list_add);
	res &= handle_test("indexes", test_list_indexes);
	res &= handle_test("remove", test_list_remove);
	res &= handle_test("remove all", test_list_remove_all);
	res &= handle_test("replace", test_list_replace);
	res &= handle_test("sort 1", test_list_sort_1);
	res &= handle_test("sort 2", test_list_sort_2);
	res &= handle_test("sort 3", test_list_sort_3);
	cout << "\nAll tests passed: " << to_string(res) << "\n";
	return 0;
}
