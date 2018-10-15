#include <bits/stdc++.h>
#include <boost/date_time/local_time/local_time.hpp>

#define ASSERT(expected, res)  cout << (expected == res? "\033[1;32mpass\033[0m":"\033[1;31mfail\033[0m" ) << endl;
#define ASSERT_M(msg, expected, res)cout <<msg<<endl;cout << "exp "<<expected<<endl;cout << "actual "<<res<<endl;  cout << (expected == res? "\033[1;32mpass\033[0m":"\033[1;31mfail\033[0m" ) << endl;
using namespace std;

class HitCounter{
  private:
    set<long> dates;
    unordered_map<long, long> date_hits;
    long tot_count;
    long max_mem;
  public:
    HitCounter(long max_mem):max_mem(max_mem),tot_count(0){
    }
    void record(long date){
      if(tot_count+1>max_mem){
        int to_remove =(dates.size()/2);
        cout << "to_remove" << to_remove <<" items "<< endl;
        cout << "tot_count " <<tot_count << endl;
        cout << "total in dates set " <<dates.size() << endl;
        tot_count -=to_remove;
        for(auto it = dates.begin(); it!=dates.end() &&to_remove>0 ;++it){
          long date = *it;
          date_hits.erase(date);
          to_remove--;
        }
        //cout <<"to_remove" << to_remove <<" items "<< endl;

        auto end = dates.begin();
        advance(end, (dates.size() / 2));

        dates.erase(dates.begin(),end);
        cout << tot_count<< endl;
        cout << dates.size()<< endl;
        cout << date_hits.size()<< endl;
      }

      tot_count++;
      if(date_hits.find(date) == date_hits.end()){
        dates.insert(date);
        date_hits.insert({date,1});
      }else{
        date_hits[date]++;
      }
    }
    long total(){
      return tot_count;
    }
    long range(long lower, long upper){
      long count = 0;
      for(auto it = dates.lower_bound(lower); it!=dates.upper_bound(upper); ++it){
        long date = *it;
        count+=date_hits[date];
      }
      return count;
    }
};



int main(){

  int n, date, memo;
  cin>>n;
  cin>>memo;
  HitCounter* hc = new HitCounter(memo);
  while(n--){
    cin >>date;
    hc->record(date);
  }
  
  int exp_total,range_low, range_high, exp_range;
  cin >>exp_total >>range_low >>range_high >> exp_range;

  ASSERT_M("Total Test", exp_total,hc->total() );
  ASSERT_M("Range Test",exp_range,hc->range(range_low, range_high) );

  return 0;
}
