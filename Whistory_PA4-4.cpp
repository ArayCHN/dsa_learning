#include <cstdio>
#include <iostream>

using namespace std;

char** str;
int* nxt, *ans, *key;
int m, n;

void expand(int i)
{
	for (int j = 0; j < n; j++)
		str[i][n + j] = str[i][j];
}

bool compare(int x, int y) // KMP, find str[x] in str[y]
{
	int ly = 2 * n;
	int ix = -1, iy = -1;
	while (ix < n && iy < ly)
	{
		if (ix < 0 || str[x][ix] == str[y][iy]) // if ix = -1, matches all
		{
			++ix;
			++iy;
		}
		else
			ix = nxt[ix];
	}
	if (ix >= n) // everything 0..n-1 matched before
		return true;
	else// ix <=n && iy has reached end
		return false;
}

void find_nxt(int i) // initialize nxt[] in KMP
{
	nxt = new int[n];
	nxt[0] = -1;
	int ix = -1; int iy = 0;
	while (iy < n - 1)
	{
		if (ix < 0 || str[i][ix] == str[i][iy]) // if ix = -1, matches all
			nxt[++iy] = ++ix;
		else
			ix = nxt[ix];
	}
}

int match(int i)
{
	find_nxt(i);
	bool has_pre = false;
	for (int j = 0; j < i; j++)
	{
		if (ans[j] == j && key[j] == key[i] && compare(i, j)) // find the first match
		{
			ans[i] = j;
			has_pre = true;
			break;
		}
	}
	delete [] nxt;
	if (!has_pre) ans[i] = i; // no match found, return itself
	return ans[i];
}

int generate_key(int i)
{
	int s = 0;
	for (int j = 0; j < n; j++)
		s += (int)(str[i][j]-'a'); // same key with the same set of letters, different order
	return s;
}

int main()
{
	scanf("%d%d", &m, &n);
	str = new char*[m];
	ans = new int[m];
	key = new int[m];
	for (int i = 0; i < m; i++)
	{
		str[i] = new char[n << 1];
		scanf("%s", str[i]);
		key[i] = generate_key(i); // use key to rule out strings with different letters
		expand(i); // double the string to mimic a "circle"
		printf("%d\n", match(i));
	}
	return 0;
}