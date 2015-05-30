class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int N1 = nums1.size(), N2 = nums2.size();
        assert(N1+N2>0);
        if((N1+N2)%2) return findKth(nums1, 0, N1-1, nums2, 0, N2-1, (N1+N2)/2); // odd: middle one
        else return 0.5*(findKth(nums1,0,N1-1,nums2,0,N2-1,(N1+N2)/2)+findKth(nums1,0,N1-1,nums2,0,N2-1,(N1+N2)/2-1)); // eve: mean of middle two
    }
    
    int findKth(vector<int>& n1, int a1, int a2, vector<int>& n2, int b1, int b2, int k) {
    	if(a1>a2) return n2[b1+k]; // n1 passed
    	if(b1>b2) return n1[a1+k]; // n2 passed
    	if(k==0) return min(n1[a1], n2[b1]); // find the first one

    	int ma = (a1+a2)/2, mb = (b1+b2)/2;
    	if(ma-a1+mb-b1+1>k) { // drop the larger one: ------1------, ----------(2----------)
    		if(n1[ma]>=n2[mb]) return findKth(n1, a1, ma-1, n2, b1, b2, k);
    		else return findKth(n1, a1, a2, n2, b1, mb-1, k);
    	} else if(ma-a1+mb-b1+1<k) { // drop the smaller one: (-----1)-----, -------2-------
    		if(n1[ma]>=n2[mb]) return findKth(n1, a1, a2, n2, mb+1, b2, k-(mb-b1+1));
    		else return findKth(n1, ma+1, a2, n2, b1, b2, k-(ma-a1+1));
    	} else { // drop head of smaller and tail of larger: (-----1)-----, -------2(-------)
    		if(n1[ma]==n2[mb]) return n1[ma];
    		if(n1[ma]>n2[mb]) return findKth(n1, a1, ma, n2, mb+1, b2, k-(mb-b1+1));
    		else return findKth(n1, ma+1, a2, n2, b1, b2, k-(ma-a1+1));
    	}
    }
};
