#include<iostream>
#include<string>

using namespace std;
class node
{
public:
	string name;
	int n;
	node();
};
node::node()
{
	n = 0;
}


unsigned int hashfun(string name)
{
	unsigned int h = 0;
	for(int n = name.length(), i = 0; i < n; i++)
	{
		h = (h << 5)|(h >> 27);
		h += (int)name[i];
	}
	return h;
}
bool insert(node* table, int index, string StudentName)
{
	if(table[index].n == 0) 
	{
		table[index].name = StudentName;
		table[index].n++;
		return true;
	}
	else if(table[index].name == StudentName)
	{
		table[index].n++;
		return true;
	}
	else
	{
		int i = 1;
		while(!insert(table, index + i*i, StudentName))
		{
			i++;
		}

	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	node* hashtable = new node[20003];
	int n;
	cin>>n;
	string StudentName;
	unsigned int index;
	for(int i = 0; i < n; i++)
	{
		cin>>StudentName;
		index = hashfun(StudentName)%20003;
		insert(hashtable, index, StudentName);
	}
	int max = 0;
	string one;
	for(int i = 0; i < 20003; i++)
	{
		if(hashtable[i].n > max) 
		{
			max = hashtable[i].n;
			one = hashtable[i].name;
		}
	}
	cout<<one<<" "<<max<<endl;
	
	return 0;
}
