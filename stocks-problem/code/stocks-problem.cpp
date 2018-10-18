#include <bits/stdc++.h>
using namespace std;
#define ASSERT(expected, res)  cout << (expected == res? "\033[1;32mpass\033[0m":"\033[1;31mfail\033[0m" ) << endl;
 /*
  CSCareerQuestions problem Oct 9 2018
  This problem was asked by Facebook.
  Given an array of numbers representing the stock prices of a company in chronological 
  order and an integer k, return the maximum profit you can make from k buys and sells. 
  You must buy the stock before you can sell it, and you must sell the stock before you 
  can buy it again.

  For example, given k = 2 and the array [5, 2, 4, 0, 1], you should return 3.

  
*/

int main(){
  int n, k, expected;
  cin >> n >> k;
  vector<int> stocks(n);
  for(int i = 0; i< n; i++) cin >> stocks[i];
  cin >> expected;

  vector<vector<int>> profits(k+1, vector<int>(n+1, 0));
  for(int t = 1; t < k+1; t++){
    int prev_diff = -stocks[0];
    for(int i = 1; i < n; i++){
      prev_diff     = max(prev_diff, profits[t-1][i-1]-stocks[i-1]);
      profits[t][i] = max(profits[t][i-1], stocks[i]+prev_diff);
    }
  }
  int res = profits[k][n-1];
  cout << res << endl;
  ASSERT(expected, res);
  return 0;
}
