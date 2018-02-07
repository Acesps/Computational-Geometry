#include <iostream>
#include <algorithm>
#include <vector>
#include "Grahams.h"
#include "jarvis.h"

#define pb push_back

using namespace std;

template < typename T>
ostream& operator <<(ostream& o, vector<T> a){
	size_t n = a.size();
	for(size_t i = 0;i < n; i++){
		o<<a[i].x<<" "<<a[i].y<<"\n";
	}
	return o;
}

void Jarvis::jarvis(vector<cordinate> cordinates){
	//leftmost point
	vector<cordinate> S;
	int l = 0;
	for(int i = 1;i < cordinates.size(); i++){
		if(cordinates[i].x < cordinates[l].x)
			l = i;
	}
	int first = l;
	int second;
	do{	
 		second = (first + 1) % cordinates.size();
 		S.pb(cordinates[first]);
		for(int i = 0;i < cordinates.size(); i++)
			if(Graham::angle(cordinates[first],cordinates[i],cordinates[second]) == 1)
				second = i;
		first = second;
	}while(first != l);
	cout<<S;
	cout<<"Number of points in Convex Hull "<<S.size()<<endl;
}