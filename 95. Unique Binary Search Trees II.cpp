/***
  Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1...n.
For example,
Given n = 3, your program should return all 5 unique BST's shown below. 
***/

/*  借鉴96题的思路，可以划分成分别求以1, 2, 3, ..., n为根节点的BST，然后将解组合在一个数组中，经过分析可以看出， 子问题具有重叠性， 而且可以
分别独立求解，于是就可以借助动态规划算法，自底向上地解出问题。具体分析如下：
    假设T[i, i+1, ..., j]表示序列(i, i+1, ..., j)构造出的BST的集合，T[i]表示以i为根节点的BST的集合，则有如下关系：
    T[i, i+1, ..., j] = { T[1], T[2], ..., T[j] }
    T[k]中任意一个BST的左子树从 T[i, i+1, ..., k-1] 中抽取，右子树从 T[k+1, k+2, ..., j] 中抽取
    当 i==j 时， T[i, ..., j] 只有一种情况，即由单一根结点i构成的BST
    经分析可以看出，T[i, i+1, ..., j]的解依赖于所有序列长度小于j-i+1的子问题的解， 因此可以以长度递增的顺序求解，我的代码如下：
*/

// 注：由于i<=j, 因此为了节省空间，就把上三角矩阵每个元素的坐标映射成了一维数组的下标，即(i,j)映射成了i*(2*n-i-1)/2+j
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if(n==0) {
            vector<TreeNode*> res;
            return res;
        }
        vector< vector<TreeNode*> > subRes(n*(n+1)/2);
        for(int i=0; i<n; i++) {
            TreeNode *root = new TreeNode(i+1);
            subRes[i*(2*n-i+1)/2].push_back(root);
        }
        for(int len=2; len<=n; len++) {
            for(int i=0; i<=n-len; i++) {
                int j = i + len - 1;
                vector<TreeNode*> subRootsLb = subRes[(i+1)*(2*n-i-2)/2+j];
                for(int m=0; m<subRootsLb.size(); m++) {
                    TreeNode *lbRoot = new TreeNode(i+1);// 以序列的下界构造根节点
                    lbRoot->right = subRootsLb[m];
                    subRes[i*(2*n-i-1)/2+j].push_back(lbRoot);
                }
                vector<TreeNode*> subRootsUb = subRes[i*(2*n-i-1)/2+j-1];
                for(int m=0; m<subRootsUb.size(); m++) {
                    TreeNode *ubRoot = new TreeNode(j+1);   // 以序列的上界构造根节点
                    ubRoot->left = subRootsUb[m];
                    subRes[i*(2*n-i-1)/2+j].push_back(ubRoot);
                }
                for(int k=i+1; k<j; k++) {
                    vector<TreeNode*> subRootsMidL = subRes[i*(2*n-i-1)/2+k-1];
                    vector<TreeNode*> subRootsMidR = subRes[(k+1)*(2*n-k-2)/2+j];
                    for(int m=0; m<subRootsMidL.size(); m++) {
                        for(int r=0; r<subRootsMidR.size(); r++) {
                            TreeNode *midRoot = new TreeNode(k+1);  // 以序列的中间元素构造根节点
                            midRoot->left = subRootsMidL[m];
                            midRoot->right = subRootsMidR[r];
                            subRes[i*(2*n-i-1)/2+j].push_back(midRoot);
                        }
                    }
                }
                
            }
        }
        return subRes[n-1];
    }
};
