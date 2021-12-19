#include <iostream>
#include "Task1.hpp"

using namespace std;

void TestIndex() {
	char string[10] = "string";
	char string1[10] = "string1";
	char string2[10] = "string2";
	char string3[10] = "string3";
	char string4[10] = "string4";

	char string5[10] = "aaaaaa";

	char** head = NULL;

	cout << "\n\n" << "\tTest of the function: StringlistIndexOf\n\n";
	StringListInit(&head, string);
	StringListAdd(head, string1);
	StringListAdd(head, string2);
	StringListAdd(head, string3);
	StringListAdd(head, string4);
	cout << "List:\n";
	ListShow(head);
	cout << "\n";
	cout << "Index of the " << "\"" << string << "\"" << " in the list : " << StringListIndexOf(head, string) << endl;
	cout << "Index of the " << "\"" << string1 << "\"" << " in the list: " << StringListIndexOf(head, string1) << endl;
	cout << "Index of the " << "\"" << string2 << "\"" << " in the list: " << StringListIndexOf(head, string2) << endl;
	cout << "Index of the " << "\"" << string3 << "\"" << " in the list: " << StringListIndexOf(head, string3) << endl;
	cout << "Index of the " << "\"" << string4 << "\"" << " in the list: " << StringListIndexOf(head, string4) << endl;
	cout << "Index of the " << "\"" << string5 << "\"" << " in the list: " << StringListIndexOf(head, string5) << endl;
	StringListDestroy(&head);
}

void TestRemove() {
	char string[10] = "string";
	char string1[10] = "string1";
	char string2[10] = "string";
	char string3[10] = "string3";
	char string4[10] = "string";

	char** head = NULL;

	cout << "\n\n" << "\tTest of the function: StringlistRemove\n\n";
	StringListInit(&head, string);
	StringListAdd(head, string1);
	StringListAdd(head, string2);
	StringListAdd(head, string3);
	StringListAdd(head, string4);
	cout << "List before removing:\n";
	ListShow(head);

	cout << endl << "List after removing " << "\"" << string << "\"" << endl;
	StringListRemove(&head, string);

	ListShow(head);
	StringListDestroy(&head);
}

void TestRemoveDuplicates() {
	char string[10] = "string";
	char string1[10] = "string1";
	char string2[10] = "string";
	char string3[10] = "string3";
	char string4[10] = "string";
	char string5[10] = "string1";

	char** head = NULL;

	cout << "\n\n" << "\tTest of the function: StringlistRemoveDuplicates\n\n";
	StringListInit(&head, string);
	StringListAdd(head, string1);
	StringListAdd(head, string2);
	StringListAdd(head, string3);
	StringListAdd(head, string4);
	StringListAdd(head, string5);
	cout << "List before removing duplicates:\n";
	ListShow(head);

	cout << endl << "List after removing duplicates " << endl;
	StringListRemoveDuplicates(head);

	ListShow(head);
	StringListDestroy(&head);
}

void TestSort() {
	char string[10] = "1";
	char string1[10] = "A";
	char string2[10] = "a";
	char string3[10] = "b";
	char string4[10] = "aa";
	char string5[10] = "ac";
	char string6[10] = "B";
	char string7[10] = "c";
	char** head = NULL;

	cout << "\n\n" << "\tTest of the function: StringlistSort\n\n";
	StringListInit(&head, string5);
	StringListAdd(head, string7);
	StringListAdd(head, string6);
	StringListAdd(head, string1);
	StringListAdd(head, string2);
	StringListAdd(head, string3);
	StringListAdd(head, string4);
	StringListAdd(head, string);
	cout << "List before sorting:\n";
	ListShow(head);

	cout << endl << "List after sorting " << endl;
	StringListSort(head);

	ListShow(head);
	StringListDestroy(&head);
}

void TestReplace() {
	char string[10] = "1string1";
	char string1[10] = "string1";
	char string2[10] = "AstringA";
	char string3[15] = "string3string";
	char string4[20] = "stringstringstring";
	char string5[10] = "String";

	char before[10] = "string";
	char after[10] = "str";

	char** head = NULL;

	cout << "\n\n" << "\tTest of the function: StringlistReplaceInStrings\n\n";
	StringListInit(&head, string);
	StringListAdd(head, string1);
	StringListAdd(head, string2);
	StringListAdd(head, string3);
	StringListAdd(head, string4);
	StringListAdd(head, string5);
	cout << "List before replacing:\n";
	ListShow(head);

	cout << endl << "List after replacing " << "\"" << before << "\" on " << "\"" << after << "\"" << endl;
	StringListReplaceInStrings(head, before, after);

	ListShow(head);
	StringListDestroy(&head);
}

int main() {
	TestIndex();
	TestRemove();
	TestRemoveDuplicates();
	TestSort();
	TestReplace();
	return 0;
}
