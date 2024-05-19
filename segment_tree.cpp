#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
typedef long long int ll;


using namespace std;
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>


void build(ll index,ll low,ll high,vector<ll> &arr,vector<ll> &segArray)
{
    if(low==high)
    {
        segArray[index] = arr[low];
        return;
    }

    ll mid = (low+high)/2;

    build(2*index+1,low,mid,arr,segArray);
    build(2*index+2,mid+1,high,arr,segArray);

    segArray[index]=min(segArray[2*index+1],segArray[2*index+2]);


}

ll query(ll index,ll low,ll high,ll l,ll r,vector<ll> &segArray)
{
    // no overlap
    ///[low high l r] or [l r low high]

    if(high<l || low>r)
    {
        return LONG_MAX;
    }


    // Complete Overlap
    /// [l low high r]

    if(low>=l && high<=r)
    {
        return segArray[index];
    }

    /// Partial overlap

    ll mid = (low+high)/2;

    ll left=query(2*index+1,low,mid,l,r,segArray);
    ll right=query(2*index+2,mid+1,high,l,r,segArray);

    return min(left,right);

}

void update(ll index,ll low,ll high,ll updateIndex,ll value,vector<ll> &segArrray)
{
    if(low==high)
    {
        segArrray[index]=value;
        return;
    }

    ll mid = (low+high)/2;

    if(updateIndex<=mid)
        update(2*index+1,low,mid,updateIndex,value,segArrray);
    else
        update(2*index+2,mid+1,high,updateIndex,value,segArrray);

    segArrray[index]=min(segArrray[2*index+1],segArrray[2*index+2]);
}


void solve()
{
    int n;
    cin>>n;

    vector<ll> arr(n);

    for(ll i=0; i<n; i++)
    {
        cin>>arr[i];
    }

    vector<ll> segArray(4*n,LONG_MAX);


    build(0,0,n-1,arr,segArray);

    ll q;
    cin>>q;

    while(q--)
    {
       int type;
       cin>>type;

       if(type==1)
       {
           ll l,r;
           cin>>l>>r;

           cout<<query(0,0,n-1,l,r,segArray);
       }
       else if(type==2)
       {
           ll updateIndex,value;
           cin>>updateIndex>>value;

           update(0,0,n-1,updateIndex,value,segArray);

           arr[updateIndex]=value;
       }
    }
}


int main()
{
    int t;

    t=1;
    cin>>t;

    while(t--)
    {
        solve();
    }

    return 0;
}
