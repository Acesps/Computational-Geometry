//#include <bits/stdc++.h>
//#include <iomanip>
#include <map>
#include <unordered_map>
// #include <set>
#include <unordered_set>
// #include <list>
// #include <ctime>
// #include <deque>
// #include <queue>
// #include <stack>
// #include <bitset>
// #include <cstdio>
// #include <limits>
// #include <cstdlib>
// #include <fstream>
// #include <numeric>
// #include <sstream>
// #include <utility> 
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
#include <climits>
#define ull unsigned long long
#define ll long long
#define pb push_back	
#define mp make_pair
#define ff first
#define ss second
#define rep(a,i,n) for(ll i=a;i<n;i++)
#define IoS ios_base::sync_with_stdio(false)
#define all(x)     x.begin(), x.end()

const ll mod=(1e9+7);
using namespace std;

template < typename T>
ostream& operator <<(ostream& o,vector<T> a){
	size_t n= a.size();
	for(size_t i=0;i<n;i++){
		o<<a[i]<<" ";
	}
	o<<"\n";
	return o;
}
template< typename T>
void display(T a[],int n){
        
        for( int i=0;i<n;i++){
                cout<<a[i]<<" ";
        }
        cout<<endl;
}
template <typename T>
ostream& operator <<(ostream& o,map<int,T> m){
	size_t n= m.size();
	auto it=m.begin();
	for(;it!=m.end();it++){
		o<<(*it).ff<<" "<<(*it).ss<<"\n";
	}
	return o;
}

struct cordinate{
	int x; int y;
};

truct Node2{																	//struct for temporary index
	public :int tf;
	int priority;
};

int solve(vector<cordinate> &cordinates)
{	//unordered_set<cordinate> S;
	unordered_set<pair<int, int> > s;
	std::unordered_map<string,Node2> docIndex;									//temporary index for the doc
	
	//for_each(cordinates.begin(),cordinates.end(),[](cordinate i){s.insert(i);});	
	return 0;
}



int main(){
	IoS;
	cin.tie(0);
	cout.tie(0);int n,ans;
	cordinate input;
	vector<cordinate> cordinates;
	cout<<"Select mode:\n\t 1> Random points \n 2>Feed points from stdin\n press 1 | 2\n";
	cin>>ans;
	cout<<"Enter the Number of points\n";
	cin>>n;
	if(ans==1){
		srand (time(NULL));
		for(int i=0;i < n; i++){
			input.x = rand()%20000 - 9999;
			input.y = rand()%20000 - 9999;
			cordinates.pb(input);
		}
	}
	else {
		for(int i = 0; i < n; i++){
			cin>>input.x>>input.y;
			cordinates.pb(input);
		}
	}
	solve(cordinates);
	return 0;
} 