/*
Used dynamic programming to deal with this problem.
input: two strings to be compared. output: an integer, the length of the longest common sequence of the two inputs.
Caution: the string starts from st[0] and ends at st[st.length()-1].
WANG RUI 2016.9.26
*/
# include <cstdio>
# include <iostream>

using namespace std;

int main()
{
	string st1,st2;
	cin >> st1 >> st2;
	int m = st1.length();
	int n = st2.length();
	int f[m+1][n+1];
	memset(f, 0, sizeof(f));
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (f[i-1][j] == f[i][j-1] && st1[i-1] == st2[j-1])
				f[i][j] = f[i-1][j]+1;
			else f[i][j]=
						f[i-1][j] > f[i][j-1] ? f[i-1][j] : f[i][j-1];
		}
	}
	cout << "The length of the longest common sequence is : " << f[m][n] << endl;
	return 0;
}