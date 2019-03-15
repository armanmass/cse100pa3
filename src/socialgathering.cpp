/*
Arman Massoudian
3/7/2019
Driver method takes input files builds graph finds kcore nodes.
PA3
*/
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"

using namespace std;

void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " friendship_pairs_file k_value output_file"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    usage(argv[0]);
  }
  char* graph_filename = argv[1];
  char* output_filename = argv[3];
  //istringstream ss(argv[2]);

 //call social gathering
  Graph g;
  vector<int> invite; //store ids of kcore nodes
  ofstream o;
  o.open(output_filename);
  const int k = std::stoi(argv[2]);

  g.loadFromFile(graph_filename);
  g.socialgathering(invite, k);

  for(size_t i = 0; i < invite.size(); i++)
      o << invite[i] << endl;

  o.close();

  return 0;
}