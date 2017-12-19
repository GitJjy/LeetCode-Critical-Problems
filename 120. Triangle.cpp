/** 
  这道题大神从底层向上，原址更新，最后答案归于triangle[0][0], 十分巧妙，
代码如下：
**/

int minimumTotal(vector<vector<int>>& triangle) {
        int m=triangle.size(); 
        
        for(int i=m-2; i>=0; i--){ 
            for(int j=0; j<i+1; j++){
                triangle[i][j]+=min(triangle[i+1][j], triangle[i+1][j+1]); 
            }
        }
        
        return triangle[0][0]; 
        
    }

