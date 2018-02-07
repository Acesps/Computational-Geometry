#include <list>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Grahams.h"
#include "kirkpatrick_seidal.h"
#include <unordered_set>

#define pb push_back	

using namespace std;

template < typename T>
ostream& operator <<(ostream& o, vector<T> a){
	size_t n= a.size();
	for(size_t i=0;i<n;i++){
		o<<a[i].x<<" "<<a[i].y<<"\n";
	}
	return o;
}

template< typename T>
void display(T a[], int n){
        for( int i=0;i<n;i++){
                cout<<a[i]<<" ";
        }
        cout<<endl;
}

bool operator==(const cordinate &A,  cordinate &B){
	return A.x == B.x && A.y == B.x; 
}

void findpmin(vector<cordinate> &a, cordinate &pmin, 
	cordinate &pmax,  cordinate &pmin2,  cordinate &pmax2){
	int minxindex = 0 , maxxindex = 0;
	pmin = a[0];
	pmax = a[0];
	for(int i = 1; i < a.size(); i++){
		if(a[i].x > pmax.x || (a[i].x == pmax.x && a[i].y > pmax.y)){
			pmax = a[i];
			maxxindex = i; 
		}

		if(a[i].x < pmin.x || (a[i].x == pmin.x && a[i].y > pmin.y)){
			pmin = a[i];
			minxindex = i; 
		}
	}
	//removing both pmin and pmax
	swap(a[minxindex], a[a.size()-1]);
	if(maxxindex == a.size()-1){
		maxxindex = minxindex;
	}
	swap(a[maxxindex], a[a.size()-2]);
	a.pop_back();
	a.pop_back();
	//2. If there are two or more such pmin(pmax)
	maxxindex = -1;
	minxindex = -1;
	pmax2 = pmax;
	pmin2 = pmin;
	for(int i = 0; i < a.size(); i++){
		if(a[i].x == pmax2.x && a[i].y < pmax2.y){
			pmax2 = a[i];
			maxxindex = i;
		}
		if(a[i].x == pmin2.x && a[i].y < pmin2.y){
			pmin2 = a[i];
			minxindex = i;
		}
	}
	if(maxxindex > -1){
		swap(a[maxxindex], a[a.size()-1]);
		if(minxindex == a.size()-1){
			minxindex = maxxindex;
		}
		a.pop_back();

	}
	if(minxindex > -1){
		swap(a[minxindex], a[a.size()-1]);
		a.pop_back();
	}
}

bool myfunction (cordinate i, cordinate j) { return (i.x < j.x); }


vector<cordinate> divide(cordinate bottom, cordinate top, vector<cordinate> &points, int direction,int flag){
	vector<cordinate> T;
	if(bottom.x == top.x && bottom.y == top.y){
		return T;
	}
	for(int i = 0;i < points.size(); i++){
		if(Graham::angle(bottom, top, points[i]) == direction){
			T.pb(points[i]);
		}
	}
	T.pb(top);
	T.pb(bottom);
	unordered_set<long long int> S;
	for(int i = 0;i < T.size(); i++){
		S.insert((T[i].x + 100000) + 1ll*1000000 * (T[i].y + 100000));
	}
	T.clear();
	cordinate temp;
	for(auto i = S.begin();i != S.end(); i++){
		temp.x = (*i)%1000000 - 100000;
		temp.y = (*i)/1000000 - 100000;
		T.pb(temp);
	}

	return T;
}

