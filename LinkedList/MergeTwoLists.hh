/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode* ans;
        ListNode** pp = &ans;
        while(l1 && l2) {
            if(l1->val < l2->val) {
                *pp = l1;
                pp = &(l1->next);
                l1 = l1->next;
            } else {
                *pp = l2;
                pp = &(l2->next);
                l2 = l2->next;
            }
        }
        *pp = l1?l1:l2;
        return ans;
    }
};
