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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        int c = 0;
        ListNode* p;
        ListNode** pp = &p;
        while(l1 && l2) {
            *pp = new ListNode((c+l1->val+l2->val)%10);
            c = (c+l1->val+l2->val)/10;
            l1 = l1->next;
            l2 = l2->next;
            pp = &((*pp)->next);
        }
        ListNode* q = l1==NULL?l2:l1;
        while(q) {
            *pp = new ListNode((c+q->val)%10);
            c = (c+q->val)/10;
            q = q->next;
            pp = &((*pp)->next);
        }
        if(c) {
            *pp = new ListNode(c);
            pp = &((*pp)->next);
        }
        *pp = NULL;
        return p;
    }
};
