/***
  Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different letters represent different tasks.Tasks could be done without original order. Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.

Example 1:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.

这道题我想了很久，最终看了答案https://discuss.leetcode.com/topic/92852/concise-java-solution-o-n-time-o-26-space
我的理解是这样的：
  首先贪心策略是：尽可能把频数最大的任务先运行，这样可以最大限度地减少idle。设最大频数为k, i为任务集合中频数小于k的第一个任务下标，
则当n较大时，最优解必定包含idle, 而其长度必然为(k-1) * (n+1) + i - 1；而当n较小时，此时可以没有idle，故最优解必定为要完成的任务的总数。
代码如下：

***/

int leastInterval(vector<char>& tasks, int n) {
        vector<int> numInstance(26, 0);
        for(int i=0; i<tasks.size(); i++)
        {
            numInstance[tasks[i] - 'A']++;
        }
        
        sort(numInstance.begin(), numInstance.end());
        int i = 25;
        while(i>=0 && numInstance[i]==numInstance[25])
        {
            i--;
        }
        
        int m = tasks.size();
        return max(m, (numInstance[25]-1) * (n+1) + 25 - i);
    }
