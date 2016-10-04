#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
 
using namespace std;

long long a[32768], s[32768];
int main()
{
	int n;
	cin >> n;
	
	int x, w;
	for (int i = 0; i < 32768; i++) a[i] = 0;
	for (int i = 0; i < 32768; i++) s[i] = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> w;
		a[x] += w;
	}
	long long sum = 0;
	for (int i = 0; i < 32768; i++)
	{
		sum += a[i];
		s[i] = sum;
	}
	//int mid = ceil(sum/2);
	int i = 32767;
	while (s[i] > sum-s[i] && i > 0) --i;
	//cout << i <<endl;
	if (s[i] < sum-s[i]) ++i;
	else while (a[i] == 0 ) --i;
	int ans = i;		
	long long minimum = 0;
	for (int i = 0; i < ans; i++) minimum += a[i]*(long long)(ans-i);
	for (int i = ans+1; i < 32768; i++) minimum += a[i]*(long long)(i-ans);
	
	cout << ans << endl << minimum <<endl;
	return 0;
}