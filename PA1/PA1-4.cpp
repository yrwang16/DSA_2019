
#include <stdio.h>
using namespace std;

int px[200000],py[200000],qx[200000],qy[200000];
int n, m;

bool cross(int pxx,int pyy,int qxx, int qyy)
{
	long r1 = long(pxx)*long(qyy);
	long r2 = long(qxx - pxx)*long(-pyy);
	if (r1 >= r2)
		return true;
	else
		return false;

}

int search(int qxx, int qyy)
{
	int lo = -1, hi = n-1;
	if(cross(px[hi],py[hi],qxx,qyy) == 0)
	{
		while(lo < hi-1)
		{
			if(cross(px[(hi+lo)/2],py[(hi+lo)/2],qxx,qyy))
				lo = (hi+lo)/2;
			else
				hi = (hi+lo)/2;
		}
	    return lo+1;
	}
	else
		return hi+1;
	
}

int main()
{
	setvbuf(stdin,new char[1<<20],_IOFBF,1<<20);
	setvbuf(stdout,new char[1<<20],_IOFBF,1<<20);
	scanf("%d %d",&n,&m);
	for(int i = 0; i < n; i++)
	{
		scanf("%d %d",&px[i],&py[i]);
	}
	for(int i = 0; i < m; i++)
	{
		scanf("%d %d",&qx[i],&qy[i]);
	}
	for(int i = 0; i < m; i++)
	{
		printf("%d\n",search(qx[i],qy[i]));
	}
	return 0;
}
