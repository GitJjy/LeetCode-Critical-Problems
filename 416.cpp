#include<vector>
#include<iostream>

using namespace std;

/*这道题类似于0-1背包问题，分析可知，原问题可转化为在给定的数组中能否找到和为sum的子集
的问题，设f(i, target)为在nums[0]到nums[i]这个连续的范围内是否存在和为target的子集，则
有如下递推公式：
f(i, target) = f(i-1, target) || f(i-1, target-nums[i]) 
其中f(i-1, target)代表不包含nums[i]的范围内是否存在和为target的子集，
f(i-1, target-nums[i])代表包含nums[i]的范围内是否存在和为target的子集
可写出带备忘递归版本如下：*/
bool find_sum(vector<int> &nums, vector< vector<int> > &memo, int i, int target)
{
	if (i < 0 || target < 0)
		return false;

	if (memo[i][target] != -1)
	{
		return memo[i][target];
	}
	else
	{
			bool contain_i = find_sum(nums, memo, i - 1, target - nums[i]);
			bool not_contain_i = find_sum(nums, memo, i - 1, target);
			bool find_target = contain_i || not_contain_i;
			memo[i][target] = find_target ? 1 : 0;
			return (memo[i][target]);
	}
}

bool canPartition(vector<int> &nums)
{
	int sum = 0, n = nums.size();
	if (n <= 1)
		return false;
	for (int i = 0; i < n; i++)
	{
		sum += nums[i];
	}
	if (sum % 2 != 0)
		return false;
	else
	{
		int target = sum / 2;
		vector< vector<int> > memo(n, vector<int>(target + 1, -1));
		for (int i = 0; i < n; i++)
			memo[i][0] = 0;
		for (int j = 0; j <= target; j++)
			memo[0][j] = 0;
		if(nums[0] <= target)
			memo[0][nums[0]] = 1;
		return find_sum(nums, memo, n - 1, target);
	
	}
	

}

/*其实代码还可以进一步优化，改为自底向上的方法，采用一维数组dp[]存储，因为观察递推公式
可知，可以在外层逐个迭代nums的值，这相当于f(i, target)中递增i，内层循环从target递减，
外层循环第i次迭代dp[j]的值就相当于f(i, j)，需注意的是，内层循环不能递增，是因为nums[i]中的
元素都只选择一次，更新时用的是f(i, target) = f(i, target - nums[i]) || f(i, target)，
代码如下：*/

bool canPartition(vector<int> &nums)
{
	int sum = 0, n = nums.size();
	if (n <= 1) return false;
	for (int i = 0; i < n; i++)
	{
		sum += nums[i];
	}
	if (sum % 2 != 0)
		return false;
	else
	{
		int target = sum / 2;
		vector<bool> dp(target + 1, false);
		dp[0] = true;
		for (int i = 0; i<nums.size(); i++)
		{
			for (int j = target; j >= nums[i]; j--)
			{
				dp[j] = dp[j] || dp[j - nums[i]];
			}
		}
		return dp[target];

	}


}
void main()
{
	vector<int> nums = { 100 };
	bool res = canPartition(nums);
	if (res)
		cout << "Can partition!\n";
	else
		cout << "Can't partition\n";
	system("pause");
}