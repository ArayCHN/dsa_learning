#include <cstdio>
#include <iostream>

using namespace std;

class Stack
{
public:
	Stack(int n);
	~Stack();
	bool empty();
	void push(int);
	int pop();
	int top();
private:
	int length;
	int *s;
};

Stack::Stack(int n) : length(0)
{
	s = new int [n];
}

Stack::~Stack()
{
	delete[] s;
}

bool Stack::empty()
{
	return length == 0;
}

void Stack::push(int value)
{
	s[length++] = value;
}

int Stack::pop()
{
	return s[--length];
}

int Stack::top()
{
	return s[length - 1]; // index ranges from 0 to length - 1
}

int larger(int a, int b);

class Queap
{
public:
	Queap(int n);
	~Queap();
	void enqueap(int);
	int dequeap();
	int max();
	int mv();
private:
	Stack sl, sr, ml, mr; // stack_left , stack_right, max_left, max_right
};

Queap::Queap(int n) : sl(n), sr(n), ml(n), mr(n)
{
	// ml, mr are the shadow stacks which
	// store the largest number before a member in stack_l, stack_r
}

Queap::~Queap()
{
}

void Queap::enqueap(int value)
{
	sr.push(value);
	if (mr.empty())
		mr.push(value);
	else
	    mr.push(larger(value, mr.top())); // compare the current largest and the new-coming num
}

int Queap::dequeap()
{
	if (sl.empty()) mv();
	ml.pop();
	return sl.pop();
}

int Queap::max()
{
	if (sl.empty())
	{
		return mv();                        // transport the right stack to the left and return the largest
	}
	else if (sr.empty())
	{
		return ml.top();                    // return left largest if nothing's in the right stack
	}
	else return larger(ml.top(), mr.top()); // the largest num must be either in the left or the right stack
}

int Queap::mv()
{
	sl.push(sr.pop());
	ml.push(sl.top());
	mr.pop();                               // set the first ele to be moved as the curr largest in the left
	while (!sr.empty())
	{
		sl.push(sr.top());
		ml.push(larger(ml.top(), sr.pop()));
		mr.pop();                           // the right max stack is of no use in mv, pop directly
	}
	return ml.top();                        // in fun max(), ml.top() will be of use (as the maximum)
}

int larger(int a, int b)
{
	if (a > b) return a;
	return b;
}

int main()
{
	int n, x;
	scanf("%d", &n);
	Queap q(n);
	for (int i = 0; i < n; i++){
		char c;
		scanf(" %c", &c);
		switch (c){
			case 'E': scanf("%d", &x);
			          q.enqueap(x);
			          break;
			case 'D': printf("%d\n", q.dequeap());
			          break;
			case 'M': printf("%d\n", q.max());
			          break;
		}
	}
	return 0;
}