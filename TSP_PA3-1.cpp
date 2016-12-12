#include <iostream>
#include <cstdio>
using namespace std;

struct NEIGHBOUR
{
	int num, value;
	NEIGHBOUR *nxt;
};

struct node
{
	NEIGHBOUR *first, *last; // first is where we start our search; last is the newest neighbour
	int pred_num; // the number of predecessors
	void insert(int, int, node*);
	node();
};

inline node::node()
{
	first = NULL;
	pred_num = 0; // the number of predecessors
}

void node::insert(int b, int price, node *g)
{
	if (first) // already has at least one neighbour, won't change 'first' any more
	{
		last->nxt = new NEIGHBOUR;
		last = last->nxt;
		last->num = b;
		last->value = price;
		last->nxt = NULL;
		g[b].pred_num++;
	} else // insert the first neighbour
	{
		first = new NEIGHBOUR;
		first->num = b;
		first->value = price;
		last = first;
		last->nxt = NULL;
		g[b].pred_num++;
	}
}

int *path;

void update(int a, int &b, int j, int i)
{
	if (a > b || (a == b && j < path[i])) //keep path[i] as small as possible
	{
		path[i] = j;
		b = a;
	}
}

#define maxint 1000000;

static int maxvalue[100001];

int dfs(int i, node* g) // depth-first searching, go through every path to find the largest one
{
	if (maxvalue[i]) return maxvalue[i]; // the nodes already explored needn't be searched again
	NEIGHBOUR *nbr = g[i].first; // start from the first neighbour, find all neighbours
	int max = 0;
	while (nbr)
	{
		update(dfs(nbr->num, g) + nbr->value, max, nbr->num, i);
		nbr = nbr->nxt;
	}
	return (maxvalue[i] = max); // maxvalue[] stores the maximum profit after this node, preventing repetitive search
}

void find_max_path(int i)
{
	printf("%d", i);
	while (i = path[i]) // when encountering 0, will stop printing the path.
	{
		printf("\t%d", i);
	}
	printf("\n");
}

int main()
{
	int n,m;
	scanf("%d%d", &n, &m);
	node* g = new node[n + 1];
	path = new int[n + 1];
	for (int i = 0; i < n + 1; i++) path[i] = 0; // when encountering 0, will stop printing the path.
	int a, b, price;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &a, &b, &price);
		g[a].insert(b, price, g); // store the graph in the form of a list
	}
	int max = 0, maxnum;
	for (int i = 1; i < n + 1; i++)
	{
		if (!g[i].pred_num) // find out all nodes with no predecessor, as the start of a trip
		{
			int newgain = dfs(i, g);
			if (newgain > max) // if equals, won't update since the latter is larger in dictionary order
			{
				max = newgain;
				maxnum = i; // keep track of the starting point with the maximum profit.
			}
		}
	}
	find_max_path(maxnum);
	return 0;
}