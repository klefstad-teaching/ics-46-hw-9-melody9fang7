#include "dijkstras.h"

int main(){
    Graph g;
    file_to_graph("src/small.txt", g);
    int source = 0;
    int destination = 4;

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(g, source, previous);

    vector<int> path = extract_shortest_path(distances, previous, destination);
    cout << "\nPath from " << source << " to " << destination << ":\n";
    print_path(path, distances[destination]);
    return 0;
}