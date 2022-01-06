#include "StringList.h"
#include <iostream>


void SizeAndIndexTest() {
	char** list = nullptr;

	// Add 8 elements
	StringListAdd(&list, _strdup("AddSomeText0"));
	StringListAdd(&list, _strdup("AddSomeText1"));
	StringListAdd(&list, _strdup("AddSomeText2"));
	StringListAdd(&list, _strdup("AddSomeText3"));
	StringListAdd(&list, _strdup("AddSomeText4"));
	StringListAdd(&list, _strdup("AddSomeText5"));
	StringListAdd(&list, _strdup("AddSomeText6"));
	StringListAdd(&list, _strdup("AddSomeText7"));

	StringListPrint(list);

	printf("Index of \"AddSomeText0\": %d\n", StringListIndexOf(list, "AddSomeText0"));
	printf("Index of \"AddSomeText1\": %d\n", StringListIndexOf(list, "AddSomeText1"));
	printf("Index of \"AddSomeText2\": %d\n", StringListIndexOf(list, "AddSomeText2"));
	printf("Index of \"AddSomeText3\": %d\n", StringListIndexOf(list, "AddSomeText3"));
	printf("Index of \"AddSomeText4\": %d\n", StringListIndexOf(list, "AddSomeText4"));
	printf("Index of \"AddSomeText5\": %d\n", StringListIndexOf(list, "AddSomeText5"));
	printf("Index of \"AddSomeText6\": %d\n", StringListIndexOf(list, "AddSomeText6"));
	printf("Index of \"AddSomeText7\": %d\n", StringListIndexOf(list, "AddSomeText7"));	
	printf("Index of \"SomeText\"    : %d\n", StringListIndexOf(list, "SomeText"));

	StringListDestroy(&list);
}


void TestRemoveAndRemoveForIndex() {
	char** list = nullptr;

	// Add 8 elements
	StringListAdd(&list, _strdup("AddSomeText0"));
	StringListAdd(&list, _strdup("AddSomeText1"));
	StringListAdd(&list, _strdup("AddSomeText2"));
	StringListAdd(&list, _strdup("AddSomeText3"));
	StringListAdd(&list, _strdup("AddSomeText4"));
	StringListAdd(&list, _strdup("AddSomeText5"));
	StringListAdd(&list, _strdup("AddSomeText6"));
	StringListAdd(&list, _strdup("AddSomeText7"));
	StringListPrint(list);

	printf("\n\n");

	StringListRemove(&list, "AddSomeText6");
	StringListRemoveForIndex(&list, 1);
	StringListPrint(list);

	StringListDestroy(&list);
}

void TestRemoveAll() {
	char** list = nullptr;

	// Add 8 elements
	StringListAdd(&list, _strdup("AddSomeText0"));
	StringListAdd(&list, _strdup("AddSomeText1"));
	StringListAdd(&list, _strdup("AddSomeText2"));
	StringListAdd(&list, _strdup("AddSomeText0"));
	StringListAdd(&list, _strdup("AddSomeText0"));
	StringListAdd(&list, _strdup("AddSomeText0"));
	StringListAdd(&list, _strdup("AddSomeText6"));
	StringListAdd(&list, _strdup("AddSomeText0"));
	StringListPrint(list);

	printf("\n\n");

	StringListRemoveAll(&list, "AddSomeText0");
	StringListPrint(list);

	StringListDestroy(&list);
}


void TestReplacing() {
	char** list = nullptr;

	// Add 8 elements
	StringListAdd(&list, _strdup("AddSomeText0"));
	StringListAdd(&list, _strdup("AddSomeText1"));
	StringListAdd(&list, _strdup("AddSomeText2"));
	StringListAdd(&list, _strdup("AddSomeText3"));
	StringListAdd(&list, _strdup("AddSomeText4"));
	StringListAdd(&list, _strdup("AddSomeText5"));
	StringListAdd(&list, _strdup("AddSomeText6"));
	StringListAdd(&list, _strdup("AddSomeText7"));
	StringListPrint(list);

	printf("\n\n");

	StringListReplaceInStrings(&list, _strdup("AddSomeText0"), _strdup("AddSomeText7"));
	StringListReplaceInStrings(&list, _strdup("AddSomeText1"), _strdup("AddSomeText6"));
	StringListReplaceInStrings(&list, _strdup("AddSomeText2"), _strdup("AddSomeText5"));
	StringListReplaceInStrings(&list, _strdup("AddSomeText3"), _strdup("AddSomeText4"));

	StringListPrint(list);

}


int main() {


	printf("--------------- StringSize and StringIndex TEST ----------------\n");
	SizeAndIndexTest();

	printf("--------------- StringRemove and StringRemoveForIndex TEST ----------------\n");
	TestRemoveAndRemoveForIndex();

	printf("--------------- StringRemoveAll TEST ----------------\n");
	TestRemoveAll();

	printf("--------------- StringReplace TEST ----------------\n");
	TestReplacing();

}