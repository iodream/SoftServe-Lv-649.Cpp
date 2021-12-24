#include "Node.hpp"

Node NodeConstruct(const char* str, Node node)
{
    if (str) {
        Node new_node = static_cast<Node>(malloc(node_size));

        if (new_node) {
            NodeSetData(new_node, StringCopy(str));
            NodeSetNext(new_node, node);
            return new_node;
        }
    }
    return nullptr;
}

void NodeDestroy(Node node)
{
    if (node) {
        StringDestroy(NodeData(node));
        free(node);
    }
}

char* NodeData(Node node)
{
    if (node) {
        return *node;
    }

    return nullptr;
}

void NodeSetData(Node node, char*  str)
{
    if (node) {
        *node = str;
    }
}

Node NodeNext(Node node)
{
    return *reinterpret_cast<Node*>(node + 1);
}

void NodeSetNext(Node node, Node next)
{
    *reinterpret_cast<Node*>(node + 1) = next;
}
