#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous[source] = UNDEFINED;
    priority_queue <pair<int, int>> minHeap;
    minHeap.push({source, 0});
    while(!minHeap.empty()){
        int u = minHeap.extractVertexWithMinimumWeight().first;
        if(visited[u]) continue;
        visited[u] = true;
        for(Edge edge: G[u]){
            int v = edge.dest;
            int weight = edge.second;
            if(!visited[v] &&distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector <int> path;
    for (int v = destination; v != =1; v = previous[v]){
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}
void print_path(const vector<int>& v, int total){
    if (v.empty()){
        error("", "", "no path found");
        return;
    }
    cout 
     "shortest path: ";
    for(size_t i = 0; i < v.size(); i++){
        cout << v[i];
    }
    cout << "\ntotal weight: " << total << endl;
}