#include <bits/stdc++.h>
using namespace std;
struct Edge{
    int src, dest, weight;
};
struct Graph{
    int V, E;
    Edge* edge;
};
struct Graph* createGraph(int V, int E){
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge;
    return graph;
}
void printArr(int dist[], int n){
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
void BellmanFord(struct Graph* graph, int src){
    int V = graph->V;
    int E = graph->E;
    int dist[V];
    for (int i = 0; i < V; i++)
        dist[i]   = INT_MAX;
    dist[src] = 0;
    for (int i = 1; i <= V-1; i++){
        for (int j = 0; j < E; j++){
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
    for (int i = 0; i < E; i++){
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            printf("Graph contains negative weight cycle");
    }
    printArr(dist, V);
    return;
}
int main(){
    int V, E;
    cin>>V>>E;
    Graph* graph = createGraph(V, E);
    int src, dest, cost;
    for(int i = 0; i<E; i++){
    	cin>>src>>dest>>cost;
    	src--;
    	dest--; // zero based indexing
        graph->edge[i].src = src;
        graph->edge[i].dest = dest;
        graph->edge[i].weight = cost;
    }
    int start_s = clock();
    BellmanFord(graph, 0);
    int stop_s=clock();
    cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
    return 0;
}
/*
V E T
50 200 0.263
100 500 1.043
150 600 1.427
200 800 2.505
300 900 3.496
400 1000 5.111
500 1500 13.178
600 1800 14.575
*/
