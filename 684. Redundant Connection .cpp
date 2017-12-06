/*** 
  问题描述：
  https://leetcode.com/problems/redundant-connection/description/
  
  解决方案： 使用并查集数据结构（https://zh.wikipedia.org/wiki/%E5%B9%B6%E6%9F%A5%E9%9B%86），动态地构建rank表和fathers表，合并每次访问到的两个
  顶点，若出现两个顶点属于同一个集合，则说明出现了环，则由他们构成的边就是多余的边，返回即可。
  
  代码如下：
  
***/

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> res;
        int rank[n], fathers[n];
        for(int i=0; i<n; i++) {
            rank[i] = 0;
            fathers[i] = i;
        }
        for(int i=0; i<n; i++) {
            int x = edges[i][0]-1, y = edges[i][1]-1;
            if(getFather(x, fathers) == getFather(y, fathers)) {
                res = edges[i];
                break;
            }
            else {
                merge(x, y, rank, fathers);
            }
        }
        
        return res;
    }
    
    int getFather(int x, int fathers[]) {
        if(fathers[x] != x) {
            fathers[x] = getFather(fathers[x], fathers);
        }  
        return fathers[x];
    }
    
    
    void merge(int x, int y, int rank[], int fathers[]) {
        int fx = getFather(x, fathers);
        int fy = getFather(y, fathers);
        if(fx != fy) {
            if(rank[fx] < rank[fy]) {
                fathers[fx] = fy;
            }
            else if(rank[fx] > rank[fy]) {
                fathers[fy] = fx;
            }
            else {
                fathers[fx] = fy;
                rank[fy]++;
            }
        }
    }


