#include <cstdio>
#include <iostream>

using namespace std;

int *name;
char **namelib;
int*lenlib;
int *Count;
static int number_of_names = 0; // number of names in the namelib

#define M 40009

bool compare(char* a, int lena, char* b, int lenb) // see if a == b
{
	if (lena != lenb) return false;
	int i = 0;
	while (i < lena)
	{
		if (a[i] != b[i]) return false;
		i++;
	}
	return true;
}

int exist(int length, char* ch, int &code) // needs to change code so as to insert a new
{
	while (name[code] != 0 && !compare(ch, length, namelib[name[code]], lenlib[name[code]]))
		code = (code + 1) % M;
	if (name[code] == 0) return 0; // if meets a space, the name is new
	else return name[code]; // has encountered an existing name, returns its place in namelib
}

int insert(char *ch, int length)
{
	++number_of_names;
	namelib[number_of_names] = new char[length]; // add a new name to library
	for (int i = 0; i < length; i++)
		namelib[number_of_names][i] = ch[i];
	lenlib[number_of_names] = length;
	Count[number_of_names] = 1;
	return number_of_names;
}

void encode(char *ch, int length)
{
	int code = 0;
	for (int k = 0; k < length; k++)
	{
		code = (code * 11 + (int)(ch[k] - 'a' + 1)) % M;
	}
	int check = exist(length, ch, code); // find the location of this name, ch
	if (check) Count[check]++; // name already exists, simply add the number
	// code already changed to a vacant place by the function exists(), if ch is a new name
	else name[code] = insert(ch, length); // add a new name to the name library
}

void findmax()
{
	int max = 0, maxi;
	for (int i = 1; i <= number_of_names; i++) // Note: index of namelib ranges from 1 to 10000
	{
		if (Count[i] > max)
		{
			max = Count[i];
			maxi = i;
		}
	}
	for (int i = 0; i < lenlib[maxi]; i++)
		printf("%c", namelib[maxi][i]);
	printf(" %d\n", Count[maxi]);
}

int main()
{
	int n;
	scanf("%d ", &n);
	name = new int[M + 1]();  // hash table of name (place of name in the lib) & set all to 0
	char* ch = new char[9];    // temporary string to store the current input name
	namelib = new char*[10001]; // name library
	lenlib = new int[10001];  // length of related name in namelib
	Count = new int[10001]; // the time of names in namelib appearing
	for (int i = 0; i < n; i++)
	{
		scanf("%s", ch);
		int j = 0;
		while (ch[j++] != '\0');
		j--; // j is the length of the name
		encode(ch, j);
	}
	findmax();
	return 0;
}