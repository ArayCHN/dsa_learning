#include <cstdio>
#include <iostream>

using namespace std;

struct node
{
	int lc, rc;// left child, right child
	int loc_mid; // location in in-order sequence
};

bool check = true;

int rebuild(int pl, int pr, int ml, int mr, node *tree, int* pre)
{
	int root = pre[pl];
	int mloc = tree[root].loc_mid; // the location of local root in mid
	if (mloc > ml && mloc <= mr - 1) {  tree[root].lc = rebuild(pl + 1, mloc - ml + pl + 1, ml, mloc, tree, pre);}
	else tree[root].lc = -1;
	if (mloc < mr - 1 && mloc >= ml) {  tree[root].rc = rebuild(pr - mr + mloc + 1, pr, mloc + 1, mr, tree, pre);}
	else tree[root].rc = -1;
	if ((mloc < ml || mloc >= mr) && check)
	{
		printf("%d\n", -1);
		check = false;
	}
	return root;
}

void post(node *tree, int no, int root) // no is the index of the node to be printed, root is used in order to check the printing format
{
	if (no == -1) return;
	post(tree, tree[no].lc, root);
	post(tree, tree[no].rc, root);
	no != root ? printf("%d ", no) : printf("%d\n", no); // if the root is to be printed, post-order has reached end
}

int main()
{
	int n;
	scanf("%d", &n);
	int *pre = new int [n + 1];
	int *mid = new int [n + 1];
	node *tree = new node [n + 1];

	for (int i = 0; i < n; i++)
		scanf("%d", &pre[i]); // the sequence of pre-order traversing
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &mid[i]);
		tree[mid[i]].loc_mid = i; // to record the loc of a node in in-order sequence
	}
	int pl = 0, pr = n; // the subtree is in domain [pl, pr) in pre[]
	int ml = 0, mr = n; // the subtree is in domain [ml, mr) in mid[]
	rebuild(pl, pr, ml, mr, tree, pre); // rebuild the subtree defined by [l, r)

	if (!check) return 0;
	post(tree, pre[0], pre[0]);
	return 0;
}