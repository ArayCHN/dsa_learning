#include <cstdio>
#include <iostream>
using namespace std;

int a[10000001] ; //stores number
int  status[10000001]; //stores timestamp
int main()
{
	int n,m;
	cin >> n >> m;
	
	//memset(status, -1, sizeof(status)); <- can be compiled under clang, but not on oj.
	for (int i = 0; i <= 10000001; i++) status[i] = -1;
	char op;
	int num, code;
	int tot = 0, rec = 0, ans = 0;
	for (int i = 0; i < m; i++)
	{
		cin >> op;
		switch (op)
		{
		case 'I': 
				  cin >> num >> code;
			 	  a[num] = code;
			 	  if (status[num] != rec) //prevents repitition
			 	  	{
			 	  		tot++;
			 	  		status[num] = rec;
			 	  	}
			 	  break;
		case 'O': 
				  cin >> num;
			 	  if (status[num] == rec) tot--;
			 	  status[num] = -1;
			 	  break;
		case 'Q': 
				  cin >> num;
			 	  if (status[num] == rec) ans += a[num];
			 	  else ans -= 1;
			 	  break;
		case 'C': tot = 0;
			 	  rec ++; //record stores the time of off work. once, twice, or more? #TIME STAMP#
			 	  break;
		case 'N': ans += tot;
				  break;
		}
	}
	cout << ans << endl;
	return 0;
}