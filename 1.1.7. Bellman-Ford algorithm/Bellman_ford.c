#include <stdio.h>
#include <limits.h>

#define INF LLONG_MAX

typedef struct {
    int u, v;
    long long w;
} Edge;

void printPath(int parent[], int vertex) {
    int path[1001];
    int count = 0;

    while (vertex != -1) {
        path[count++] = vertex;
        vertex = parent[vertex];
    }

    for (int i = count - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0)
            printf("->");
    }
}

int main() {
    int V, E;

    scanf("%d", &V);
    scanf("%d", &E);

    Edge edges[E];

    for (int i = 0; i < E; i++) {
        scanf("%d %d %lld",
              &edges[i].u,
              &edges[i].v,
              &edges[i].w);
    }

    int src;
    scanf("%d", &src);

    long long dist[V + 1];
    int parent[V + 1];

    // Initialization
    for (int i = 1; i <= V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[src] = 0;

    // Bellman-Ford relaxation
    for (int i = 1; i <= V - 1; i++) {
        int updated = 0;

        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            long long w = edges[j].w;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                updated = 1;
            }
        }

        // Optimization: stop if no distance changed
        if (!updated)
            break;
    }

    // Check for a reachable negative-weight cycle
    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        long long w = edges[i].w;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("Negative cycle detected\n");
            return 0;
        }
    }

    // Print shortest distances and paths
    for (int v = 1; v <= V; v++) {
        if (v == src)
            continue;

        if (dist[v] == INF) {
            printf("%d INF None\n", v);
        } else {
            printf("%d %lld ", v, dist[v]);
            printPath(parent, v);
            printf("\n");
        }
    }

    return 0;
}