void upperBridge(vector<cordinate> points, cordinate &pl, cordinate &pr, int a){
	vector<cordinate> candidates;
	//random_shuffle (points.begin(),  points.end());
	if(points.size() == 2){
		if(points[0].x > points[1].x){
			swap(points[0], points[1]);
		}
		pl = points[0];
		pr = points[1];
		return;
	}
	if(points.size() % 2){
		candidates.pb(points.back());
	}
	vector<float> slopes;
	for(int i = 0;i < points.size()-(points.size()%2); i+=2){
		if(points[i].x == points[i+1].x){
			if(points[i].y > points[i+1].y) 
				candidates.pb(points[i]);
			else 
				candidates.pb(points[i+1]);
			swap(points[i], points[points.size()-1]);
			swap(points[i+1], points[points.size()-2]);
			points.pop_back();
			points.pop_back();
			i-=2;
			continue;
		}
		if(points[i].x > points[i+1].x){
			swap(points[i], points[i+1]);
		}
		float k = (points[i].y - points[i+1].y) / (1.0*(points[i].x - points[i+1].x));
		slopes.pb(k);
	}
	
	//5.median of slopes
	if(slopes.size()){
	nth_element(slopes.begin(), slopes.begin() + slopes.size()/2, slopes.end());
	float K = slopes[slopes.size()/2];
	slopes.clear();
	//6.
	vector<cordinate> small, equal, large;
	for(int i = 0;i < points.size()-(points.size()%2);i+=2){
		float k = (points[i].y - points[i+1].y) / (1.0*(points[i].x - points[i+1].x)); 
		if(K > k){
			small.pb(points[i]);
			small.pb(points[i+1]);
		}
		else if(K == k){
			equal.pb(points[i]);
			equal.pb(points[i+1]);
		}
		else{
			large.pb(points[i]);
			large.pb(points[i+1]);
		}
	}
	//7.
	points.insert(points.end(),candidates.begin(),candidates.end());
	vector<int> maxindex;
	float maxintersect = points[0].y - K * points[0].x;
	maxindex.pb(0);
	for(int i = 1;i < points.size(); i++){
		float intersect = points[i].y - K * points[i].x;
		if(maxintersect == intersect){
			maxindex.pb(i);
		}
		else if(maxintersect < intersect){
			maxintersect = intersect;
			maxindex.clear();
			maxindex.pb(i);	
		}
	}
	cordinate pk = points[maxindex[0]], pm = points[maxindex[0]];
	for(int i = 1 ;i < maxindex.size(); i++){
		if(points[maxindex[i]].x < pk.x)
			pk = points[maxindex[i]];
		if(points[maxindex[i]].x > pm.x)
			pm = points[maxindex[i]];
	}
	//8.
	if(pk.x <= a && pm.x > a){
		pl = pk;
		pr = pm;
		return;
	}
	//9.
	if(pm.x <= a){
		for (int i = 0; i < large.size(); i+=2)
		{	
			candidates.pb(large[i+1]);
		}
		for (int i = 0; i < equal.size(); i+=2)
		{	
			candidates.pb(equal[i+1]);
		}
		for (int i = 0; i < small.size(); i++)
		{	
			candidates.pb(small[i]);
		}
	}
	//10.
	else if(pk.x > a){
		for (int i = 0; i < equal.size(); i+=2)
		{	
			candidates.pb(equal[i]);
		}
		for (int i = 0; i < small.size(); i+=2)
		{	
			candidates.pb(small[i]);
		}
		for (int i = 0; i < large.size(); i++)
		{	
			candidates.pb(large[i]);
		}
	}	
}	

	return upperBridge(candidates, pl, pr, a);
}

void lowerBridge(vector<cordinate> points, cordinate &pl, cordinate &pr, int a){
	vector<cordinate> candidates;
	if(points.size() == 2){
		if(points[0].x > points[1].x){
			swap(points[0], points[1]);
		}
		pl = points[0];
		pr = points[1];
		return;
	}
	if(points.size() % 2){
		candidates.pb(points.back());
	}
	vector<float> slopes;
	for(int i = 0;i < points.size()-(points.size()%2); i+=2){
		if(points[i].x == points[i+1].x){
			if(points[i].y < points[i+1].y) 
				candidates.pb(points[i]);
			else 
				candidates.pb(points[i+1]);
			swap(points[i], points[points.size()-1]);
			swap(points[i+1], points[points.size()-2]);
			points.pop_back();
			points.pop_back();
			i-=2;
			continue;
		}
		if(points[i].x > points[i+1].x){
			swap(points[i], points[i+1]);
		}
		float k = (points[i].y - points[i+1].y) / (1.0*(points[i].x - points[i+1].x));	
		slopes.pb(k);
	}
	//5.median of slopes
	if(slopes.size()){
	nth_element(slopes.begin(), slopes.begin() + slopes.size()/2, slopes.end());
	float K = slopes[slopes.size()/2];
	slopes.clear();
	//6.
	vector<cordinate> small, equal, large;
	for(int i = 0;i < points.size()-(points.size()%2);i+=2){
		float k = (points[i].y - points[i+1].y) / (1.0*(points[i].x - points[i+1].x)); 
		if(K < k){
			small.pb(points[i]);
			small.pb(points[i+1]);
		}
		else if(K == k){
			equal.pb(points[i]);
			equal.pb(points[i+1]);
		}
		else{
			large.pb(points[i]);
			large.pb(points[i+1]);
		}
	}
	//7.
	points.insert(points.end(),candidates.begin(),candidates.end());
	vector<int> maxindex;
	float maxintersect = points[0].y - K * points[0].x;
	maxindex.pb(0);
	for(int i = 1;i < points.size(); i++){
		float intersect = points[i].y - K * points[i].x;
		if(maxintersect == intersect){
			maxindex.pb(i);
		}
		else if(maxintersect >	 intersect){
			maxintersect = intersect;
			maxindex.clear();
			maxindex.pb(i);	
		}
	}
	
	cordinate pk = points[maxindex[0]], pm = points[maxindex[0]];
	{	
		for(int i = 1 ;i < maxindex.size(); i++){
			if(points[maxindex[i]].x < pk.x)
				pk = points[maxindex[i]];
			if(points[maxindex[i]].x > pm.x)
				pm = points[maxindex[i]];
		}
	}//8.
	if(pk.x <= a && pm.x > a){
		pl = pk;
		pr = pm;
		return;
	}
	//9.
	if(pm.x <= a){
		for (int i = 0; i < large.size(); i+=2)
		{	
			candidates.pb(large[i+1]);
		}
		for (int i = 0; i < equal.size(); i+=2)
		{	
			candidates.pb(equal[i+1]);
		}
		for (int i = 0; i < small.size(); i++)
		{	
			candidates.pb(small[i]);
		}
	}
	//10.
	else if(pk.x > a){
		for (int i = 0; i < equal.size(); i+=2)
		{	
			candidates.pb(equal[i]);
		}
		for (int i = 0; i < small.size(); i+=2)
		{	
			candidates.pb(small[i]);
		}
		for (int i = 0; i < large.size(); i++)
		{	
			candidates.pb(large[i]);
		}
	}
}	

	return lowerBridge(candidates, pl, pr, a);

}
	

