#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int main() {
    int n;
    scanf("%d", &n);
    int cost[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == -1)
                cost[i][j] = INF;
        }
	}
    int totalMasks = 1 << n;
    int **dp = (int **)malloc(totalMasks * sizeof(int *));
    for (int i = 0; i < totalMasks; i++) {
        dp[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            dp[i][j] = INF;
	}
    dp[1][0] = 0;
    for (int mask = 1; mask < totalMasks; mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u)))
                continue;
            if (dp[mask][u] == INF)
                continue;
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v))
                    continue;
                if (cost[u][v] == INF)
                    continue;
                int newMask = mask | (1 << v);
                int newCost = dp[mask][u] + cost[u][v];
                if (newCost < dp[newMask][v])
                    dp[newMask][v] = newCost;
            }
        }
	}
    int fullMask = totalMasks - 1;
    int answer = INF;
    for (int i = 1; i < n; i++) {
        if (dp[fullMask][i] == INF)
            continue;
        if (cost[i][0] == INF)
            continue;
        int tourCost = dp[fullMask][i] + cost[i][0];
        if (tourCost < answer)
            answer = tourCost;
	}
    printf("%d\n", answer);
    for (int i = 0; i < totalMasks; i++)
        free(dp[i]);
    free(dp);
    return 0;
}
