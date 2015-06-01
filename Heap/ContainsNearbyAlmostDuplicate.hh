class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if(nums.size()<2 || k<1 || t<0) return false;
        set<int> m;
        for(int i=0; i<k&&i<nums.size(); i++) {
            if(m.size()>0 && (diff(nums[i], *(m.begin()))<=t || diff(nums[i], *(m.rbegin()))<=t)) return true;
            m.insert(nums[i]);
        }
        for(int i=k; i<nums.size(); i++) {
            if(diff(nums[i], *(m.begin()))<=t || diff(nums[i], *(m.rbegin()))<=t) return true;
            m.insert(nums[i]);
            m.erase(nums[i-k]);
        }
        return false;
    }
    
    // use long int to avoid overflow when doing subtracting
    long diff(long a, long b) {
        return a>b?a-b:b-a;
    }
};
