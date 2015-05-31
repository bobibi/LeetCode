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
    void recoverTree(TreeNode* root) {
        TreeNode *first = NULL, *second = NULL;
        TreeNode *pre = NULL, *cur = root;
        int last = INT_MIN;
        bool found = false;
        while(cur) {
            if(cur->left) {
                pre = cur->left;
                while(pre->right && pre->right!=cur) pre = pre->right;
                if(pre->right) { // all left visited
                    pre->right = NULL;
                    // visit cur
                    ///
					if(cur->val<last) {
						second = cur;
						found = true;
					}
					if(!found) first = cur;
					last = cur->val;
                    ///
                    cur = cur->right;
                } else {
                	pre->right = cur;
                    cur = cur->left;
                }
            } else {
                // visit cur
				///
				if (cur->val < last) {
					second = cur;
					found = true;
				}
				if (!found)
					first = cur;
				last = cur->val;
				///
                cur = cur->right;
            }
        }
        
        swap(first->val, second->val);
    }
};
