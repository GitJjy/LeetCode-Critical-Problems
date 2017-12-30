/***
  Count the number of prime numbers less than a non-negative number, n.
  这道题巧妙地利用了质数和合数的区别以及合数可分解质因数的性质，通过将小于n的数中的合数都去掉，达到统计
  质数个数的目的，借鉴答案之后的代码如下：
 ***/
 
 int countPrimes(int n) {
        if(n < 3)
        {
            return 0;
        }
        else
        {
            vector<bool> isPrime(n, true);
            int upper = int(sqrt(n)) + 1;
            int count = 0;
            for(int i=2; i<upper; i++)
            {
                for(int j=i; i*j<n; j++)
                {
                    isPrime[i*j] = false;
                }
            }
            
            for(int i=2; i<n; i++)
            {
                if(isPrime[i])
                {
                    count++;
                }
            }
            return count;
        }
    }
