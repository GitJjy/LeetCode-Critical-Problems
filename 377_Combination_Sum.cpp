/*
此题相对简单，相当于从输入数组nums中有放回地抽取元素，每次抽取都是独立的，且对应一个cur_target，
目标是计算所有和等于target的排列的个数，递归关系很明显：
dp[cur_target] = sum(dp[cur_target-nums[i]], if 0 <= i < nums.size() && cur_target - nums[i] >= 0)
需要注意的是dp[0] = 1，因为当cur_target等于0时说明前面已生成的排列已经满足条件，当前无需再取元素，故
只有一种可能，就是什么都不取， 另外由于排列数较大，dp的类型需要改为unsigned long long
 */
int combinationSum4(vector<int> &nums, int target)
{
    if (nums.empty())
        return 0;
    else
    {
        vector<unsigned long long int> dp(target + 1, 1); // initialize dp[0] to 1
        int n = nums.size();

        for (int cur_target = 1; cur_target <= target; cur_target++)
        {
            unsigned long long int cur_sum = 0; // current combination sum
            for (int i = 0; i < n; i++)
            {
                int rest_target = cur_target - nums[i];
                if (rest_target >= 0)
                    cur_sum += dp[rest_target];
            }
            dp[cur_target] = cur_sum;
        }

        return dp[target];
    }
}