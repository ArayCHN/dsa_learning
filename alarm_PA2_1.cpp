#include <cstdio>

using namespace std;

bool below(unsigned long long x, unsigned long long y, unsigned long long a, unsigned long long b)
{
  if (x > a || y > b) return false; // pre-check to prevent numbers smaller than 0.
  return b * (a - x) > a * y;
  // BAD VERSION: if (b * x + a * y < a * b) return true; else return false;
}

int binsearch(unsigned int x, unsigned int y, unsigned int* a, unsigned int* b, int n)
{
  int l = 0, r = n, mid;
  while (l < r - 1)                       // if l == r-1, will fall into endless loop
  {
    mid = (l + r) / 2; 
    below(x, y, a[mid], b[mid]) ?         // to check if the dot is below a line defined by a[i], b[i]
    r = mid : l = mid;                    // if yes, search further in the left half. vice versa
  }
  return below(x, y, a[l], b[l]) ? l : r; // deal with the case of (x, y) belonging to area 0
}

int main()
{
  int m, n;
  scanf("%d%d", &n, &m);
  unsigned int *a = new unsigned int [n];     // applies the equation b x + a y = ab, where 
  unsigned int *b = new unsigned int [n];     // a, b are x, y intercepts
  for (int i = 0; i < n; i++)                 // initialize alarms
    scanf("%d%d", &a[i], &b[i]);
  unsigned int x, y;
  for (int i = 0; i < m; i++)
  {
    scanf("%d%d", &x, &y);
    printf("%d\n", binsearch(x, y, a, b, n)); // uses binary search to locate the area
  }
  return 0;
} 