#include "StringList.h"
#include <iostream>
using namespace std;

int main() {
	char** list = nullptr;

	StringListAdd(&list, _strdup("ijbnif"));
	StringListRemove(&list, "ijbnif");
	StringListDestroy(&list);

	StringListAdd(&list, _strdup("ijasdabniseff"));
	StringListAdd(&list, _strdup("ijbnsfsfif"));
	StringListAdd(&list, _strdup("ijbnif"));
	StringListAdd(&list, _strdup("ijbnief"));

	StringListPrint(list);

	StringListRemove(&list, "ijbnsfsfif");

	cout << StringListIndexOf(list, "ijbnif") << endl;
	cout << StringListSize(list) << endl;

	StringListRemoveAll(&list, "ijbnif");

	StringListPrint(list);

	return 0;
}