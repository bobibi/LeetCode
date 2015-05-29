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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        assert(head!=NULL);
        ListNode *left=head, *right=head, **pp=&head;
        while(n>0) {
            assert(right->next!=NULL);
            right=right->next;
            n--;
        }
        while(right) {
            right=right->next;
            pp = &(left->next);
            left=left->next;
        }
        
        *pp = left->next;
        return head;
    }
};