list<cordinate> UPPER_HULL(cordinate pmin, cordinate pmax, vector<cordinate> points){
	list<cordinate> upper;
	if(pmin.x == pmax.x && pmin.y == pmax.y){
		upper.push_back(pmin);
		return upper;
	}
	//finding median in O(n)
	int n = points.size();
	nth_element(points.begin(), points.begin() + n/2, points.end(), myfunction);
	cordinate pl, pr;	
	upperBridge(points, pl, pr, points[n/2].x);
	vector<cordinate> Tleft = divide(pmin, pl, points, 1, 0);//1==counterclockwise
	vector<cordinate> Tright = divide(pmax, pr, points, 2, 0);//2==clockwise
	upper = UPPER_HULL(pmin, pl, Tleft);
	upper.splice(upper.end(), UPPER_HULL(pr, pmax, Tright));
	return upper;
}

list<cordinate> LOWER_HULL(cordinate pmin, cordinate pmax, vector<cordinate> &points){
	list<cordinate> lower;
	if(pmin.x == pmax.x && pmin.y == pmax.y){
		lower.push_back(pmin);
		return lower;
	}
	int n = points.size();
	nth_element(points.begin(), points.begin() + n/2, points.end(), myfunction);
	cordinate pl, pr;
	lowerBridge(points, pl, pr, points[n/2].x);
	vector<cordinate> Tleft = divide(pmin, pl, points, 2, 1);//2==clockwise
	vector<cordinate> Tright = divide(pmax, pr, points, 1, 1);//1==counterclockwise
	lower = LOWER_HULL(pr, pmax, Tright);
	lower.splice(lower.end(),LOWER_HULL(pmin, pl, Tleft) );
	return lower;
}


void KIRKPATRICK_SEIDAL::kirkpatrick_seidal(vector<cordinate> cordinates){
	cordinate pmin, pmax, pmin2, pmax2;
	findpmin(cordinates, pmin, pmax, pmin2, pmax2);
	//adding pmin and pmax and calling upper hull 
	cordinates.push_back(pmin);
	cordinates.push_back(pmax);
	list<cordinate> upper = UPPER_HULL(pmin, pmax, cordinates);
	cordinates.pop_back();
	cordinates.pop_back();

	//adding pmin2 and pmax2 and calling lower hull 

	cordinates.push_back(pmin2);
	cordinates.push_back(pmax2);
	list<cordinate> lower = LOWER_HULL(pmin2, pmax2, cordinates);

	if(pmin.y==pmin2.y){
		lower.pop_back();
	}
	if(pmax.y==pmax2.y){
		lower.pop_front();
	}
	upper.splice(upper.end(), lower);
	for_each(upper.begin(), upper.end(), [] (cordinate i){cout<<i.x<<" "<<i.y<<"\n";});
	cout<<"Number of points in Convex Hull "<<upper.size();
}