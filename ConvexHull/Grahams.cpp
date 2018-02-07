#include <iostream>
#include <algorithm>
#include <vector>
#include "Grahams.h"

#define pb push_back	

using namespace std;

template < typename T>
ostream& operator <<(ostream& o,vector<T> a){
	size_t n= a.size();
	for(size_t i=0;i<n;i++){
		o<<a[i].x<<" "<<a[i].y<<"\n";
	}
	return o;
}

template< typename T>
void display(T a[],int n){
        
        for( int i=0;i<n;i++){
                cout<<a[i]<<" ";
        }
        cout<<endl;
}


//global variable p0 for origin
cordinate p0;

void findp0(vector<cordinate> &a){
	int n = a.size();
	//taking min y point to end of array
	for(int i = 0;i < n-1; i++){
		if(a[i].y < a[n-1].y || (a[i].y == a[n-1].y && a[i].x < a[n-1].x)){
			swap(a[i],a[n-1]);
		}
	}
	p0=a[n-1];
	a.resize(n-1);
}

int Graham::angle(cordinate a, cordinate b, cordinate c)
{
    int val = (b.x-a.x)*(c.y-b.y)-(b.y-a.y)*(c.x-b.x);
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; //  counterclock or clock wise
}

int dis(cordinate a,cordinate b){
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

bool compare1(cordinate p1, cordinate p2){
	int C = Graham::angle(p0, p1, p2);
	if(C==0)
		return dis(p0, p1) <= dis(p0, p2) ;
	return C==1;
}

void Graham::Grahams(vector<cordinate> cordinates){
	//lowest point
	findp0(cordinates);
	
	sort(cordinates.begin(),cordinates.end(),compare1);
	
	//removing points at same Graham::angle from p0
	int k=0;//size of new vector
	
	for(int i = 0; i < cordinates.size();i++){
		while(i < cordinates.size()-1 && Graham::angle(p0, cordinates[i],cordinates[i+1])==0)
			i++;
		if(i<cordinates.size())
			cordinates[k]=cordinates[i];
		k++;
	}
	if(k<2){
		cout<<"Convex hull not possible";
		return;
	}
	cordinates.resize(k);
	vector<cordinate> S;
	S.pb(p0);
	S.pb(cordinates[0]);
	S.pb(cordinates[1]);
	for(int i=2;i<cordinates.size();i++){
		while(Graham::angle(S[S.size()-2],S.back(),cordinates[i]) != 1){
			S.pop_back();
		}
		S.pb(cordinates[i]);
	}
	cout<<S;
	cout<<"Number of points in Convex Hull "<<S.size()<<endl;
}

