#include <cstdio>
#include <iostream>
#include "temperature.h"

using namespace std;

struct dot
{
  int x, y, temp;
} *dots; // in order to use sort(), store all related info in a struct

void sort(int l, int r) // qsort function
{
    if (l < r)
    {      
      int i = l, j = r;
      dot tmp = dots[l];
        while (i < j)
        {
            while (i < j && dots[j].x >= tmp.x) j--; 
            if (i < j) dots[i++] = dots[j];        
            while (i < j && dots[i].x < tmp.x) i++; 
            if (i < j) dots[j--] = dots[i];
        }
        dots[i] = tmp;
        sort(l, i - 1);
        sort(i + 1, r);
    }
}

struct node
{
  int *lpointer, *rpointer, *num; // *num: total number of stations;
                                  //lpointer, rpointer: use in fractional cascading
  long long *sum;
  dot *stations;
  node *lc, *rc; // leftchild rchild
  int size, lx, rx; // left/right x boundary [lx, rx)
  node(dot d, int i) : lpointer(NULL), rpointer(NULL), size(1), lx(i), rx(i + 1) // construct a leaf
  {
    stations = new dot(d);
    sum = new long long[2];
    sum[0] = 0;
    sum[1] = d.temp;
  }
  node(int n, int l, int r) : size(n), lx(l), rx(r)
  {
    stations = new dot[n];
    sum = new long long[n + 1];
    lpointer = new int[n + 1];
    rpointer = new int[n + 1];
  }
};

node* merge(node* a, node* b, int l, int r)
{
  node* c = new node(a->size + b->size, l, r);
  int firstia = 0, firstib = 0; // the smallest index of a series of repetitive a/b->stations[i].y
  for (int i = 0, ia = 0, ib = 0; i < c->size; i++) // merge sort
  {
    if (ib == b->size || (ia < a->size && a->stations[ia].y <= b->stations[ib].y)) // merge a to c
    {
      c->stations[i] = a->stations[ia];
      if (!(ia && a->stations[ia].y == a->stations[ia - 1].y)) // if this is not a repetitive point
        firstia = ia; // then update the latest y
      // lpointer and rpointer are for fractional cascading, where the index of the next element in child is recorded
      c->lpointer[i] = firstia; // always store the position of the 1st element in a repetitive series
      c->stations[i] = a->stations[ia];
      if (c->stations[i].y == b->stations[firstib].y) c->rpointer[i] = firstib;
      else c->rpointer[i] = ib;
      ia++;
    } 
    else // merge b to c
    {
      c->stations[i] = b->stations[ib];
      if (!(ib && b->stations[ib].y == b->stations[ib - 1].y))
        firstib = ib;
      c->rpointer[i] = firstib;
      c->stations[i] = b->stations[ib];
      if (c->stations[i].y == a->stations[firstia].y) c->lpointer[i] = firstia;
      else c->lpointer[i] = ia;
      ib++;
    }
    if (i)
      c->sum[i] = c->sum[i - 1] + c->stations[i - 1].temp; // sum[i] = sum(0..i-1)
    else
      c->sum[i] = 0;
  }
  c->sum[c->size] = c->sum[c->size - 1] + c->stations[c->size - 1].temp;
  c->lpointer[c->size] = a->size; c->rpointer[c->size] = b->size;
  c->lc = a; c->rc = b; // set a,b as children
  return c;
}

node* build_rangetree(int l, int r)
{
  if (r - l == 1)
  {
    return (new node(dots[l], l)); // treat stations with the same x as different leaves
  }
  int mid = (l + r) >> 1;
  return merge(build_rangetree(l, mid), build_rangetree(mid, r), l, r);
}

struct ave // used to store the total temperature and the number of stations inside, as return value of a function
{
  long long sumtemp;
  int num;
  ave(long long s, int n) : sumtemp(s), num(n) {}
  ave operator+ (ave &b);
};
ave ave::operator+ (ave &b)
{
  return ave(sumtemp + b.sumtemp, num + b.num);
}

