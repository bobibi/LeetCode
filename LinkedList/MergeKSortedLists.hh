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
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        multimap<int, ListNode*> headers;
        for(vector<ListNode *>::iterator it = lists.begin(); it != lists.end(); it++){
            if(*it) headers.insert(pair<int, ListNode*>((*it)->val, *it));
        }
        
        ListNode* L = NULL;
        ListNode* tmp;
        ListNode** tailPtr = &L;
        
        while(headers.size()) {
            tmp = headers.begin()->second;
            
            *tailPtr = tmp;
            tailPtr = &(tmp->next);
            headers.erase(headers.begin());
            
            if(tmp->next){
                headers.insert(pair<int, ListNode*>(tmp->next->val, tmp->next));
            }
        }
        
        return L;
    }
};
