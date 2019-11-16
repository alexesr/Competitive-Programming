#include <bits/stdc++.h>
using namespace std;

struct point{
	double x, y;
}points[16];
int N;

double distance(int i, int j){
	double x = points[i].x-points[j].x;
	double y = points[i].y-points[j].y;
	return sqrt(x*x+y*y);
}
double mem[16][1<<16];
double make_pairs(int index, int visited){
	//cout<<"RC: index: "<<index<<" visted: "<<visited<<"\n";	
	double besti =INT_MAX;
	int C  = 1<<index;
	//cout<<"BF while: index: "<<index<<" visited:"<<visited<<"\n";
	while((visited&C)!=0 && index<N){
		index++;
		C<<=1;
	}
	//cout<<"AF while: index: "<<index<<" visited:"<<visited<<"\n";
	if(index==N)
		return 0;

	if(mem[index][visited]!=-1.0)
		return mem[index][visited];	
	visited = visited | (1<<index);
	for(int i= index+1; i<N;i++){
		//cout<<"index:"<<index<<" i: "<<i<<"N:"<<N<<"\n";
		//cout<<(visited&(1<<i))<<"\n";
		if((visited&(1<<i))==0){
			//cout<<"Not visited ["<<i<<"]\n";
			visited= visited | (1<<i);// visted |=(1<<i);
			besti = min(make_pairs(index+1,visited)+distance(index,i), besti);
			visited = visited ^ (1<<i);
			
		/*  0 xor 0 = 0
		   [0 xor 1 = 1] <-This will never happen since our (1<<i) will always have just one bit ON
			1 xor 0 = 1
			1 xor 1 = 0
		*/
		}
	}
	mem[index][visited] = besti;
	return mem[index][visited];
}
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	string name;
	int tc =0;
	cin>>N;
	while(N){
		N<<=1;
		for(int i=0; i<N;i++){
			for(int j=0; j<(1<<N);j++)
				mem[i][j] = -1;
			cin>>name>>points[i].x>>points[i].y;
		}
		cout<<"Case "<<(++tc)<<": "<<fixed<<setprecision(2)<<make_pairs(0,0)<<"\n";
		cin>>N;
	}
	return 0;
}
