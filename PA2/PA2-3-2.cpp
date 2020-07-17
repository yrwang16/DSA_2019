#include<stdio.h>
using namespace std;
int find(int path_l, int *fc, int *ns, int *pa);//声明路径查找函数
int path[1000000];//路径数组，长度 <= cost <= 10^6 
int main()
{
	//开辟读写缓冲区
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
    int n, m, ch_num;
    scanf("%d %d", &n, &m);
	/*
	  定义
	  pa数组为父节点id
	  fc为长子id
	  ns为下一个兄弟id
	  ps为上一个兄弟id
	  s为层次遍历时的辅助栈
	*/
    int* pa = new int[n+1];
    int* fc = new int[n+1];
    int* ns = new int[n+1];
    int* s = new int[n+1];
    int* ps = new int[n+1];
    int l = 0, order = 0;
    int temp1, temp2, temp;
	//读入树结构
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
	//子树移动模块
    for(int i = 0; i < m; i++)
    {
        scanf("%d", &l);//读入路径长度
        for(int j = 0; j < l; j++)//读入路径
        {
            scanf("%d", &path[j]);
        }
        temp1 = find(l, fc, ns, pa);//找到源子树
        //如果源子树身份为长子，直接改变其父节点的fc及下一个兄弟的ps（如果存在下一个兄弟的话）
		if(fc[pa[temp1]] == temp1)
        {
            fc[pa[temp1]] = ns[temp1];//改变代继关系
            if(ns[temp1] != -1) ps[ns[temp1]] = -1;//判断兄弟是否存在
        }
		//不为长子则找到上一个兄弟，改变其ns和下一个兄弟的ps（如果存在下一个兄弟的话）
        else
        {
            temp = ps[temp1];
            ns[temp] = ns[temp1];
            if(ns[temp1] != -1) ps[ns[temp1]] = temp;
        }

        scanf("%d", &l);//读入路径长度
        for(int j = 0; j < l; j++)//读入路径
        {
            scanf("%d", &path[j]);
        }
        temp2 = find(l, fc, ns, pa);//找到插入节点

        scanf("%d", &order);//读入插入顺序

        pa[temp1] = temp2;//将插入位置记为源子树的父节点
        if(order == 0)//如果作为长子插入
        {
            ns[temp1] = fc[temp2];//改变源子树ns为插入节点当前长子
            ps[temp1] = -1;//ps为空，取-1
            if(fc[temp2] != -1) ps[fc[temp2]] = temp1;//如果当前长子存在的话，将其ps记为源子树
            fc[temp2] = temp1;//将长子身份变更为源子树
        }
        else//如果不作为长子插入
        {
            temp = fc[temp2];//找到长子
            while(order > 1)//找到插入位置的前一个节点
            {
                if(ns[temp] != -1) temp = ns[temp];
                order--;
            }
			//改变相应关系，原理同上
            ns[temp1] = ns[temp];
            if(ns[temp] != -1) ps[ns[temp]]=temp1;
            ns[temp] = temp1;
            ps[temp1] = temp;
        }
    }
	//通过辅助栈s进行层次遍历
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
//find函数定义
int find(int path_l, int *fc, int *ns, int *pa)
{
    int temp = 1;//从根节点开始寻找
    int order = 0;//当前路径位置
    int error = 0;//是否非法
    while(path_l)
    {
        if(fc[temp] != -1) temp = fc[temp];//若无长子，非法，直接break，返回当前节点
        else break;
        while(path[order])
        {
            if(ns[temp] != -1) temp = ns[temp];
            else//若给出的孩子位置超过孩子个数，非法
            {
                error = 1;
                break;
            }
            path[order]--;
        }
        if(error)
		{
			temp = pa[temp];//由孩子个数引发的非法情况时，temp已经被赋值为长子，故应返回其父节点
			break;
		}
        path_l--;
        order++;
    }
    return temp;//返回最后一个合法节点
}


