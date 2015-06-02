/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval ni) {
        if(intervals.size()==0 || intervals.rbegin()->end < ni.start) {
            intervals.push_back(ni);
            return intervals;
        }
        if(intervals.begin()->start > ni.end) {
            intervals.insert(intervals.begin(), ni);
            return intervals;
        }
        
        int left = 0, right = intervals.size()-1;
        while(left<=right) {
            int m = (left+right)/2;
            if(ni.start>=intervals[m].start && ni.start<=intervals[m].end) {
                int i = 1;
                while(m+i<intervals.size()&&intervals[m+i].start<=ni.end) i++;
                intervals[m].end = max(ni.end, intervals[m+i-1].end);
                if(i>1) intervals.erase(intervals.begin()+m+1, intervals.begin()+m+i);
                return intervals;
            }
            if(ni.start<intervals[m].start) right = m-1;
            else left = m+1;
        }
        int i = 0;
        while(left+i<intervals.size() && ni.end>=intervals[left+i].start) i++;
        if(i>0) {
            ni.end = max(ni.end, intervals[i+left-1].end);
            intervals.erase(intervals.begin()+left, intervals.begin()+left+i);
        }
        intervals.insert(intervals.begin()+left, ni);
        return intervals;
    }
};
