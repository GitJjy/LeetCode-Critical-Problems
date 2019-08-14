/*
这道题答案方法比较巧妙，对于数组中每个元素nums[i]，有以下3种情况：
1、nums[i-1] < nums[i]，意味着以nums[i]为末尾的序列最后两个元素是“增长的”；
2、nums[i-1] == nums[i]，意味着i这个位置没有增长也没有下降；
3、nums[i-1] > nums[i]，类比于1.

定义up[i]为子数组up[:i+1]（Python记法）中最后两个元素是“增长”的最长wiggle序列的长度，
down[i]同理，则更新规则如下：
            if(nums[i-1] < nums[i]) // 此种情况下up[i]对应的序列必然包含nums[i]
            {   up[i] = down[i-1] + 1;
                down[i] = down[i-1];
            }
            else if(nums[i-1] == nums[i])   
            {
                // 此时up[i]与down[i]的长度和末尾数字都不更新，因此下次遇到“增/减”位置时能衔接上
                up[i] = up[i-1];
                down[i] = down[i-1];
            }
            else    // 此时down[i]对应的序列必然包含nums[i]
            {
                down[i] = up[i-1] + 1;
                up[i] = up[i-1];
            }
代码如下：
 */
int wiggleMaxLength(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    vector<int> up(n, 1), down(n, 1);

    for (int i = 1; i < n; i++)
    {
        if (nums[i - 1] < nums[i])
        {
            up[i] = down[i - 1] + 1;
            down[i] = down[i - 1];
        }
        else if (nums[i - 1] == nums[i])
        {
            up[i] = up[i - 1];
            down[i] = down[i - 1];
        }
        else
        {
            down[i] = up[i - 1] + 1;
            up[i] = up[i - 1];
        }
    }
    return max(up[n - 1], down[n - 1]);
}

/*
我的方法就是朴素的动态规划，定义sub_max_lengths[i]为子数组nums[0:i+1]以nums[i]结尾的最长wiggle
子序列的长度，last_sign[i]为该子序列末尾的符号变化，因为最长wiggle子序列可能有多个，因此最多有两种
符号变化，所以last_sign[i]是一个两元素数组，元素值代表符号变化，0表示未定义。符号变化用符号函数signFunc
计算，+1代表nums[i] - nums[i-1] > 0，其余类似。然后递推关系可见代码
 */
int wiggleMaxLength(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0 || n == 1)
        return n;
    else
    {
        int max_length = 1;
        vector<int> sub_max_lengths(n, 1);
        vector<vector<int>> last_signs(n, vector<int>(2, 0));

        //sub_max_lengths[1] = 2;
        //last_signs[1][0] = signFunc(nums[1] - nums[0]);

        for (int i = 1; i < n; i++)
        {
            //int sub_max_len = 0;
            for (int j = 0; j < i; j++)
            {
                int cur_len, cur_sign = signFunc(nums[i] - nums[j]);
                if (cur_sign == 0)
                    continue;
                if (sub_max_lengths[j] == 1 || last_signs[j][0] == -cur_sign || last_signs[j][1] == -cur_sign)
                {
                    cur_len = sub_max_lengths[j] + 1;
                    if (cur_len > sub_max_lengths[i])
                    {
                        sub_max_lengths[i] = cur_len;
                        fill(last_signs[i].begin(), last_signs[i].end(), 0);
                        last_signs[i][0] = cur_sign;
                    }

                    else
                    {
                        if (cur_len == sub_max_lengths[i])
                        {
                            if (last_signs[i][1] == 0)
                            {
                                if (cur_sign != last_signs[i][0])
                                    last_signs[i][1] = cur_sign;
                            }
                        }
                    }
                }
            }
            if (sub_max_lengths[i] > max_length)
                max_length = sub_max_lengths[i];
        }
        return max_length;
    }
}

int signFunc(int x)
{
    if (x > 0)
        return 1;
    else if (x == 0)
        return 0;
    else
        return -1;
}