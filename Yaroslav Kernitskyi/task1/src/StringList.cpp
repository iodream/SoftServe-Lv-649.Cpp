#include "StringList.hpp"

static Node StringListHead(StringList* list)
{
    return *list;
}

static void StringListSetHead(StringList* list, Node head)
{
    *list = head;
}

StringList StringListCreateSingleton(const char* str)
{
    return NodeConstruct(str, nullptr);
}

bool StringListIsSingleton(StringList head)
{
    return head && !NodeNext(head);
}

Node StringListLastNode(StringList head)
{
    while (!StringListIsSingleton(head)) {
        head = NodeNext(head);
    }

    return head;
}

void StringListInit(StringList* list)
{
    StringListSetHead(list, nullptr);
}

void StringListDestroy(StringList* list)
{
    Node head = StringListHead(list);

    while (head) {
        Node next = NodeNext(head);
        NodeDestroy(head);
        head = next;
    }

    StringListSetHead(list, nullptr);
}

void StringListPushFront(StringList* list, const char*  str)
{
    if (str) {
        StringListSetHead(list, NodeConstruct(str, StringListHead(list)));
    }
}

void StringListPushBack(StringList* list, const char*  str)
{
    if (str) {
        Node head = StringListHead(list);

        if (head) {
            NodeSetNext(StringListLastNode(head), StringListCreateSingleton(str));
        } else {
            StringListSetHead(list, StringListCreateSingleton(str));
        }
    }
}

// Helper for removal
static void StringListRemoveAllButFirst(StringList head, const char* str)
{
    if (head) {
        Node previous = head;
        Node current = NodeNext(head);
        while (current) {
            if (StringEqual(NodeData(current), str)) {
                Node next = NodeNext(current);
                NodeDestroy(current);
                NodeSetNext(previous, next);
                current = next;
            } else {
                Node next = NodeNext(current);
                previous = current;
                current = next;
            }
        }
    }
}

void StringListRemoveAll(StringList* list, const char* str)
{
    if (str) {
        Node head = StringListHead(list);

        if (head) {
            StringListRemoveAllButFirst(head, str);

            // Special case for first element
            if (StringEqual(NodeData(head), str)) {
                Node next = NodeNext(head);
                NodeDestroy(head);
                StringListSetHead(list, next);
            }
        }
    }
}

int StringListSize(StringList head)
{
    int size = 0;
    while (head) {
        head = NodeNext(head);
        size++;
    }

    return size;
}

int StringListIndexOf(StringList head, const char* str)
{
    if (str) {
        int index = 0;
        while (head) {
            if (StringEqual(NodeData(head), str)) {
                return index;
            }
            head = NodeNext(head);
            index++;
        }
    }

    return -1;
}

void StringListRemoveDuplicates(StringList head)
{
    while (head) {
        StringListRemoveAllButFirst(head, NodeData(head));
        head = NodeNext(head);
    }
}

void StringListReplaceInStrings(StringList head, const char* before, const char*  after)
{
    if (before && after) {
        while (head) {
			char* new_string = StringReplace(NodeData(head), before, after);
			
			if (new_string) {
				char* old_string= NodeData(head);
				NodeSetData(head, new_string);
				StringDestroy(old_string);
			}

            head = NodeNext(head);
        }
    }
}

// Helper for sort
static void StringListInsertNodeIntoSortedList(StringList head, Node node)
{
	while (head && StringLess(NodeData(node), NodeData(head))) {
		char* tmp = NodeData(head);
		NodeSetData(head, NodeData(node));
		NodeSetData(node, tmp);
		
		head = NodeNext(head);
	}
	
}

void StringListSort(StringList head)
{
	if (head) {
		Node current = NodeNext(head);

		while (current) {
			StringListInsertNodeIntoSortedList(head, current);
			current = NodeNext(current);
		}
	}
}