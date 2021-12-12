#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "String.hpp"

#include <cstdlib>

using Node = char**;
const size_t node_size = sizeof(char*) + sizeof(Node);

// List node interface
Node NodeConstruct(const char*  str, Node node);
void NodeDestroy(Node node);

bool NodeIsEmpty(Node node);

char* NodeData(Node node);
void NodeSetData(Node node, char*  str);

Node NodeNext(Node node);
void NodeSetNext(Node node, Node next);

#endif // NODE_H_INCLUDED
