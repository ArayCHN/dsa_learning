#include <cstdio>
#include <iostream>
//#include <cstring>
using namespace std;

int a[10000001] ; int  status[10000001]; int offwork[10000001];
int main()
{
	int n,m;
	cin >> n >> m;
	
	//memset(status, 0, sizeof(status));
	//memset(offwork, -1, sizeof(offwork));
	//cout<< "OK!" <<endl;
	for (int i = 0; i <= n; i++) status[i] = 0;
	for (int i = 0; i <= n; i++) offwork[i] = -1;	
	char op;
	int num, code;
	int tot = 0, rec = 0, ans = 0;
	for (int i = 0; i < m; i++)
	{
		//scanf("%c", &op);
		//while (op == ' ' || op == '\n' ) scanf("%c", &op);
		cin >> op;
		switch (op)
		{
		case 'I': //scanf("%d%d", &num, &code);
				  cin >> num >> code;
			 	  a[num] = code;
			 	  if (status[num] == 0 || offwork[num] != rec) 
			 	  	{
			 	  		tot++;
			 	  		offwork[num] = rec;
			 	  		status[num] = 1;
			 	  	}
			 	  // for debug: cout << num << ' ' << code << endl;
			 	  break;
		case 'O': //scanf("%d", &num);
				  cin >> num;
			 	  if (status[num] == 1 && offwork[num] == rec) tot--;
			 	  status[num] = 0;
			 	  break;
		case 'Q': //scanf("%d", &num);
				  cin >> num;
			 	  if (status[num] == 1 && offwork[num] == rec) ans += a[num];
			 	  else ans -= 1;
			 	  break;
		case 'C': tot = 0;
			 	  rec ++; //record stores the time of off work. once, twice, or more?
			 	  break;
		case 'N': ans += tot;
				  // for debug: cout << tot;
				  break;
		}
	}
	cout << ans << endl;
	return 0;
}