/*
A mimic version of vector in STL lib.
WANG RUI 2016.10.4

***TO BE ADDED:
1.search in a sorted vector
2.sort
3.unify in a sorted vector
*/
#include <cstdio>
#include <iostream>

using namespace std;

#define DEFAULT_SIZE 100

///////////////BELOW VECTOR/////////////////
template <typename T> class vector
{
private:
	T* _elem; int _capacity, _size;
	void copyfrom(const T* a, int lo, int hi);
	void expand();
protected:
public:
	////construct and delete//////
	vector(int c = DEFAULT_SIZE);
	vector(const T* a, int lo, int hi);
	vector(vector<T> const& a, int lo, int hi);
	vector(vector<T> const& a);
	~vector() { delete [] _elem; }
	////construct and delete//////

	////member functions//////
	T get(int index) { return( _elem[index] ); }

	template <typename FUN>
	void traverse(FUN &visit);

};

template <typename T>
inline vector<T>::vector(int c) { _capacity = c; _size = 0; _elem = new T[_capacity] ; }

template <typename T>
inline vector<T>::vector(const T* a, int lo, int hi) { copyfrom(a, lo, hi); }

template <typename T>
inline vector<T>::vector(vector<T> const& a, int lo, int hi) { copyfrom(a._elem, lo, hi); }

template <typename T>
inline vector<T>::vector(vector<T> const& a) { int hi = a._size-1; copyfrom(a._elem, 0, hi); }

template <typename T>
void vector<T>:: copyfrom(const T* a, int lo, int hi)
{
	_size = hi+1-lo;
	_capacity = _size << 1;
	_elem = new  T[_capacity] ; 
 	for (int i = lo; i < hi+1; i++)
		_elem[i] = a[i];
}

template <typename T>
void vector<T>:: expand()
{
	if (_size < _capacity) return;
	_capacity <<= 1;
	T* old_elem = _elem;
	_elem = new T[_capacity];
	for (int i=0; i < _size; i++)
		_elem[i] = old_elem[i];
	delete [] old_elem;
}

template <typename T>
template <typename FUN>
void vector<T>:: traverse(FUN & visit)
{
	for (int i = 0; i < _size; i++)
	{
		visit (_elem[i]);
	}
}
////////////////ABOVE VECTOR////////////////

template <typename T>
class increase
{
public:
	virtual void operator() (T& x) { x++; }
};

int main()
{
	int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	vector<int> v(a, 0, 10);
	increase<int> fun;
	for (int i = 0; i < 10; i++)
	{
		cout << v.get(i) << endl;
	}
	v.traverse( fun );
	for (int i = 0; i < 10; i++)
	{
		cout << v.get(i) << endl;
	}
	return 0;
}