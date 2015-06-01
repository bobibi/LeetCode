/**
 * Contains Duplicate III
 * 
 * Question: Given an array of integers, find out whether there are two distinct indices i and j in the array 
 * such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at 
 * most k.
 * 
 * Solution: Maintain a sorted structure which contains at most consecutive k elements of nums, i.e. a moving
 * window with maximum size k. Iterating over nums, compare the distance between the coming number and the max
 * and min of the moving window. If the distance is less than or equal to t, then return TRUE. Insert the coming
 * number, and remove the oldest number if the window size exceeds k.
 * 
 * Be careful about overflowing.
**/

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
