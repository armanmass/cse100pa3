#include "Node.hpp"

Node::~Node() {
    delete prev;
    for(Node* n : neighbors)
        delete n;
}