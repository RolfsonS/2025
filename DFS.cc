#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <stack>

bool dfs(int source, int destination, std::unordered_map<int, std::vector<int>>& nodes, std::unordered_set<int>& visited) {
    // first check if the source vertex is destination vertex
    if (source == destination) {
        return true;
    }

    // Add the source vertex to the set
    visited.insert(source);

    // iterate through the neighbors of the vertex
    // If not visited, recursively perform dfs
    for (auto neighbor : nodes[source]) {
        if(visited.find(neighbor) == visited.end()) {
            if(dfs(neighbor, destination, nodes, visited)) {
                return true;
            }
        }
    }
    return false;
}

bool dfsIterative(int source, int destination, std::unordered_map<int, std::vector<int>>& nodes, std::unordered_set<int>& visited) {
    std::stack<int> dfsStack;

    dfsStack.push(source);

    while (!dfsStack.empty()) {
        int current = dfsStack.top();
        dfsStack.pop();

        if(current == destination) {
            return true;
        } 

        if (visited.find(current) == visited.end()) {
            visited.insert(current);
            for (auto neighbor : nodes[current]) {
                dfsStack.push(neighbor);
            }
        }
    }
    return false;
}

bool checkRoute(std::vector<std::vector<int>> edges, int destination, int source) {
    // Create an adjacency list for the vertices
    std::unordered_map<int, std::vector<int>> map;

    // Iterate through the edges, add to map to create the list
    for(const auto& edge : edges) {
        int firstDirection = edge[0];
        int secondDirection = edge[1];
        map[firstDirection].push_back(secondDirection);
        map[secondDirection].push_back(firstDirection);
    }

    // Create a set for the visited vertices
    std::unordered_set<int> visited;
    return dfsIterative(source, destination, map, visited);
}

int main() {
    std::vector<std::vector<int>> graph = {{1,2}, {2,3}};

    bool check = checkRoute(graph, 3, 1);

    if(check) {
        std::cout << "A path exists" << std::endl;
    } else {
        std::cout << "No path exist" << std::endl;
    }

    return 0;
}