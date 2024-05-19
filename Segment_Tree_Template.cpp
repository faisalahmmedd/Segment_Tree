#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
typedef long long int ll;


using namespace std;
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

class segmentTree
{

    vector<ll> segArray;

public:
    segmentTree(ll n)
    {
        segArray.resize(4*n);
    }

    void build(ll index,ll low,ll high,vector<ll> &arr)
    {
        if(low==high)
        {
            segArray[index]=arr[low];
            return;
        }

        ll mid = (low+high)/2;

        build(2*index+1,low,mid,arr);
        build(2*index+2,mid+1,high,arr);

        segArray[index] = min(segArray[2*index+1],segArray[2*index+2]);
    }

    ll query(ll index,ll low,ll high,ll l,ll r)
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

        ll left=query(2*index+1,low,mid,l,r);
        ll right=query(2*index+2,mid+1,high,l,r);

        return min(left,right);


    }

    void update(ll index,ll low,ll high,ll updateIndex,ll value)
    {
        if(low==high)
        {
            segArray[index]=value;
            return;
        }

        ll mid=(low+high)/2;

        if(updateIndex<=mid)
            update(2*index+1,low,mid,updateIndex,value);
        else
            update(2*index+2,mid+1,high,updateIndex,value);

        segArray[index]=min(segArray[2*index+1],segArray[2*index+2]);
    }

    void display()
    {
        for(auto s:segArray)
        {
            cout<<s<<" ";
        }
        cout<<endl;
    }


};


void solve()
{
    ll n1;
    cin>>n1;

    vector<ll> arr1(n1);

    for(ll i=0; i<n1; i++)
    {
        cin>>arr1[i];
    }

    segmentTree sgt1(n1);

    sgt1.build(0,0,n1-1,arr1);

    // sgt1.display();

    ll n2;
    cin>>n2;

    vector<ll> arr2(n2);

    for(ll i=0; i<n2; i++)
    {
        cin>>arr2[i];
    }

    segmentTree sgt2(n2);

    sgt2.build(0,0,n2-1,arr2);


    ll q;
    cin>>q;

    while(q--)
    {
        ll type;
        cin>>type;

        if(type==1)
        {
            ll l1,r1,l2,r2;
            cin>>l1>>r1>>l2>>r2;

            ll min1=sgt1.query(0,0,n1-1,l1,r1);
            ll min2=sgt2.query(0,0,n2-1,l2,r2);
            cout<<min(min1,min2);
        }
        else
        {
           ll arrayNo,updateIndex,value;
           cin>>arrayNo>>updateIndex>>value;

           if(arrayNo==1)
           {
             sgt1.update(0,0,n1-1,updateIndex,value);
           }
           else
           {
               sgt2.update(0,0,n2-1,updateIndex,value);
           }
        }
    }





}


int main()
{
    int t;
    cin>>t;

    while(t--)
    {
        solve();
    }

    return 0;
}
