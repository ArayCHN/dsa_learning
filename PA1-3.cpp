#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	int n, a[500000] , b[500000], c[500000], hash[500000];
	memset(hash, 0, sizeof(hash));//stores the coach number
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
	for (int i = 0; i < n; i++)
	scanf("%d", &b[i]);
	for (int i = 0; i < n; i++)
	scanf("%d", &c[i]);
	int k;
	cin >> k;
	int h1 = 0, h2 = 0, h3 = 0, tot = 0;
	while (tot < n-3) //simulates the process of allocating
	{
		
		while (hash[a[h1]] != 0) h1++; hash[a[h1]] = 1; 
		while (hash[b[h2]] != 0) h2++; hash[b[h2]] = 2; 
		while (hash[c[h3]] != 0) h3++; hash[c[h3]] = 3; 
		tot +=3;
	}
	/* needs to see if there's still members left to be chosen */
	while (hash[a[h1]] != 0) h1++; hash[a[h1]] = 1; ++tot;
	if (tot < n) { while (hash[b[h2]] != 0) h2++; hash[b[h2]] = 2; ++tot; }
	if (tot < n) { while (hash[c[h3]] != 0) h3++; hash[c[h3]] = 3; ++tot; }
	switch (hash[k])
	{
		case 1: printf("A\n"); break;
		case 2: printf("B\n"); break;
		case 3: printf("C\n"); break;
	}
	return 0;
}