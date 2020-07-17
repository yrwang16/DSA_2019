#include<stdio.h>
using namespace std;

int  pre[1100005], post[1100005];
void reconstruction(int preleft, int postright, int length)
{
	int i;
	for(i = preleft + 2; pre[i] != post[postright - 1]; i++);
	if(length == 3)
	{
		printf("%d %d %d ", pre[preleft + 1], pre[preleft], pre[preleft + 2]);
	}
	else if(i == preleft + 2)
	{
		printf("%d %d ", pre[preleft + 1], pre[preleft]);
		reconstruction(i, postright - 1, length - 2);
	}
	else if(i == preleft + length - 1)
	{
		reconstruction(preleft + 1, postright - 2, length - 2);
		printf("%d %d ", pre[preleft], post[postright - 1]);
	}
	else
	{
		reconstruction(preleft + 1, postright - (preleft + length - i) - 1, i - preleft - 1);
		printf("%d ", pre[preleft]);
		reconstruction(i, postright - 1, preleft + length - i);
	}
}

int main()
{
	int n;
	setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
	setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
	scanf("%d", &n);
	
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &pre[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &post[i]);
	}
	reconstruction(1, n, n);
	return 0;
}

