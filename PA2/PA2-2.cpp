#include<stdio.h>

using namespace std;

int a[2000][2000];
int main()
{
	setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
    long long num = 0;
	long long sum = 0;
    int n, m, nmax, mmax;
	int* s;
    scanf("%d %d", &n, &m);
    scanf("%d %d", &nmax, &mmax);
    s = new int[n];
    int max = 1;
	int min = 1;
	s[0] = -1;
    //读入0/1矩阵
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    //矩阵预处理
    for(int i = 1; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(a[i-1][j] && a[i][j])
				a[i][j] += a[i-1][j];
        }
    }
    //遍历矩阵元素
    for(int i = m - 1; i >= 0; i--)
    {
        for(int j = 0; j < n; j++)
        {
            while((max != min) && (a[i][s[max - 1]] > a[i][j]))
            {
                int r = s[max - 1]; max--;
                num -= (a[i][r] < mmax? a[i][r] : mmax)*(r - s[max-1]);
            }

            s[max] = j;
			num += (a[i][s[max]] < mmax? a[i][s[max]] : mmax)*(j - s[max - 1]);
			max++;

			if(j + 1 > nmax)
			{
				num -= a[i][s[min]];
				if (s[min] == j - nmax) min++;
			}
			
            sum += num;
        }
		max = 1;
		min = 1;
		num = 0;
    }
	
    printf("%lld", sum%10007);
	
    return 0;
}