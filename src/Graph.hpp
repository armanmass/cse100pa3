#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include "Node.hpp"

using namespace std;

class Graph {
 protected:
  //MAYBE ADD CLASS DATA STRUCTURE(S) HERE

 public:
  std::unordered_map<int, Node*> nodeMap;

  Graph(void);

  ~Graph(void);

  //MAYBE ADD SOME MORE METHODS HERE SO AS TO ANSWER QUESTIONS IN YOUR PA
  bool addNode(int idNumber, int neighbor);
	
  Node* getNode(int id);
  /* YOU CAN MODIFY THIS IF YOU LIKE , in_filename : THE INPUT FILENAME */

  bool loadFromFile(const char* in_filename);

  bool pathfinder(Node* from, Node* to, ostream & o);
    
  void socialgathering(vector<string>& invitees, const int& k);

};

#endif  // GRAPH_HPP
