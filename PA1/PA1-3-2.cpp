#include <stdio.h>
#include <iostream>
using namespace std;
typedef int Rank;
typedef struct ListNode {
	int data; struct ListNode *pred; struct ListNode *succ;
	ListNode( int e=0,struct ListNode *p = NULL, struct ListNode *s = NULL)
		: data(e), pred(p), succ(s) {};
}ListNode,*pListNode;

class List {
	 
public:
	int _size;
	void visit(pListNode &p);
	void init();
	pListNode header; pListNode trailer;
};

pListNode insertAsPred(pListNode &p,int const& e ,List &q){
	pListNode x = new ListNode(e, p->pred, p);
	p->pred->succ = x; p->pred = x;
	q._size++;
	return x;
}

pListNode insertAsSucc (pListNode &p,int const& e,List &q ) {
   pListNode x = new ListNode ( e, p, p->succ ); 
   p->succ->pred = x; p->succ = x; 
   q._size++;
   return x; 
}

void List::visit(pListNode &p)
{
	cout<<p->data;
}
void List::init()
{
	header = new ListNode;
	trailer = new ListNode;
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0;
}



int main(){
	int n, m;
	int temp;
	pListNode pre;
	cin>>n>>m;
	List l;
	l.init();
	for(int i = 0; i < n; i++)
	{
		scanf("%d",&temp);
		if(i != 0)
		{
			for(int j = 1; (j < m)||(pre->succ == NULL); j++)
			{
				if(pre->succ != NULL)
					pre = pre->succ;
				else
				{
					pre = l.header->succ;
					j--;
				}

			}
			pre = insertAsSucc(pre,temp,l);
		}
		else
			pre = insertAsSucc(l.header,temp,l);
	}
	for(int i = 0; (i < n)||(pre->pred == NULL); i++)
	{
		if(pre->pred != NULL)
		{
			l.visit(pre);
			if(i != n-1) cout<<' ';
			pre = pre->pred;
		}

		else
		{
			pre = l.trailer->pred;
			l.visit(pre);
			if(i != n-1) cout<<' ';
			pre = pre->pred;
		}
	}

	return 0;
	
}