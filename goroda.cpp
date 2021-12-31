#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <tuple>
using namespace std;

class Graph {
public:
    Graph(int vertices_count, vector<tuple<int, int, int>>& edges){
        vertices.resize(vertices_count);
        for (auto [v1, v2, length] : edges){
            vertices[v1].push_back({v2, length});
            vertices[v2].push_back({v1, length});
        }
    }

    ~Graph(){}

    int VerticesCount() const{
        return vertices.size();
    }

    vector<pair<int, int>> GetNextVertices(int vertex) const{
        vector<pair<int, int>> result(vertices[vertex].begin(), vertices[vertex].end());
        return result;
    }

private:
    vector<vector<pair<int, int>>> vertices;
};

int find_shortest_path(const Graph& graph, int start, int finish){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    int inf = 1000 * 1000 * 1000;
    vector<int> path_length(graph.VerticesCount(), inf);

    path_length[start] = 0;
    q.push({0, start});
    while(!q.empty()){
        auto [length, v] = q.top();
        q.pop();
        if (length > path_length[v]) continue;

        vector<pair<int, int>> children = graph.GetNextVertices(v);
        for (auto& child : children){
            if (path_length[child.first] > length + child.second) {
                path_length[child.first] = length + child.second;
                q.push({path_length[child.first], child.first});
            }

        }
    }
    return path_length[finish];
}


int main(){
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    int vertices_count = 0, edge_count = 0;
    vector<tuple<int, int, int>> edges;
    cin >> vertices_count >> edge_count;
    for (int i = 0; i < edge_count; i++){
        int v1 = 0, v2 = 0, length = 0;
        cin >> v1 >> v2 >> length;
        edges.push_back({v1, v2, length});
    }
    int start = 0, finish = 0;
    cin >> start >> finish;

    Graph graph(vertices_count, edges);

    cout << find_shortest_path(graph, start, finish);

    return 0;
}
