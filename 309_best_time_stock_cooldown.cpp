/*
 * 这道题用了有限状态机的思想，巧妙至极，定义三种状态s0, s1, s2，分别表示等待买入股票、
 * 等待卖出股票、刚卖出即将cooldown这三种状态。详细解释见本题discuss板块。
 * 链接：
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/discuss/75928/Share-my-DP-solution-(By-State-Machine-Thinking)
 * 启发：动态规划有时候存在多组依赖关系，而且呈现周期性，此时不妨使用有限状态机解决
*/
int maxProfit(vector<int> &prices)
{
    int n = prices.size();
    if (n == 0)
        return 0;

    vector<int> s0(n, 0), s1(n, -prices[0]), s2(n, INT_MIN);
    for (int i = 1; i < n; i++)
    {
        s0[i] = max(s2[i - 1], s0[i - 1]);
        s1[i] = max(s0[i - 1] - prices[i], s1[i - 1]);
        s2[i] = s1[i - 1] + prices[i];
    }

    return max(s0[n - 1], s2[n - 1]);
}