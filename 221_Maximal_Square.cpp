/*
这道题答案处理得特别巧妙，用“前缀”定义子问题。设dp[i][j]为以matrix[i][j]为右下角元素的所有正方形的最大
边长，则有如下递推公式：
    dp[i][j] = matrix[i][j] - '0',    if i==0 || j==0 || matrix[i][j] == '0'
    dp[i][j] = min(min(dp[i][j-1], dp[i-1][j]), dp[i-1][j-1]) + 1,  else
同时注意到，每次更新dp[i][j]时最多只用了当前位置的左边、上边和左上角的邻接元素，因此空间上也可以优化为
O(n)，此时需注意对左上角元素的保存。代码如下：
 */

int maximalSquare(vector<vector<char>> &matrix)
{

    if (matrix.empty())
    {
        return 0;
    }
    int m = matrix.size(), n = matrix[0].size();
    int pre_len = 0, up_left_len = 0; // left and up-left neighbor's max length
    vector<int> cur_lens(n, 0);       // current and pre rows' max lengths
    int max_len = 0;                  // global max length

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int temp = cur_lens[j]; // restore the up-left neighbor for next iteration
            if (i == 0 || j == 0 || matrix[i][j] == '0')
                cur_lens[j] = matrix[i][j] - '0';
            else
                cur_lens[j] = min(pre_len, min(up_left_len, cur_lens[j])) + 1;

            max_len = max(cur_lens[j], max_len);

            up_left_len = temp;
            pre_len = cur_lens[j];
        }
    }

    return max_len * max_len;
}

/*
我的思路：定义f(m, i, j)表示左上角坐标为(i, j)、边长为m的正方形区域是否全为'1'，
则有如下公式：
    f(m, i, j) = f(m-1, i, j) && f(m-1, i, j+1) && f(m-1, i+1, j) && f(m-1, i+1, j+1)
据此可自底向上比较得出满足全为'1'条件的最大的正方形。代码如下：
 */
int maximalSquare(vector<vector<char>> &matrix)
{
    int num_rows = matrix.size();
    if (num_rows == 0)
        return 0;

    int num_cols = matrix[0].size();
    // Upper bound for the side length of the square
    int len_upd = min(num_rows, num_cols);
    vector<vector<vector<bool>>> dp(len_upd, vector<vector<bool>>(num_rows, vector<bool>(num_cols, false)));
    int max_len = 0; // global max length

    // len = 1, 1 * 1 square
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            if (matrix[i][j] == '1')
            {
                dp[0][i][j] = true;
                max_len = 1;
            }
        }
    }

    // len > 1
    for (int len = 2; len <= len_upd; len++)
    {
        bool changed = false; // indicate whether the max_len has been updated
        for (int i = 0; i + len - 1 < num_rows; i++)
        {
            for (int j = 0; j + len - 1 < num_cols; j++)
            {
                dp[len - 1][i][j] = (dp[len - 2][i][j] && dp[len - 2][i][j + 1] && dp[len - 2][i + 1][j] && dp[len - 2][i + 1][j + 1]);
                if (dp[len - 1][i][j])
                {
                    max_len = len;
                    changed = true;
                }
            }
        }

        if (!changed)
            break;
    }

    return max_len * max_len;
}