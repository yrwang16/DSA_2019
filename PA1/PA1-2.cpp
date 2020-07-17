#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
using namespace std;

class Bitmap {
private:
	int* F; int N;
	int* T; int top;

public:
	Bitmap(int n)
	{ N = n; F = new int[N]; T = new int[N]; top = 0;}
	~Bitmap() {
		delete [] F;
		delete [] T;
	}

	inline void reset(){ top = 0;}
	inline void set(int k){
		if(!test(k)){
			T[top] = k; F[k] = top++;
		}
	}
	inline void clear(int k){
		if(test(k)){
			if(--top){
				F[T[top]] = F[k]; T[F[k]] = T[top];
			}

		}
	}
	inline bool test(int k)
	{
		return (-1 < F[k] )&&(F[k] < top)&&(k == T[F[k]]);
	}
	inline int number()
	{
		return top;
	}

};



int main(){
	int* S;
	int n, m;
	char c;
	int a, code, num = 0;
	long long int sum = 0;
	scanf("%d %d",&n,&m);
	S = new int [n];
	Bitmap B(n);
	for ( int i = 0; i < m; i++){
		scanf("%s",&c);
		if (c == 'I'){
			scanf("%d",&a);
			scanf("%d",&code);
			B.set(a);
			S[a] = code;
		}
		else if (c == 'O'){
			scanf("%d",&a);
			B.clear(a);
		}
		else if(c == 'C'){
			B.reset();
		}
		else if(c == 'N'){
			num = B.number();
			sum += num;
		}
		else
		{
			scanf("%d",&a);
			if(B.test(a))
				code = S[a];
			else
				code = -1;
			sum += code;
		}
	}
	printf("%lld",sum);
	return 0;
	
}
