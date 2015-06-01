class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> m;
        for(int i=0; i<k&&i<nums.size(); i++) {
            if(m.find(nums[i])!=m.end()) return true;
            m.insert(nums[i]);
        }
        for(int i=k; i<nums.size(); i++) {
            if(m.find(nums[i])!=m.end()) return true;
            m.insert(nums[i]);
            m.erase(nums[i-k]);
        }
        return false;
    }
};
