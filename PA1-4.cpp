/*
WR 2016.10.13
*/
#include <cstdio>
#include <iostream>
using namespace std;

struct ele{
	int id;
	ele *pre, *succ;
};

ele* header = new ele;
ele* trailer = new ele;

ele* insert(ele* p, int num_people, int id)
{
	int i = 1;
	while (i < num_people)
	{   
		if (p != header && p != trailer) i++;
		p = p -> succ;
	}
	while (p == header || p == trailer) p = p -> succ; // in case p points to header or trailer

	ele *q = new ele;
	q -> id = id;
	q -> succ = p -> succ;
	q -> succ -> pre = q;
	q -> pre = p;
	p -> succ = q;

	return q;
}

int main()
{
	int m,n;
	scanf("%d%d", &n, &m);
	int id, tot = 0, num_people;
    /* Below: deal with the first candidate */
	scanf("%d", &id);
	ele *q = new ele;
	q -> id = id;
	header -> succ = q; q -> pre = header;
	q -> succ = trailer; trailer -> pre = q;
    trailer -> succ = header; header -> pre = trailer;
    ele *last = q;
    tot ++;
    /* ABOVE: deal with the first candidate */

    /* BELOW: deal with all the new comers */
    int i;
	for (i = 1; i < n; i++)
	{
		scanf("%d", &id);
		last = insert(last, m % (m + tot), id);
		tot ++;
	}

	i = 0;
	while (i < tot)
	{   if (last != header && last != trailer) //skips the header and trailer
		   { 
		   	if (i < tot-1)
		   	 printf("%d ", last -> id); 
		   	else
		   	 printf("%d\n", last -> id);
		   	i++; 
		   }
		last = last -> pre; //go next (inverse order) for any element, header & trailer included
	}
	return 0;
}