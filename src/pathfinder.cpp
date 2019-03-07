#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"
#include "Node.hpp"
using namespace std;

void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " friendship_pairs_file test_pairs_file output_file"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  
  if (argc != 4) {
    usage(argv[0]);
  }
  

  char* graph_filename = argv[1];
  char* pairs_filename = argv[2];
  char* output_filename = argv[3];

  //TODO   
 /* You can call the pathfinder function from here */

  Graph g = new Graph();
  ofstream o;
  o.open(argv[3]);

  g.loadFromFile(graph_filename);
  ifstream infile(pairs_filename);

  int id1;
  int id2;

  while (infile) {
    if (infile.peek() == -1) break;
    infile >> id1;
    infile >> id2;

    Node* n1 = g.getNode(id1);
    Node* n2 = g.getNode(id2);

    
  }


  o.close();

  return 0;
}  