#include <algorithm>
#include <vector>
#include <iostream>
#include <random>
using namespace std;


void _merge(vector<int> &a, int l, vector<int> &A, vector<int> &B)
{
	int p1=0;
	int p2=0;
	int p=l;
	while(p1<A.size() && p2<B.size())
	{
		if(A[p1]<B[p2])
			a[p++]=A[p1++];
		else
			a[p++]=B[p2++];
	}
	while(p1<A.size())
		a[p++]=A[p1++];
	while(p2<B.size())
		a[p++]=B[p2++];
}
void merge(vector<int> &a, int l, int r)
{
	//take care of case where r>=n
	int n=a.size();
	int mid=(l+r)/2;
	r=min(r,n-1);

	vector<int>A;
	vector<int>B;

	for(int i=l;i<=mid;i++)
		A.push_back(a[i]);
	for(int i=mid+1;i<=r;i++)
		B.push_back(a[i]);

	_merge(a, l, A, B);
}

void merge_sort(vector<int> &a)
{
	int n=a.size();
	for(int i=2;i<=2*n;i*=2)
	{
		for(int j=0;j<n;j+=i)
			merge(a,j,j+i-1);
	}
}

int main()
{
	mt19937 rng(696967);

	vector<vector<int>> tests={
		{},
		{1},
		{2,1},
		{1,2},
		{1,1,1,1},
		{1,2,3,4,5},
		{5,4,3,2,1},
		{5,1,5,2,5,3,5},
		{-5,-1,-3,-2,-4},
		{INT_MIN,0,INT_MAX,-1,1}
	};

	// Random tests
	for(int t=0;t<10000;t++)
	{
		int n=rng()%1000;
		vector<int> a(n);

		for(int i=0;i<n;i++)
			a[i]=uniform_int_distribution<int>(-100000,100000)(rng);

		tests.push_back(a);
	}

	for(int tc=0;tc<(int)tests.size();tc++)
	{
		vector<int> a=tests[tc];
		vector<int> expected=a;

		sort(expected.begin(),expected.end());

		merge_sort(a);

		if(a!=expected)
		{
			cout<<"FAILED on test "<<tc<<endl;

			cout<<"Input:    ";
			for(int x:tests[tc])
				cout<<x<<" ";
			cout<<endl;

			cout<<"Expected: ";
			for(int x:expected)
				cout<<x<<" ";
			cout<<endl;

			cout<<"Got:      ";
			for(int x:a)
				cout<<x<<" ";
			cout<<endl;

			return 1;
		}
	}

	cout<<"All "<<tests.size()<<" tests passed!"<<endl;

	return 0;
}