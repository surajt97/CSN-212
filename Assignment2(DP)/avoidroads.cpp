#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007
using namespace std;
bool path[105][105][2];//two roads, vertical & horizontal
ll dp[105][105];
class AvoidRoads{
public:
    ll numWays(int w, int h, vector <string> bad) {
        memset(path, true, sizeof(path));
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < bad.size(); i++) {
            stringstream ss(bad[i]);
            int x1, y1, x2, y2;
            ss>>x1>>y1>>x2>>y2;//converting string input to integers
            if (x1 < x2){
                path[y1][x1][0] = false;
            }
            else if (y1 < y2){
                path[y1][x1][1] = false;
            }
            else if (x2 < x1){
                path[y2][x2][0] = false;
            }
            else if (y2 < y1){
                path[y2][x2][1] = false;
            }
        }
        dp[0][0] = 1;
        for (int i = 0; i <= h; i++){
            for (int j = 0; j <= w; j++){
                if (path[i][j][1])
                    dp[i+1][j] = dp[i+1][j] + dp[i][j];
                if (path[i][j][0])
                    dp[i][j+1] = dp[i][j+1] + dp[i][j];
            }
        }
        return dp[h][w];
    }
};
