/*
此题详见MIT算法导论课程笔记，代码如下：
 */

int minDistance(string word1, string word2)
{
    unsigned int m = word1.length(), n = word2.length();
    if (m == 0)
        return n;
    if (n == 0)
        return m;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++)
        dp[i][n] = m - i;
    for (int j = 0; j <= n; j++)
        dp[m][j] = n - j;

    for (int i = m - 1; i >= 0; i--)
    {
        for (int j = n - 1; j >= 0; j--)
        {

            int insert_cost = 1;
            int delete_cost = 1;
            int replace_cost = 1;
            int equal_cost = 0;

            if (word1[i] == word2[j])
            {

                equal_cost += dp[i + 1][j + 1];
                dp[i][j] = equal_cost;
            }

            else
            {

                delete_cost += dp[i + 1][j];
                replace_cost += dp[i + 1][j + 1];
                // equal_cost += dp[i+1][j+1];
                insert_cost += dp[i][j + 1];

                dp[i][j] = min(min(insert_cost, delete_cost), replace_cost);
            }
        }
    }

    return dp[0][0];
} /*
此题详见MIT算法导论课程笔记，代码如下：
 */

int minDistance(string word1, string word2)
{
    unsigned int m = word1.length(), n = word2.length();
    if (m == 0)
        return n;
    if (n == 0)
        return m;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++)
        dp[i][n] = m - i;
    for (int j = 0; j <= n; j++)
        dp[m][j] = n - j;

    for (int i = m - 1; i >= 0; i--)
    {
        for (int j = n - 1; j >= 0; j--)
        {

            int insert_cost = 1;
            int delete_cost = 1;
            int replace_cost = 1;
            int equal_cost = 0;

            if (word1[i] == word2[j])
            {

                equal_cost += dp[i + 1][j + 1];
                dp[i][j] = equal_cost;
            }

            else
            {

                delete_cost += dp[i + 1][j];
                replace_cost += dp[i + 1][j + 1];
                // equal_cost += dp[i+1][j+1];
                insert_cost += dp[i][j + 1];

                dp[i][j] = min(min(insert_cost, delete_cost), replace_cost);
            }
        }
    }

    return dp[0][0];
}