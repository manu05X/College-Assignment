#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>

using namespace std;

const int n = 1e4 + 5;
int id[n], vertices, edges;
pair<int, pair<int, int> > p[n];
vector<int> connect[n];
bool visited[n];

void BFS(int root) {
    queue<int> q;
    q.push(root);
    visited[root] = true;
    while (!q.empty()) {
        int k = q.front();
        q.pop();
        int count = 0;
        int length = connect[k].size();
        for (int i = 0; i < length; i++) {
            if (count == 0)
                cout << k << " --> " << connect[k][i];
            else
                cout << " --> " << connect[k][i];
            count++;
        }
        cout << endl;
        for (int i = 0; i < length; i++) {
            if (!visited[connect[k][i]]) {
                q.push(connect[k][i]);
                visited[connect[k][i]] = true;
            }
        }
    }
    cout << endl;
}

int root(int x) {
    while (id[x] != x) {
        id[x] = id[id[x]];
        x = id[x];
    }
    return x;
}

void join(int x, int y) {
    int p = root(x);
    int q = root(y);
    id[p] = id[q];
}

void kruskal(pair<int, pair<int, int> > p[]) {
    int x, y;
    int k, helper = 0;
    for (int i = 0; i < edges; ++i) {
        x = p[i].second.first;
        y = p[i].second.second;
        k = p[i].first;

        if (root(x) != root(y)) {
            helper += k;
            join(x, y);
            connect[x].push_back(y);
            connect[y].push_back(x);
        }
    }
}

int main() {
    int x, y;
    int weight = 1, k, helper;
    int root;

    for (int i = 0; i < n; ++i)
        id[i] = i;

    cout << "Enter number of Vertices and edges of the graph: " << endl;
    cin >> vertices >> edges;

    cout << "Enter the connected vertices according to the no. of edges given in input: " << endl;
    for (int i = 0; i < edges; ++i) {
        cin >> x >> y;
        p[i] = make_pair(weight, make_pair(x, y));
    }
    cout << "Enter the root for the spanning tree below: " << endl;
    cin >> root;

    sort(p, p + edges);
    kruskal(p);

    for (int i = 0; i < n; i++)
        visited[i] = false;
    cout << "\nConsidering " << root << " as root" << endl;
    cout << "Displaying connectivity between vertices" << endl;
    cout << "************************" << endl;
    BFS(root);

    return 0;
}