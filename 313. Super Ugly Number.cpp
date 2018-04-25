/***
Write a program to find the nth super ugly number. 
Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k. For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26, 28, 32] is the sequence of the first 12 super ugly numbers given primes = [2, 7, 13, 19] of size 4. 
Note:
(1) 1 is a super ugly number for any given primes.
(2) The given numbers in primes are in ascending order.
(3) 0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
(4) The nth super ugly number is guaranteed to fit in a 32-bit signed integer. 
这道题就是给出一组质数，求由这些质数作为质因数构成的所有的数中第n小的数，关键在于：
每个新生成的super ugly number由已生成的和primes中的质数相乘求得，因此可以动态地维护一个指针，
每个指针对应primes中一个质数，值为uglyNums中目前待与primes中质数相乘的已生成的数的下标，
动态、递增地更新指针和uglyNums, 最终即可得到结果，时间复杂度O(kn)
代码如下：
***/

int nthSuperUglyNumber(int n, vector<int>& primes) {
        int k = primes.size();
        //初始化uglyNums以及指针数组
        vector<int> uglyNums(n, INT_MAX), indices(k, 0);
        uglyNums[0] = 1;
        
        for(int i=1; i<n; i++)
        {
            //生成新的ugly number（在primes中所有质数乘以其对应的已生成的ugly number所得乘积中最小的）
            for(int j=0; j<k; j++) uglyNums[i] = min(uglyNums[i], primes[j] * uglyNums[indices[j]]);
            //若某个指针对应的ugly number已被用完，则指针加一
            for(int j=0; j<k; j++) indices[j] += (primes[j] * uglyNums[indices[j]] == uglyNums[i]);
        }
        
        return uglyNums[n-1];

    }
