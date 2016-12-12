#include <cstdio>
#include <iostream>
using namespace std;

int *tree, *l, *r, *mid;
bool *inverted;

void init(int num, int x, int y) // recursively initialize the tree
{
	l[num] = x;
	r[num] = y;
	tree[num] = y - x + 1;
	if (x != y)
	{
		mid[num] = (x + y) >> 1;
		init(num * 2, x, mid[num]);
		init(num * 2 + 1, mid[num] + 1, y);
	}
}

void inv(int i) // deal with the invertion of the section covered by node i
{
	inverted[i] = !inverted[i]; // change not passed to this node's son, so make a mark
	tree[i] = r[i] - l[i] + 1 - tree[i];
}

int change(int num, int x, int y, bool father_has_changed)
{
	if (x == l[num] && r[num] == y)
	{
		if (!father_has_changed) inv(num); // if father has inverted, then two invertions cancel
	} else
	if (y <= mid[num])
	{
		if (father_has_changed) inv(num);
		change(num * 2, x, y, inverted[num]);
		if (inverted[num])
		{
			inv(num * 2 + 1);
			inverted[num] = 0; // has passed the effect to both sons, so change back to normal
		}
		tree[num] = tree[num * 2] + tree[num * 2 + 1]; // update the number of cards
	} else
	if (x > mid[num])
	{
		if (father_has_changed) inv(num);
		change(num * 2 + 1, x, y, inverted[num]);
		if (inverted[num])
		{
			inv(num * 2);
			inverted[num] = 0; // has passed the effect to both sons, so change back to normal
		}
		tree[num] = tree[num * 2] + tree[num * 2 + 1];
	} else // l <= x <= mid | mid+1 <=y <= r
	{
		if (father_has_changed) inv(num);
		change(num * 2, x, mid[num], inverted[num]);
		change(num * 2 + 1, mid[num] + 1, y, inverted[num]);
		inverted[num] = 0;
		tree[num] = tree[num * 2] + tree[num * 2 + 1];
	}
	return tree[num]; // return the current number of cards to update father
}

int inquire(int num, int x, int y, bool father_has_changed)
{
	if (father_has_changed) inv(num); // make the delayed change of father take effect
	if (x == l[num] && r[num] == y)
	{
		return tree[num];
	} else
	if (y <= mid[num])
	{
		int ans = inquire(num * 2, x, y, inverted[num]);
		if (inverted[num])
		{
			inv(num * 2 + 1);
			inverted[num] = 0; // has passed the effect to both sons, so change back to normal
		}
		return ans;
	} else
	if (x > mid[num])
	{
		int ans = inquire(num * 2 + 1, x, y, inverted[num]);
		if (inverted[num])
		{
			inv(num * 2);
			inverted[num] = 0; // has passed the effect to both sons, so change back to normal
		}
		return ans;
	} else
	{
		int ans1 = inquire(num * 2, x, mid[num], inverted[num]);
		int ans2 = inquire(num * 2 + 1, mid[num] + 1, y, inverted[num]);
		inverted[num] = 0; // has effect transferred to both sons
		return ans1 + ans2;
	}
}

int main()
{
	int n,m;
	scanf("%d%d", &n, &m);
	tree = new int[4 * n];
	l = new int[4 * n]; // left boundary
	r = new int[4 * n]; // right boundary
	mid = new int[4 * n];
	inverted  = new bool[4 * n](); // a sign showing whether an invertion has changed 
	                               // and has not been passed to offsprings
	init(1, 1, n);
	int x, y;
	char op;
	for (int i = 0; i < m; i++)
	{
		scanf(" %c%d%d", &op, &x, &y); // prevent reading blank chars
		switch (op)
		{
			case 'H': change(1, x, y, 0); break;
			case 'Q': printf("%d\n", inquire(1, x, y, 0)); break;
		}
	}
	return 0;
}