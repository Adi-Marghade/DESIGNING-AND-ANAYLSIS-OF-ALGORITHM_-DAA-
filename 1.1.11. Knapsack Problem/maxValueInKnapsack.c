include <stdio.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    int N, W;

    scanf("%d", &N);

    int value[N], weight[N];

    for (int i = 0; i < N; i++)
        scanf("%d", &value[i]);

    for (int i = 0; i < N; i++)
        scanf("%d", &weight[i]);

    scanf("%d", &W);

    int dp[W + 1];

    for (int i = 0; i <= W; i++)
        dp[i] = 0;

    for (int i = 0; i < N; i++)
    {
        for (int w = W; w >= weight[i]; w--)
        {
            dp[w] = max(dp[w], value[i] + dp[w - weight[i]]);
        }
    }

    printf("%d", dp[W]);

    return 0;
}
