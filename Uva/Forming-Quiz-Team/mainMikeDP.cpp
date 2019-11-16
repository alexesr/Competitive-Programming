#include <bits/stdc++.h>
///problem: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1852
using namespace std;

int n;
pair<int,int>coordinates[16];
double memo[16][1<<16];
string name;

int lineD(int a , int b ){
    return a-b;
}

double d(int i , int j ){
    int xDelta = lineD(coordinates[i].first,coordinates[j].first) , yDelta = lineD(coordinates[i].second,coordinates[j].second);
    return  sqrt(xDelta * xDelta + yDelta * yDelta) ;
}

double f(int i , int v ){
    if(i==n) return 0 ; ///done with all points
    if(v&(1<<i)) return f(i+1,v);///already taken
    if(memo[i][v]!=-1) return memo[i][v];
    memo[i][v] = INT_MAX;
    for(int j = i + 1 ; j < n ; j ++ ) {
        if(!(v&(1<<j))){
            ///no visited
            memo[i][v] = min(memo[i][v],f(i+1,v|(1<<i)|(1<<j))+d(i,j));
        }
    }
    return memo[i][v];
}

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);
    int c=1;
    while(cin >>n,n){
        n <<= 1 ;
        for(int i = 0 ; i < n ; i ++ ){
            fill(memo[i],memo[i]+(1<<n),-1);
            cin >> name >> coordinates[i].first >> coordinates[i].second;
        }
        cout << "Case " << c++ << ": " << fixed << setprecision(2) << f(0,0) << "\n" ;
    }
    return 0;
}
