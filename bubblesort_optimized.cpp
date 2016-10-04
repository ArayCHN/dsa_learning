/*
This is an optimized version of bubble sort. In case of a random sequence, the algorithm performs roughly
twice better than normal ones. In case of designed sequence with a large portion of latter half in good
order, this algorithm runs way faster than normal ones. --> see in the case with input bubblesort_optimized.in.
Output: the first 20 numbers of the sorted sequence.
WANG RUI 2016.10.4
*/
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

void swap(int &a, int & b)
{
	int c = a; a = b; b = c;
}

int main()
{
	ifstream file("bubblesort_optimized.in");
	int n;
	file >> n ;
	int a[100000];
	for (int i = 0; i < n; i++)
		file >> a[i];
	int last = n-1;
	int i = n-1;
	while (i > 0)
	{
		int late = 0;
		for (int j = 0; j < i-1; j++)
		{
			if (a[j] > a[j+1]) 
				{
					swap(a[j], a[j+1]);
					late = j;
				}
		}
		i = late;
	}
	cout << a[0];
	for (int i = 1; i < 20; i++)// to see if the program runs correctly.
		cout << ' ' << a[i];
	cout << endl;
}