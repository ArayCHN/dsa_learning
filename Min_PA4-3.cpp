#include <cstdio>
#include <iostream>

using namespace std;

class heap
{
	int size;
	int *a;
	void deleteit(); // delete the root
	void up(int pos); // adjust the relevent position to maintain the heap
	void down(int pos); // maintain the heap
	void swap(int &x, int &y);
public:
	heap(int k):size(0) { a = new int[k + 3]; }
	int root() { return a[1]; } // return the root
	void insert(int, int);
};

void heap::swap(int &x, int &y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

void heap::insert(int x, int k)
{
	if (size == k && a[1] < x) return; // not among k smallest, rule out directly
	size++;
	a[size] = x;
	up(size);
	if (size > k) deleteit(); // keep size <= k
}

void heap::up(int curr_pos) // upward adjustment
{
	int par = curr_pos >> 1; // parent
	while (par > 0 && a[par] < a[curr_pos]) 
	{
		swap(a[par], a[curr_pos]);
		curr_pos = par;
		par = curr_pos >> 1;
	}
}

void heap::down(int curr_pos) // downward adjustment
{
	while (true)
	{
		int lc = curr_pos * 2;
		int rc = lc + 1;
		if (lc > size) return;
		if (rc > size)
		{
			if (a[curr_pos] < a[lc]) swap(a[curr_pos], a[lc]);
			return;
		}
		if (a[curr_pos] >= a[lc] && a[curr_pos] >= a[rc]) return; // partial order requirement met
		if (a[lc] > a[rc])
		{
			swap(a[curr_pos], a[lc]);
			curr_pos = lc; // go to the next layer
		}
		else
		{
			swap(a[curr_pos], a[rc]);
			curr_pos = rc; // go to the next layer
		}
	}
}

void heap::deleteit()
{
	a[1] = a[size--]; // maintain the heap size < k
	down(1);
}

int main()
{
	int n, k, x;
	fread(&n, sizeof(int), 1, stdin);
	fread(&k, sizeof(int), 1, stdin);
	heap h(k);
	for (int i = 0; i < n; i++)
	{
		fread(&x, sizeof(int), 1, stdin);
		h.insert(x, k);
	}
	printf("%d\n", h.root()); // the heap root is the largest among the k smallest
	return 0;
}