ave find(node* curr, int x1, int x2, int lo, int hi) // x:find[x1, x2) in [curr->lx, curr->rx)  y:[lo, hi)
{
  // lo - hi equals the total number of stations
  if (x1 == x2) return ave(0, 0); // if there's no element in between, stop. otherwise will go to a NULL child!
  if (x1 <= curr->lx && curr->rx <= x2) return ave(curr->sum[hi] - curr->sum[lo], hi - lo);
  int mid = curr->lc->rx;
  if (x1 < mid && mid < x2) 
  { 
    ave ans1 = find(curr->lc, x1, mid, curr->lpointer[lo], curr->lpointer[hi]); // find in left child
    ave ans2 = find(curr->rc, mid, x2, curr->rpointer[lo], curr->rpointer[hi]); // find in right child
    return ans1 + ans2;
  }
  if (x2 <= mid)
    return find(curr->lc, x1, x2, curr->lpointer[lo], curr->lpointer[hi]);
  if (mid <= x1)
    return find(curr->rc, x1, x2, curr->rpointer[lo], curr->rpointer[hi]);
}

int binsearchy(node* root, int lo, int hi, int goal)
{
  if (lo == hi - 1) return hi; // if goal doesn't exist, choose the 1st element larger than it
  int mid = (lo + hi) >> 1;
  if (goal < root->stations[mid].y) return binsearchy(root, lo, mid, goal);
  else if (root->stations[mid].y < goal) return binsearchy(root, mid, hi, goal);
  else if (root->stations[mid - 1].y == goal) return binsearchy(root, lo, mid, goal); // try to find the left-most
  else return mid; // already the left-most
}

int binsearchx(int lo, int hi, int goal)
{
  if (lo == hi - 1) return hi;
  int mid  = (hi + lo) >> 1;
  if (goal < dots[mid].x) return binsearchx(lo, mid, goal);
  else if (dots[mid].x < goal) return binsearchx(mid, hi, goal);
  else if (dots[mid - 1].x == goal) return binsearchx(lo, mid, goal);
  else return mid;
}

int main()
{
  int n = GetNumOfStation();
  dots = new dot[n]; // dots[] is a library of all stations with info x, y, temp
  for (int i = 0; i < n; i++)
  {
    GetStationInfo(i, &dots[i].x, &dots[i].y, &dots[i].temp);
  }
  sort(0, n - 1); // sort dots[] within range [0, n) according to x
  node *root = build_rangetree(0, n); // build the range tree of range [0, n)

  int x1, x2, y1, y2;
  while (GetQuery(&x1, &y1, &x2, &y2))
  {
    int lo = (y1 <= root->stations[0].y ? 0 : binsearchy(root, 0, n, y1));
    while (lo && root->stations[lo - 1].y == root->stations[lo].y) lo--; // go to the left-most position
    int hi = (y2 < root->stations[0].y ? 0 : binsearchy(root, 0, n, y2 + 1));
    while (hi && root->stations[hi - 1].y == root->stations[hi].y) hi--; // [lo, hi) is the range on y axis
    if (y2 > root->stations[n - 1].y) hi = n;

    x1 = x1 <= dots[0].x ? 0 : binsearchx(0, n, x1);
    while (x1 && dots[x1 - 1].x == dots[x1].x) x1--;
    x2 = x2 < dots[0].x ? 0 : binsearchx(0, n, x2 + 1);
    while (x2 && dots[x2 - 1].x == dots[x2].x) x2--; // [x1, x2) is the range on x axis

    ave result = find(root, x1, x2, lo, hi); // NOTE: here x, y all represent index in dot[], not value!
    int tempbar = result.num == 0 ? 0 : (int) (result.sumtemp / (long long)result.num);
    Response(tempbar); // print the average temperature
  }
  return 0;
}