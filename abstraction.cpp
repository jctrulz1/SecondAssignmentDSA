template<typename vertex>
vertex GetVertex(std::pair<vertex, int> pair) {
	return pair.first;
}

template<typename vertex>
vertex GetDistance(std::pair<vertex, int> pair) {
	return pair.second;
}

template<typename vertex>
bool ContainVertex(vertex v, std::unordered_set<vertex>& visitedVertices) {
	return visitedVertices.find(v) != visitedVertices.end();
}

bool IsFirstLessThanSecond(int& first, int& second) { //this is created because I used -1 to represent infinity. So if second is == -1, always return true
	if(second == -1) {
		return true;
	}
	else {
		return first < second;
	}
}

template<typename vertex>
int SmallestDistance(std::map<vertex, int>& table, std::unordered_set<vertex>& visitedVertices) {
    //sets minPath to a path that has not been visited yet and not infinity (-1) 
	std::pair<int, int> minPath;
	for(auto path = table.begin(); path != table.end(); path++) {
		if(!ContainVertex(GetVertex(*path), visitedVertices) && GetDistance(*path) != -1) {
			minPath = *path;
            break;
		}
	}
	//compare all the paths that have not been visited and not infinity and less than min path. Repeat until minPath is the minimum path
    for(auto path = table.begin(); path != table.end(); path++) {
        if(!ContainVertex(GetVertex(*path), visitedVertices) && GetDistance(*path) != -1) {
            if(GetDistance(*path) < GetDistance(minPath)) {
                minPath = *path;
            }
        }
    }

    return GetVertex(minPath);
}
