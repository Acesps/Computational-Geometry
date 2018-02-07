#include <iostream>
#include <algorithm>
#include <vector>
#include "Grahams.h"
#include "kirkpatrick_seidal.h"
#include "jarvis.h"
#include <ctime>
#include <stdlib.h>     
#include <time.h>       

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


int main()
{	/*cordinate points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                      {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int n = sizeof(points)/sizeof(points[0]);
    vector<cordinate> cordinates(points,points+n);
    */
	int n,ans;
	cordinate input;
	vector<cordinate> cordinates;
	cout<<"Select mode:\n\t 1> Random points \n\t 2>Feed points from stdin\n press 1 | 2\n";
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
	/*cout<<"points are"<<endl;
	cout<<cordinates;
	*/
	cout<<"Running Graham's Algorithm:"<<endl;
	clock_t t=clock();
	Graham::Grahams(cordinates);
    cout << "Time taken by Graham's Algorithm:" << (t-clock()) * 1000.0 / CLOCKS_PER_SEC << " ms" << '\n';
	
	cout<<"Running Jarvis Algorithm:"<<endl;
	t=clock();  
    Jarvis::jarvis(cordinates);
    cout << "Time taken by Jarvis Algorithm:" << (t-clock()) * 1000.0 / CLOCKS_PER_SEC << " ms" << '\n';
    
    cout<<"Running kirkpatrick-seidal Algorithm:"<<endl;
	t=clock();  
    KIRKPATRICK_SEIDAL::kirkpatrick_seidal(cordinates);
    cout << "Time taken by kirkpatrick-seidal Algorithm:" << (t-clock()) * 1000.0 / CLOCKS_PER_SEC << " ms" << '\n';
    return 0;
} 
