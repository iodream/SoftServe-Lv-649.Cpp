#include "Task1.hpp"


void ListShow(char** list) {
	if (!list) {
		return;
	}

	while (list) {
		printf("%s\n", list[0]);
		list = (char**)list[1];
	}
}


int StringListSize(char** list) {

	if (!list) {
		return -1;
	}
	int counter = 0;
	while (list) {
		++counter;
		list = (char**)list[1];
	}
	return counter;
}


void CopyStr(char** node, char* text) {
	if (!node || !text) {
		return;
	}
	if (*node) {
		free(*node);
		*node = NULL;
	}
	*node = (char*)calloc(strlen(text) + 1, sizeof(char));

	if (!(*node)) {
		return;
	}
	strncpy(*node, text, strlen(text));
}


void StringListInit(char*** list, char* text)
{
	if (!list || !text) {
		return;
	}

	*list = (char**)calloc(2, sizeof(char*));
	if (!(*list)) {
		return;
	}
	CopyStr(*list, text);
}


void StringListAdd(char** list, char* text) {
	if (!list || !text) {
		return;
	}

	while (list[1]) {
		list = (char**)list[1];
	}

	list[1] = (char*)calloc(2, sizeof(char*));

	if (!list[1]) {
		return;
	}

	list = (char**)list[1];

	CopyStr(list, text);
}

void StringListRemove(char*** list, char* text) {
	if (!list || !text) {
		return;
	}

	while ((*list) && !strcmp((**list), text)) {

		char** temp = *list;
		*list = (char**)(*list)[1];;
		free(*temp);
		free(temp);
		temp = NULL;

	}

	if (*list && (*list)[1]) {
		char** previousNode = *list;
		char** currentNode = (char**)(*list)[1];
		while (previousNode[1]) {
			if (!strcmp(*currentNode, text)) {
				previousNode[1] = currentNode[1];
				free(*currentNode);
				free(currentNode);
				currentNode = (char**)previousNode[1];
			}
			else {
				previousNode = (char**)previousNode[1];
				currentNode = (char**)currentNode[1];
			}
		}
	}
}


void StringListDestroy(char*** list) {
	if (!list) {
		return;
	}

	char** nextNode = NULL;
	if (*list) {
		nextNode = (char**)(*list)[1];
	}
	while (*list) {
		free((*list)[0]);
		free(*list);
		*list = NULL;
		if (nextNode) {
			*list = nextNode;
			nextNode = (char**)nextNode[1];
		}
	}
}

int StringListIndexOf(char** list, char* text) {
	if (!list || !text) {
		return -1;
	}

	int index = 0;
	while (list) {
		if (!strcmp(*list, text)) {
			return index;
		}
		++index;
		list = (char**)list[1];
	}

	return -1;
}

void StringListRemoveDuplicates(char** list) {
	if (!list) {
		return;
	}
	if (StringListSize(list) < 2) {
		return;
	}
	while (list) {
		char** previousNode = list;
		char** nextNode = (char**)list[1];
		while (nextNode) {
			if (!strcmp(*list, *nextNode)) {
				previousNode[1] = nextNode[1];
				free(*nextNode);
				free(nextNode);
				nextNode = (char**)previousNode[1];
			}
			else {
				previousNode = (char**)previousNode[1];
				nextNode = (char**)nextNode[1];
			}
		}
		list = (char**)list[1];
	}
}

void StringListSort(char** list) {
	if (!list) {
		return;
	}
	if (StringListSize(list) < 2) {
		return;
	}
	while (list) {
		char** nextNode = (char**)list[1];
		while (nextNode != NULL) {
			if (strcmp(*list, *nextNode) > 0) {
				char* temp = *nextNode;
				*nextNode = *list;
				*list = temp;
				nextNode = (char**)nextNode[1];
			}
			else {
				nextNode = (char**)nextNode[1];
			}
		}
		list = (char**)list[1];
	}
}

void StringListReplaceInStrings(char** list, char* before, char* after) {
	if (!list || !before || !after) {
		return;
	}

	const int sizeBefore = strlen(before);
	const int sizeAfter = strlen(after);

	while (list) {
		if (strstr(*list, before) && sizeBefore) {
			char* tempPtr = *list;
			int quantityOfOccurrences = 0;
			while (strstr(*list, before)) {
				++quantityOfOccurrences;
				*list = strstr(*list, before) + sizeBefore;
			}
			*list = tempPtr;

			int sizeOfTempResult = strlen(*list) + quantityOfOccurrences * (sizeAfter - sizeBefore);
			char* tempResult = (char*)calloc(sizeOfTempResult + 1, sizeof(char));

			while (strstr(*list, before) && strlen(*list)) {

				int index = strlen(tempResult);
				int sizeOfCopy = strlen(*list) - strlen(strstr(*list, before));
				strncpy(tempResult + index, *list, sizeOfCopy);

				if (sizeAfter) {
					index = strlen(tempResult);
					strncpy(tempResult + index, after, sizeAfter);
				}
				*list = strstr(*list, before) + sizeBefore;
			}

			int index = strlen(tempResult);
			strncpy(tempResult + index, *list, strlen(*list));
			free(tempPtr);
			*list = (char*)calloc(strlen(tempResult) + 1, sizeof(char));
			if (!(*list)) {
				return;
			}
			strncpy(*list, tempResult, strlen(tempResult));
			free(tempResult);
			list = (char**)list[1];
		}
		else {
			list = (char**)list[1];
		}
	}
}
