#include<stdio.h>

using namespace std;

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	int* a = new int [n];
	int* s = new int [m];
	char* op = new char [2*n];
	int* opnum = new int [2*n];
	int top = 1;
	int size = 0;
	int res = n;
	int i = 0;
	for(int j = 0; j < n; j++)
	{
		scanf("%d", &a[j]);
	}

	while(res > 0)
	{
		if(a[n-res] == top)
		{
			op[i] = 'P'; opnum[i] = top;
			top++; i++; res--;
		}
		else if((size > 0)&&(s[size - 1] == top))
		{
			op[i] = 'O'; opnum[i] = top;
			top++; size--; i++;
		}
		else if(size < m)
		{
			s[size] = a[n-res];
			op[i] = 'I';opnum[i] = a[n-res];
			size++; i++; res--;
		}
		else
			break;
	}

	if((size <= m)&&(res == 0))
	{
		while(size > 0)
		{
			if(s[size - 1] == top)
			{
				op[i] = 'O'; opnum[i] = s[size - 1];
				size--; i++; top++;
			}
			else
				break;
		}
		if(size == 0)
		{
			for(int j = 0; j < i; j++)
			{
				printf("%d %c\n",opnum[j],op[j]);
			}
		}
		else
		{
			printf("No");
		}
	}
	else
	{
		printf("No");
	}
	
	return 0;
}
