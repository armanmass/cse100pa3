/*  
Arman Massoudian
3/7/2019
Graph Header
PA3
*/
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include "Node.hpp"

using namespace std;

class NodePtrComp {
  public:
    bool operator()(Node*& lhs, Node*& rhs) const {
        return *lhs < *rhs;
    }
};

class Graph {
 public:
  std::unordered_map<int, Node*> nodeMap;

  Graph();

  ~Graph();

  //MAYBE ADD SOME MORE METHODS HERE SO AS TO ANSWER QUESTIONS IN YOUR PA
  void addNode(int idNumber, int neighbor);
	
  Node* getNode(int id);
  
  /* YOU CAN MODIFY THIS IF YOU LIKE , in_filename : THE INPUT FILENAME */

  bool loadFromFile(const char* in_filename);

  bool pathfinder(Node* from, Node* to, ostream & o);
    
  void socialgathering(vector<int>& invitees, const int& k);
  
};

#endif  // GRAPH_HPP
