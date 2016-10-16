#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
 
using namespace std;
#define maxint 32768

long long a[maxint], s[maxint];
int main()
{
	int n;
	cin >> n;
	int x, w;
	for (int i = 0; i < maxint; i++) a[i] = 0;
	for (int i = 0; i < maxint; i++) s[i] = 0; // can use memset instead
	for (int i = 0; i < n; i++)
	{
		cin >> x >> w;
		a[x] += w;
	}
	long long sum = 0;
	for (int i = 0; i < maxint; i++)
	{
		sum += a[i]; // s[i] refers to the a[1]+a[2]+...+a[i], 
		s[i] = sum;  // so that a[i]+...+a[j] can be figured out quickly.
	}
	int i = maxint-1;
	while (s[i] > sum-s[i] && i > 0) --i;
	if (s[i] < sum-s[i]) ++i;
	else while (a[i] == 0 ) --i; // make sure it's with a village
	int ans = i; // ABOVE: finds the place for the hospital, stores it in i

	long long minimum = 0;
	for (int i = 0; i < ans; i++) minimum += a[i] * (long long)(ans-i);
	for (int i = ans+1; i < maxint; i++) minimum += a[i] * (long long)(i-ans);
	cout << ans << endl << minimum << endl;
	return 0;
}