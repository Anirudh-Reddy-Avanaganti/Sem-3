#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
using namespace std;

class Heap{
	vector<int> a;
	int sz;

	int parent(int i)
	{
		return (i-1)/2;
	}

	int left(int i)
	{
		return (2*i+1);
	}

	int right(int i)
	{
		return (2*i+2);
	}

	void bubbleUp(int idx)
	{	
		while((idx>0) && (a[parent(idx)]>a[idx]))
		{
			swap(a[idx],a[parent(idx)]);
			idx=parent(idx);
		}
	}

	void bubbleDown(int idx)
	{
		while(left(idx)<sz)
		{
			if(right(idx)>=sz)
			{
				if(a[left(idx)]<a[idx])
				{
					swap(a[left(idx)],a[idx]);
					idx=left(idx);
				}
				else
					return;
			}
			else if(a[left(idx)]<a[right(idx)])
			{
				if(a[left(idx)]<a[idx])
				{
					swap(a[left(idx)],a[idx]);
					idx=left(idx);
				}
				else
					return;
			}
			else
			{
				if(a[right(idx)]<a[idx])
				{
					swap(a[right(idx)],a[idx]);
					idx=right(idx);
				}
				else	
					return;
			}
		}
	}

	public:
	
	Heap()
	{
		a=vector<int>();
		sz=0;
	}
	int pop()
	{
		int ans=a[0];
		a[0]=a.back();
		a.pop_back();
		bubbleDown(0);
		sz--;
		return ans;
	}

	void push(int x)
	{
		a.push_back(x);
		bubbleUp(sz);
		sz++;
	}

	int size()
	{
		return sz;
	}
};

int main()
{
	mt19937 rng(12345);

	Heap h;
	vector<int> v;

	for(int i=0;i<10000;i++)
	{
		if(v.empty() || rng()%2==0)
		{
			int x=(int)(rng()%1001)-500;

			h.push(x);
			v.push_back(x);
		}
		else
		{
			sort(v.begin(),v.end());

			int expected=v[0];
			int actual=h.pop();

			assert(actual==expected);

			v.erase(v.begin());
		}
	}

	while(!v.empty())
	{
		sort(v.begin(),v.end());

		int expected=v[0];
		int actual=h.pop();

		assert(actual==expected);

		v.erase(v.begin());
	}

	assert(h.size()==0);

	cout<<"INTERLEAVED TEST PASSED!\n";

	return 0;
}