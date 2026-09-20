#include <iostream>
using namespace std;

#define MAX 100

int parent[MAX], rankArr[MAX];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]); 
    return parent[x];
}

bool unite(int x, int y) {
    int rootX = find(x), rootY = find(y);
    if (rootX == rootY) return false; 

    if (rankArr[rootX] < rankArr[rootY]) {
        int temp = rootX;
        rootX = rootY;
        rootY = temp;
    }
    parent[rootY] = rootX;
    if (rankArr[rootX] == rankArr[rootY]) rankArr[rootX]++;
    return true;
}

struct Edge {
    int u, v, weight;
};

void sortEdges(Edge edges[], int e) {
    for (int i = 0; i < e - 1; i++) {
        for (int j = 0; j < e - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, e;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> e;

    Edge edges[MAX];
    cout << "Enter edges as: u v weight\n";
    for (int i = 0; i < e; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    sortEdges(edges, e);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rankArr[i] = 0;
    }

    int mstWeight = 0;

    cout << "Edges in MST:\n";
    for (int i = 0; i < e; i++) {
        if (unite(edges[i].u, edges[i].v)) {
            mstWeight += edges[i].weight;
            cout << edges[i].u << " - " << edges[i].v << " : " << edges[i].weight << endl;
        }
    }

    cout << "Total weight of MST: " << mstWeight << endl;

    return 0;
}
