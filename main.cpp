#include <iostream>
#include "weighted_graph.hpp"
#include "graph_algorithms.cpp"
#include <unordered_set>

int main() {
	
weighted_graph<int> g;
	
	g.add_vertex(0);
  	g.add_vertex(1);
  	g.add_vertex(2);
 	g.add_vertex(3);
 	g.add_vertex(4);

    g.add_edge(0,1,1);
    g.add_edge(0,3,2);
    g.add_edge(1,2,8);
    g.add_edge(1,3,4);
    g.add_edge(2,4,2);
    g.add_edge(3,4,3);
	
	if(is_connected(g)) {
		std::cout << "Ye" << std::endl;
	}
	
//	for(auto it = g.begin(); it != g.end(); it++)
//	std::cout << *it << std::endl;

    std::unordered_map<int, int> num;

    num[7] = 0;
    num[3] = 1;
    num[5] = 2;


   

    std::cout << num[5] << std::endl;
	
}
