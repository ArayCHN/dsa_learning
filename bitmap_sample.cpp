#include <cstdio>
#include <iostream>
using namespace std;

int t[1000000], f[1000000];

class bitmap{
private:
	char* a;
	int top, n;
public:
	bitmap(int n = 8): top(0), n(n) { //QUESTION: if no n, is n == 8?
	    a = new char[ (n+7)/8 ]; 
	    //memset(a, 0, sizeof(a));
	} //***The best way to describe ceiling(n/8), even if n%8 == 0
	bitmap( bitmap &x ): top(x.top), n(x.n) {
		a = new char[ (n+7)/8 ]; //deep copy
		for (int i = 0; i < x.top; i++)
			a[i] = x.a[i];
	}
	void add(int x);
	//void rm(int x);
	void clear(int x);
	bool check(int x);
};
void bitmap::add(int x) {
	//a[x >> 3] |= 8 >> (x & 7);
	top++;
	t[top] = x;
	f[x] = top;
}
void bitmap::clear(int x) {
	t[f[x]] = t[top];
	f[x] = f[top];
	top --;
}
bool bitmap::check(int x) {
	return (f[x] <= top) && (x == t[f[x]]);
}

int main(){
	int n,num;
	cin >> n;
	char op;
	bitmap b;
	for (int i = 0; i < n; i++) {
		cin >> op >> num;
		if (op == 'a') b.add(num);
		else if (op == 'c') b.clear(num);
		else cout << b.check(num) << endl;
	}
	return 0;
}