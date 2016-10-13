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
	//ele *p = start;
	int i = 1;
	while (i < num_people)
	{   
		if (p != header && p != trailer) i++;
		//cout<<i<<" "<<endl;
		p = p -> succ;
	}
	while (p == header || p == trailer) p = p -> succ;

	ele *q = new ele;
	q -> id = id;
	q -> succ = p -> succ;
	q -> succ -> pre = q;
	q -> pre = p;
	p -> succ = q;
	//delete header;
	//cout<<endl;
	p = header -> succ;
	/*cout<<"OK"<<endl;
	for (int i = 0; i < 10; i++)
		{cout<< p->id<<" "; p = p->succ; if (p == trailer) break;}
	cout<<endl;*/
	return q;
}

int main()
{
	int m,n;
	scanf("%d%d", &n, &m);
	int id, tot = 0, num_people;

	scanf("%d", &id);
	ele *q = new ele;
	q -> id = id;
	header -> succ = q; q -> pre = header;
	q -> succ = trailer; trailer -> pre = q;
    trailer -> succ = header; header -> pre = trailer;
    ele *last = q;
    tot ++;
    //cout<<"OK"<<endl;
    int i;
	for (i = 1; i < n; i++)
	{
		scanf("%d", &id);
		//tot != 0 ? num_people = m % tot : num_people = 0;
		//cout<<num_people<<endl;
		last = insert(last, m, id);
		tot ++;
	}
///////OK///////
	//cout<<tot<<endl;
	i = 0;
	while (i < tot)
	{   if (last != header && last != trailer)
		   { 
		   	if (i < tot-1)
		   	 printf("%d ", last -> id); 
		   	else
		   	 printf("%d\n", last -> id);
		   	i++; 
		   }
		last = last -> pre;
	}
	return 0;
}