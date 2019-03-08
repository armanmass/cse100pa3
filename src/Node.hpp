#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    int id;
    Node* prev;
    bool visited;
    std::vector<Node*> neighbors;

    Node(int id,
        Node* prev,
        bool visited,
        std::vector<Node*> neighbors)
        : id(id), prev(prev), visited(visited), neighbors(neighbors) { }

    ~Node() { }

};

#endif // NODE_HPP