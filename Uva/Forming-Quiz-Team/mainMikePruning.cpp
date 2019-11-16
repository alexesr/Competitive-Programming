#include <bits/stdc++.h>
///problem: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1852
using namespace std;

int n;
pair<int,int>coordinates[16];
string name;
struct node{
    int val;
    node *next;
    node(){}
    node(int val){
        next=NULL;
        this->val=val;
    }
};

node * globalNav = NULL;

int lineD(int a , int b ){
    return a-b;
}

double d(int i , int j ){
    int xDelta = lineD(coordinates[i].first,coordinates[j].first) , yDelta = lineD(coordinates[i].second,coordinates[j].second);
    return  sqrt(xDelta * xDelta + yDelta * yDelta) ;
}

double f(int i , int v ){
    if(v==(1<<n)-1) return 0 ; ///done with all points
    node * globaNavCopyMaster = globalNav;
    while((v&(1<<i))&&i<n) i++;
    while(globalNav&&globalNav->val<i) globalNav = globalNav->next ;
    double ans = INT_MAX;
    node * globalNavCopy = globalNav;
    node * before = NULL;
    for(node * nav = globalNav -> next ; nav ; nav = nav->next){
        if(!before){
            globalNavCopy = globalNav;
            globalNav=globalNav->next ;
        }else{
            globalNavCopy=NULL;
            ///erase it
            before -> next = nav->next ;
        }
        ans = min(ans,f(i+1,v|(1<<i)|(1<<nav->val))+d(i,nav->val));
        if(globalNavCopy){
            globalNav = globalNavCopy;
        }else{
            ///return node
            before->next = nav;
        }
        before = nav;
    }
    globalNav = globaNavCopyMaster ;
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);
    int c=1;
    while(cin >>n,n){
        n <<= 1 ;
        node * before = NULL;
        globalNav = NULL;
        for(int i = 0 ; i < n ; i ++ ){
            node * newNode = new node(i);
            if(before)
                before->next = newNode;
            else
                globalNav = newNode;
            before = newNode;
            cin >> name >> coordinates[i].first >> coordinates[i].second;
        }
        cout << "Case " << c++ << ": " << fixed << setprecision(2) << f(0,0) << "\n" ;
    }
    return 0;
}
