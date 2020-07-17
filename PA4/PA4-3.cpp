#include<iostream>
#include<string>
using namespace std;

class node
{
public:
	string str;
	int n;
	node();
};
node::node()
{
	str = "";
	n = 0;
}
unsigned int hashfun(string str)
{
	unsigned int h = 0;
	unsigned int sum = 0;
	for(int n = str.length(), i = 0; i < n; i++)
	{
		sum += (int) str[i];
	}

	while(sum != 0)
	{
		h = (h << 5)|(h >> 27);
		h += sum%10;
		sum /= 10;
	}
	return h;
}
node hashtable[1000007];
int *buildNext(string s)
{
	int m = s.length(), j = 0;
	int *N = new int [m];
	int t = -1;
	N[0] = -1;
	while(j < m-1)
	{
		if(t < 0 || s[j] == s[t])
		{
			j++;
			t++;
			N[j] = (s[j] != s[t])? t : N[t];
		}
		else
			t = N[t];

	}
	return N;
}

bool match(string s1, string s2)
{
	int *next = buildNext(s2);
	int n = (int) s1.length(), i = 0;
	int m = (int) s2.length(), j = 0;
	while(j < m && i < n)
	{
		if(0 > j || s2[j] == s1[i])
		{
			i++; j++;
		}
		else
			j = next[j];
	}
	delete [] next;
	if(j >= m)
		return true;
	else
		return false;
}

int insert(unsigned int index, string s, int k)
{
	if(hashtable[index].n == 0)
	{
		hashtable[index].str += s;
		hashtable[index].str += s;
		hashtable[index].n = k;
		return 0;
	}
	else if(match(hashtable[index].str, s))
	{
		return hashtable[index].n;
	}
	else
	{
		return insert((index + 1)%1000007, s, k);
	}

}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int m, n;
	cin>>n>>m;
	string str;
	unsigned int index;
	int *k = new int[m];
	for(int i = 0; i < m; i++)
	{
		cin>>str;
		index = hashfun(str)%1000007;
		k[i] = insert(index, str, i+1);
	}
	for(int i = 0; i < m; i++)
	{
		cout<<k[i]<<endl;
	}


	return 0;
}
