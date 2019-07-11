#include<vector>
#include<iostream>

using namespace std;

/*�����������0-1�������⣬������֪��ԭ�����ת��Ϊ�ڸ������������ܷ��ҵ���Ϊsum���Ӽ�
�����⣬��f(i, target)Ϊ��nums[0]��nums[i]��������ķ�Χ���Ƿ���ں�Ϊtarget���Ӽ�����
�����µ��ƹ�ʽ��
f(i, target) = f(i-1, target) || f(i-1, target-nums[i]) 
����f(i-1, target)��������nums[i]�ķ�Χ���Ƿ���ں�Ϊtarget���Ӽ���
f(i-1, target-nums[i])�������nums[i]�ķ�Χ���Ƿ���ں�Ϊtarget���Ӽ�
��д���������ݹ�汾���£�*/
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

/*��ʵ���뻹���Խ�һ���Ż�����Ϊ�Ե����ϵķ���������һά����dp[]�洢����Ϊ�۲���ƹ�ʽ
��֪������������������nums��ֵ�����൱��f(i, target)�е���i���ڲ�ѭ����target�ݼ���
���ѭ����i�ε���dp[j]��ֵ���൱��f(i, j)����ע����ǣ��ڲ�ѭ�����ܵ���������Ϊnums[i]�е�
Ԫ�ض�ֻѡ��һ�Σ�����ʱ�õ���f(i, target) = f(i, target - nums[i]) || f(i, target)��
�������£�*/

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