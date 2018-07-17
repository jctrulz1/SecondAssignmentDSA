#ifndef GRAPH_ALGS
#define GRAPH_ALGS

#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <utility>
#include <algorithm>
#include "weighted_graph.hpp"
#include "easy_weighted_graph_algorithms.cpp"

#include "abstraction.cpp"

//Returns true if the graph is connected, false otherwise.
template <typename vertex>
bool is_connected(const weighted_graph<vertex>& g){
    int NumOfVertices = g.num_vertices();
    int NumOfEdges = g.num_edges();

    std::vector<vertex> GraphVertices;

    if(NumOfVertices == 0 && NumOfEdges == 0)
        return true;	

    if(NumOfVertices > 0 ) {
        GraphVertices = depth_first(g, *g.begin());
        if(NumOfVertices == GraphVertices.size()) {
            return true;
        }
    }

    return false;
}

//Returns a vector of weighted graphs, where each weighted graph is a connected
//component of the input graph.
template <typename vertex>
std::vector<weighted_graph<vertex>> connected_components(const weighted_graph<vertex>& g){
    std::vector<weighted_graph<vertex>> result;
    std::unordered_set<vertex> visitedVertex;
    vertex startingVertex;
    //Begin by iterating over the vertices of graph g
    for(auto g_vertex = g.begin(); g_vertex != g.end(); g_vertex++) {
        //Pick an unvisited vertex and use that to start the traversal
        if(!ContainVertex(*g_vertex, visitedVertex)) {
            startingVertex = *g_vertex;
            //Create a vector to store the vertices returned by traversal
            std::vector<vertex> TraversalVertex;
            //Start traversal on unvisited vertex
            TraversalVertex = depth_first(g, startingVertex);
            //Mark the vertices as visited
            visitedVertex.insert(TraversalVertex.begin(), TraversalVertex.end());
            //Create a temporary weighted graph
            weighted_graph<vertex> TempGraph;
            //Add the vertices in traveral vertex to the vertices of the temporary graph
            for(auto traversal_vertex = TraversalVertex.begin(); traversal_vertex != TraversalVertex.end(); traversal_vertex++) {
                TempGraph.add_vertex(*traversal_vertex);
            }
            //Add the edges to the weighted graph by using neighbour iterators on the temp graph vertices 
            for(auto temp_vertex = TempGraph.begin(); temp_vertex != TempGraph.end(); temp_vertex++) {
                for(auto temp_neighbour_vertex = g.neighbours_begin(*temp_vertex); temp_neighbour_vertex != g.neighbours_end(*temp_vertex); temp_neighbour_vertex++) {
                    TempGraph.add_edge(*temp_vertex, GetVertex(*temp_neighbour_vertex), g.get_edge_weight(*temp_vertex, GetVertex(*temp_neighbour_vertex)));
                }
            }
            //Add the temp graph to resulting vector
            result.push_back(TempGraph);
        }
    }

    return  result;
}



//Returns a map of the vertices of the weighted graph g and their distances from
//the given starting vertex v.
template <typename vertex> 
std::map<vertex, int> dijkstras(const weighted_graph<vertex>& g, const vertex& v){
     //initiaze table for dijkstra's algorithm
	if(g.num_vertices() == 0) {
		return std::map<vertex, int>();
	}
    std::map<vertex, int > shortestPathTable;
    for(auto graphVertices = g.begin(); graphVertices != g.end(); graphVertices++) {
        shortestPathTable[*graphVertices] = -1; // -1 to represent infinity
    }
    shortestPathTable[v] = 0;
	
    //create a table to keep track of visited vertices
    std::unordered_set<vertex> visitedVertices;
    //keep track of current vertex
    vertex currentVertex = v;
    //while visitedVertex size does not equal to the number of graph vertices
    while(visitedVertices.size() != g.num_vertices()) {
        for(auto unvisited_neighbour = g.neighbours_begin(currentVertex); unvisited_neighbour != g.neighbours_end(currentVertex); unvisited_neighbour++) {
            //add the edge weight between the current and neighbour vertices with the distance from the table;
			if(!ContainVertex(GetVertex(*unvisited_neighbour), visitedVertices)) {
            	int newPathDistance = g.get_edge_weight(currentVertex, GetVertex(*unvisited_neighbour)) + shortestPathTable[currentVertex];
				int currentPathDistance = shortestPathTable[GetVertex(*unvisited_neighbour)];
            	//if that distance is smaller than the distance stored in the table, replace
				if(IsFirstLessThanSecond(newPathDistance, currentPathDistance)) {
					currentPathDistance = newPathDistance;
					shortestPathTable[GetVertex(*unvisited_neighbour)] = currentPathDistance;
				}
			}
        }
		//mark vertex as visited
		visitedVertices.insert(currentVertex);
		//set current vertex to the smallest tentative distance
		currentVertex = SmallestDistance(shortestPathTable, visitedVertices);
    }

    return shortestPathTable;
}

//Returns a vector containing all the articulation points of the
template <typename vertex>
std::vector<vertex> articulation_points(const weighted_graph<vertex>& g){
    //copy g to a new weighted_graph
    weighted_graph<vertex> tempGraph = g;
    //create a vector for articulation points 
    std::vector<vertex> articulationPoints;
    //for each graph vertex;
    for(auto graphVertex = g.begin(); graphVertex != g.end(); graphVertex++) {
    //  remove vertex
        tempGraph.remove_vertex(*graphVertex);
    //  if(is_connected(g)
        if(!is_connected(tempGraph)) {
    //      add vertex to vector of articulation points
            articulationPoints.push_back(*graphVertex);
        }
    //  add vertex back to the graph
        tempGraph = g;
    }
    return articulationPoints;	
	
}
#endif



