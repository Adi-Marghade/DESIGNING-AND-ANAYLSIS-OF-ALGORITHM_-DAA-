#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



void kruskalMST(int **cost, int V)
{
    int parent[V];

    // Initialize each vertex as its own parent
    for (int i = 0; i < V; i++)
        parent[i] = i;

    int edges = 0, minCost = 0;

    while (edges < V - 1)
    {
        int min = INT_MAX;
        int u = -1, v = -1;

        // Find the minimum edge
        for (int i = 0; i < V; i++)
        {
            for (int j = i + 1; j < V; j++)
            {
                if (cost[i][j] < min)
                {
                    min = cost[i][j];
                    u = i;
                    v = j;
                }
            }
        }

        // Find parent of u
        int a = u;
        while (parent[a] != a)
            a = parent[a];

        // Find parent of v
        int b = v;
        while (parent[b] != b)
            b = parent[b];

        // If no cycle, include edge
        if (a != b)
        {
            printf("Edge %d:(%d, %d) cost:%d\n", edges, u, v, min);
            minCost += min;
            parent[a] = b;
            edges++;
        }

        // Mark edge as processed
        cost[u][v] = cost[v][u] = INT_MAX;
    }

    printf("Minimum cost= %d\n", minCost);
}


int main() {
    int V;
    printf("No of vertices: ");
    scanf("%d", &V);

    int **cost = (int **)malloc(V * sizeof(int *));
}
