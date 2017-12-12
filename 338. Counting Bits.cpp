/***
  Given a non negative integer number num. 
  For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and 
  return them as an array. 
  
  任意一个整数的二进制表示中‘1’的个数，等于它最后一位左边的所有的‘1’的个数和最后一位的数(0或1)的和，具体参考
  https://discuss.leetcode.com/topic/40162/three-line-java-solution
  
代码如下：
***/


vector<int> countBits(int num) {
        vector<int> res(num+1, 0);
        for(int i=1; i<=num; i++) {
            int preBits = i >> 1;
            int lastBit = i & 1;
            res[i] = res[preBits] + lastBit;
        }
        return res;
    }


