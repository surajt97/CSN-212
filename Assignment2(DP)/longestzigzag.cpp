#include <bits/stdc++.h>
using namespace std;
int longestZigZag(vector <int> sequence){
    int n = sequence.size();
    int dp[n][2];
    //dp[i][0] = stores longest subsequence when a[i]<a[i-1]
    //dp[i][1] = stores longest subsequence when a[i]>a[i-1]
    for(int i = 0; i<n; i++){
        dp[i][0] = dp[i][1] = 1;
    }
    for(int i = 0; i<n; i++){
        for(int j = 0; j<i; j++){
            if(dp[j][1]+1>dp[i][0] && sequence[j]>sequence[i]){
                dp[i][0] = dp[j][1]+1;
            }
            if(dp[j][0]+1>dp[i][1] && sequence[j]<sequence[i]){
                dp[i][1] = dp[j][0]+1;
            }
        }
    }
    int ans = 0;
    for(int i = 0; i<n; i++){
        ans = max(ans, max(dp[i][0], dp[i][1]));
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector <int> arr;
    int data[19] = {70, 55, 13, 2, 99, 2, 80, 80, 80, 80, 100, 19, 7, 5, 5, 5, 1000, 32, 32};
    for(int i = 0; i<19; i++){
        arr.push_back(data[i]);
    }
    cout<<longestZigZag(arr)<<endl;
    return 0;
}