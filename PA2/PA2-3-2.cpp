#include<stdio.h>
using namespace std;
int find(int path_l, int *fc, int *ns, int *pa);//����·�����Һ���
int path[1000000];//·�����飬���� <= cost <= 10^6 
int main()
{
	//���ٶ�д������
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
    int n, m, ch_num;
    scanf("%d %d", &n, &m);
	/*
	  ����
	  pa����Ϊ���ڵ�id
	  fcΪ����id
	  nsΪ��һ���ֵ�id
	  psΪ��һ���ֵ�id
	  sΪ��α���ʱ�ĸ���ջ
	*/
    int* pa = new int[n+1];
    int* fc = new int[n+1];
    int* ns = new int[n+1];
    int* s = new int[n+1];
    int* ps = new int[n+1];
    int l = 0, order = 0;
    int temp1, temp2, temp;
	//�������ṹ
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &ch_num);
        if(ch_num == 0)
        {
            fc[i] = -1;
        }
        else
        {
            scanf("%d", &temp1);
            fc[i] = temp1;
            pa[temp1] = i;
            ps[temp1] = -1;
            ch_num--;
            while(ch_num)
            {
                scanf("%d", &temp2);
                pa[temp2] = i;
                ps[temp2] = temp1;
                ns[temp1] = temp2;
                temp1 = temp2;
                ch_num--;
            }
            ns[temp1] = -1;
        }
    }
	//�����ƶ�ģ��
    for(int i = 0; i < m; i++)
    {
        scanf("%d", &l);//����·������
        for(int j = 0; j < l; j++)//����·��
        {
            scanf("%d", &path[j]);
        }
        temp1 = find(l, fc, ns, pa);//�ҵ�Դ����
        //���Դ�������Ϊ���ӣ�ֱ�Ӹı��丸�ڵ��fc����һ���ֵܵ�ps�����������һ���ֵܵĻ���
		if(fc[pa[temp1]] == temp1)
        {
            fc[pa[temp1]] = ns[temp1];//�ı���̹�ϵ
            if(ns[temp1] != -1) ps[ns[temp1]] = -1;//�ж��ֵ��Ƿ����
        }
		//��Ϊ�������ҵ���һ���ֵܣ��ı���ns����һ���ֵܵ�ps�����������һ���ֵܵĻ���
        else
        {
            temp = ps[temp1];
            ns[temp] = ns[temp1];
            if(ns[temp1] != -1) ps[ns[temp1]] = temp;
        }

        scanf("%d", &l);//����·������
        for(int j = 0; j < l; j++)//����·��
        {
            scanf("%d", &path[j]);
        }
        temp2 = find(l, fc, ns, pa);//�ҵ�����ڵ�

        scanf("%d", &order);//�������˳��

        pa[temp1] = temp2;//������λ�ü�ΪԴ�����ĸ��ڵ�
        if(order == 0)//�����Ϊ���Ӳ���
        {
            ns[temp1] = fc[temp2];//�ı�Դ����nsΪ����ڵ㵱ǰ����
            ps[temp1] = -1;//psΪ�գ�ȡ-1
            if(fc[temp2] != -1) ps[fc[temp2]] = temp1;//�����ǰ���Ӵ��ڵĻ�������ps��ΪԴ����
            fc[temp2] = temp1;//��������ݱ��ΪԴ����
        }
        else//�������Ϊ���Ӳ���
        {
            temp = fc[temp2];//�ҵ�����
            while(order > 1)//�ҵ�����λ�õ�ǰһ���ڵ�
            {
                if(ns[temp] != -1) temp = ns[temp];
                order--;
            }
			//�ı���Ӧ��ϵ��ԭ��ͬ��
            ns[temp1] = ns[temp];
            if(ns[temp] != -1) ps[ns[temp]]=temp1;
            ns[temp] = temp1;
            ps[temp1] = temp;
        }
    }
	//ͨ������ջs���в�α���
    s[0] = 1;
    int top = 0, bot = 1;
    while(top != bot)
    {
        int x = s[top];
        printf("%d\n", x);
        top++;
        if(fc[x] != -1)
        {
            s[bot] = fc[x];
            bot++;
            while(ns[s[bot-1]] != -1)
            {
                s[bot] = ns[s[bot-1]];
                bot++;
            }
        }
    }
    return 0;
}
//find��������
int find(int path_l, int *fc, int *ns, int *pa)
{
    int temp = 1;//�Ӹ��ڵ㿪ʼѰ��
    int order = 0;//��ǰ·��λ��
    int error = 0;//�Ƿ�Ƿ�
    while(path_l)
    {
        if(fc[temp] != -1) temp = fc[temp];//���޳��ӣ��Ƿ���ֱ��break�����ص�ǰ�ڵ�
        else break;
        while(path[order])
        {
            if(ns[temp] != -1) temp = ns[temp];
            else//�������ĺ���λ�ó������Ӹ������Ƿ�
            {
                error = 1;
                break;
            }
            path[order]--;
        }
        if(error)
		{
			temp = pa[temp];//�ɺ��Ӹ��������ķǷ����ʱ��temp�Ѿ�����ֵΪ���ӣ���Ӧ�����丸�ڵ�
			break;
		}
        path_l--;
        order++;
    }
    return temp;//�������һ���Ϸ��ڵ�
}


