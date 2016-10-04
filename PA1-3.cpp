#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	int n, a[500000] , b[500000], c[500000], hash[500000];
	memset(hash, 0, sizeof(hash));
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++)
		cin >> b[i];
	for (int i = 0; i < n; i++)
		cin >> c[i];
	int k;
	cin >> k;
	int h1 = 0, h2 = 0, h3 = 0, tot = 0;
	while (tot < n-3)
	{
		
		while (hash[a[h1]] != 0) h1++; hash[a[h1]] = 1; 
		while (hash[b[h2]] != 0) h2++; hash[b[h2]] = 2; 
		while (hash[c[h3]] != 0) h3++; hash[c[h3]] = 3; 
		tot +=3;
	}
	while (hash[a[h1]] != 0) h1++; hash[a[h1]] = 1; ++tot;
	if (tot < n) { while (hash[b[h2]] != 0) h2++; hash[b[h2]] = 2; ++tot; }
	if (tot < n) { while (hash[c[h3]] != 0) h3++; hash[c[h3]] = 3; ++tot; }
	switch (hash[k])
	{
		case 1: cout << 'A' << endl; break;
		case 2: cout << 'B' << endl; break;
		case 3: cout << 'C' << endl; break;
	}
	return 0;
}