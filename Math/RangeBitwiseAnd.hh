/**
 * Bitwise AND of Numbers Range 
 * 
 * Question: Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of 
 * all numbers in this range, inclusive. For example, given the range [5, 7], you should return 4.
 * 
 * Solution: For two numbers (binary form): abcdef0xyz and abcdef1jkl, all the numbers in between
 * should have the prefix "abcdef". The remaining part will change from 0xyz to 1jkl, there must be
 * one 1000, because 0xyz^1000 = 0, the other numbers will not contribute any 1s.
 * 
 * Just scan from left to right. Be careful that the most left bit is the second postion for int.
 * 
 **/

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int k = 1<<(sizeof(int)*8-2);
        int ans = 0;
        while(k>0) {
            if((m&k)!=(n&k)) break;
            ans |= m&k;
            k>>=1;
        }
        return ans;
    }
};
