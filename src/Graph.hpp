#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include "Node.hpp"

using namespace std;

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
    
  void socialgathering(vector<string>& invitees, const int& k);

};

#endif  // GRAPH_HPP
