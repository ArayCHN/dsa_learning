#include <cstdio>

int getLchild(int root, int* &pre, int* &mid, int *loc_pre, int *loc_mid)
{
	return pre[root + 1];
}
int getRchild(int root, int *pre, int *mid, int *loc_pre, int *loc_mid)
{
	return pre[loc_mid[root + 1];
}

bool hasLchild(int root, int *loc_pre, int *loc_mid, int *pre)
{
	return loc_pre[root] < n - 1 && loc_mid[pre[loc_pre[root] + 1 ]] < loc_mid[root]; // the node directly after root in pre meanwhile before root in mid must be in the left subtree of root
}

bool hasRchild(int root, int *loc_pre, int *loc_mid, int *mid)
{
	return loc_mid[root] > 0 && loc_pre[mid[loc_mid[root] + 1]] > loc_pre[root]; // similar to hasLchild
}

void go_to_bottom(int *stack, int &top, int &root， int *loc_pre, int *loc_mid, int *pre, int *mid)
{
	while (true)
	{
		stack[top ++] = pre[root]; // the local root
		visited[top] = 1;
		if (hasRchild(root, loc_pre, loc_mid, pre))
			stack[top++] = getRchild(root, pre, mid, loc_pre, loc_mid);
		if (hasLchild(root, loc_pre, loc_mid, mid))
			root = getLchild(root, pre, mid, loc_pre, loc_mid);
		else if (hasRchild(root, loc_pre, loc_mid, pre)) root = stack[top--];
		else break;
	}
}

//bool popped = false;

void pop(int *stack, int &top, int &root)
{
	printf("%d ", stack[top--]);
	root = stack[top];
}

bool isfather(int node, int fa, int *loc_pre, int *loc_mid, int *pre, int *mid)
{
	int lc = pre[loc_pre[fa] + 1];
	if (loc_mid[lc] < loc_mid[fa] && lc == node) // lc indeed is the leftchild of fa
		return true;
	int rc = pre[loc_mid[fa] + 1];
	if (hasRchild(fa, loc_pre, loc_mid, mid) && rc == node) // node is the right child of father
		return true;
	return false;
}

int main(){
	scanf("%d", n);
	int *pre = new int [n];
	int *mid = new int [n];
	int *loc_pre = new int [n]; // in order to find the node in o(1)
	int *loc_mid = new int [n];
	for (int i = 0; i < n; i++) visited[i] = 0; // nothing's been visited
	for (int i = 0; i < n; i++)
	{
		scanf("%d", pre[i]); // the sequence of pre-order traversing
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%d", mid[i]);
		loc_pre[pre[i]] = i;
	}
	int *stack = new int [n];
	int root = pre[0];
	int top = 0;
	while (true)
	{
		got_to_bottom(stack, top, root, loc_pre, loc_mid, pre, mid); // go to highest left-most leaf (at bottom)
		while (top > 0 && isfather(root, stack[top - 1])) // if stack[top - 1] is the father of root
			pop(stack, top, root);
		if (top == 0) break;
	}
	printf("%d\n", stack[0]);
	return 0;
}