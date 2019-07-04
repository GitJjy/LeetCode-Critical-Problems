/** 
这道题有两种思路：动态规划和patience-LIS，两种方法都在笔记本里记录了。
一、动态规划的代码
**/
int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        
        for(int i=1; i<n; i++)
        {
            int pre_max_len = 0;
            for(int j=0; j<i; j++)
            {
                if(nums[j] < nums[i])
                {
                    pre_max_len = (pre_max_len > dp[j]) ? pre_max_len : dp[j];
                }
            }
            dp[i] = pre_max_len + 1;
        }
        
        int max_len = 0;
        for(int i=0; i<n; i++)
            max_len = (max_len > dp[i]) ? max_len : dp[i];
        
        return max_len;
        
    }
    
 
/* 二、patience-LIS的代码 */
 // patience-LIS method
    int lengthOfLIS(vector<int>& nums) {
    if(nums.size()==0)
        return 0;
    
    // top element's value of each pile
	vector<int> top_nums = { nums[0] };  
    
    // use (value, pointer) tuple to represent each element in the pile
    // the pointer points to the index of previous pile's top element at the
    // insertion time.
	pair<int, int> first_pair(nums[0], -1);  // -1 means no previous pile
	vector< vector<pair<int, int>> > piles = { { first_pair } };

	for (int i = 1; i<nums.size(); i++)
	{
        // find the proper position for nums[i]
		int pile_index = binSearch(top_nums, 0, top_nums.size() - 1, nums[i]);
		int pre_top = -1; // index of the previous pile's top element
		if (pile_index >= 1)
			pre_top = top_nums[pile_index - 1];
		if (pile_index == piles.size())  // need to form a new pile
		{
			vector<pair<int, int>> new_pile = { make_pair(nums[i], pre_top) };
			piles.push_back(new_pile);
			top_nums.push_back(nums[i]);
		}
		else
		{
			piles[pile_index].push_back(make_pair(nums[i], pre_top));
			top_nums[pile_index] = nums[i];
		}
	}

	return piles.size();


}
    
    int binSearch(vector<int>& nums, int low, int high, int target)
    {
    
        int mid = low + (high - low) / 2;
        
        if(nums[mid] == target)
            return mid;
        else if(nums[mid] < target)
        {
            if(mid + 1 > high)
                return mid + 1;
            else
                return binSearch(nums, mid + 1, high, target);
        }
        else
        {
            if(mid - 1 < low)
                return mid;
            else
                return binSearch(nums, low, mid - 1, target);
        }
    }
