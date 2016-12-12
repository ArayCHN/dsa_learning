#include <cstdio>

using namespace std;

class stack{
	int *a;
	int sz;     // the size of a
	int number; // the total number of members currently in the stack
public:
	stack(int n);
	~stack();
	int pop();
	int get();
	int push(int);
	int num();  // returns the current length of the stack
};

stack::stack(int n) : number(0), sz(n) {
	a = new int [n];
}

stack::~stack() { delete[] a; } 

int stack::pop(){
	return (a[--number]);
}

int stack::get(){
	if (number > 0)
		return (a[number - 1]);
	else
		return 0; // when there's no element in the stack
}

int stack::push(int x){
	a[number++] = x;
	return x;
}

int stack::num(){
	return number - 1;
}

static int tot; // the next number to push into the stack

bool check(stack &s, int x, int const &m){
	if ((x <= tot) && s.get() != x) return false; // if x is in the stack but not on top, must be false
	while (s.get() != x) s.push(++tot);           // push into the stack until x is in and can be popped out
	if ((s.num() > m)) return false; 
	s.pop();
	return true;
}

int main(){

	int n, m, x;
	bool if_possible = true;              // changes to "false" if the sequence is impossible
	scanf("%d%d", &n, &m);
	stack s(n);

	for (int i = 0; i < n; i++){
		scanf("%d", &x);
		if (!check(s, x, m)) {            // simulates the operation of a stack
			printf("No\n");               // once it is found that an output is invalid,
			if_possible = false;
			break;                        // there's no need to read in any more
		}
	}

	if (if_possible) printf("Yes\n");

	return 0;
}