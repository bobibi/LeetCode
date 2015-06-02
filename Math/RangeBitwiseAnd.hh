class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int k = 0x40000000;
        int ans = 0;
        while(k>0 && (m&k)==0 && (n&k)==0) k>>=1;
        while(k>0) {
            ans |= m&n&k;
            if((m&k)!=(n&k)) break;
            k>>=1;
        }
        
        return ans;
    }
};
