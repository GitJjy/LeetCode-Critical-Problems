/***
  Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words. You may assume the dictionary does not contain duplicate words. 
For example, given
s = "leetcode",
dict = ["leet", "code"]. 
Return true because "leetcode" can be segmented as "leet code". 

这道题是典型的动态规划，但是我在定义状态的时候有些麻烦，用了一个二维数组，在看了答案之后，仔细想想，只要用长度i即可区分不同的状态。
即isMatch[i]代表长度为i的与字符串s有共同起始字符的子串是否能从wordDict中找到，能则为true, 不能则为false，然后自底向上求解即可。

代码如下：
***/

bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.length();
        vector<bool> isMatch(n+1, false);
        isMatch[0] = true;
        for(int i=1; i<=n; i++)
        {
            for(int j=0; j<=i-1; j++)
            {
                if(isMatch[j])
                {
                    string word = s.substr(j, i-j);
                    for(int k=0; k<wordDict.size(); k++)
                    {
                        if(word == wordDict[k])
                        {
                            isMatch[i] = true;
                            break;
                        }
                    }
                }
            }
        }
        return isMatch[n];
    }
