#include<bits/stdc++.h>
using namespace std;

class SegmentTree{
    public:
    vector<int> seg;
    vector<int> lazy;
    vector<int> arr;

    SegmentTree(int n, vector<int> a){
        seg.resize(4*n);
        lazy.resize(4*n, 0);
        arr = a; // if TLE use global array;
    }

    void build(int root, int low, int high){
        if(low > high) return;
        if(low == high){
            seg[root] = arr[low];
            return;
        }
        int mid = low + (high-low)/2;
        build(2*root+1, low, mid);
        build(2*root+2, mid+1, high);
        seg[root] = seg[root*2+1] + seg[2*root+2];
    }

    void pointUpdate(int root, int low, int high, int idx, int val){
        if(low == high){
            seg[idx] = val;
            return;
        }

        int mid = low + (high-low)/2;

        if(idx<=mid){
            pointUpdate(2*root+1, low, mid, idx, val);
        }else{
            pointUpdate(2*root+2, mid+1, high, idx, val);
        }

        seg[root] = seg[2*root+1] + seg[2*root+2];
    }

    int rangeQuery(int root, int low, int high, int l, int r){
        if( r<low ||  high < l || l > r)return 0;
        // full overlap
        if(l <= low && high <= r){
            return seg[root];
        }
        //partial overlap
        int mid = low + (high-low)/2;
        return rangeQuery(2*root+1, low, mid, l, r) + 
                rangeQuery(2*root+2, mid+1, high, l, r);
    }

    int rangeUpdate(int root, int low, int high, int l, int r, int val){
        if(lazy[root]!=0){
            seg[root]+=(high-low+1)*lazy[root];

            if(low!=high){
                lazy[2*root+1] += val;
                lazy[2*root+2] += val;
            }
            lazy[root] = 0;
        }

        if(l > high || r < low) return;

        if(low>=l && high<=r){
            seg[root] += (high-low+1) * val;
            if(low!=high){
                lazy[2*root+1]+=val;
                lazy[2*root+2]+=val;
            }
            return;
        }
        int mid  = low+(high-low)/2;
        rangeUpdate(2*root+1, low, mid, l, r, val);
        rangeUpdate(2*root+2, mid+1, high, l, r, val);
    }
};