#include <iostream>
#include<string>
using namespace std;

#include "SqStack.h"
#include "TSort.h"

void opeshow()
{   cout<<"*       菜           单    *"<<endl;   
	cout<<" 1. 创建图（邻接表存储结构）"<<endl;
	cout<<" 2. 拓扑排序"<<endl;	 
	cout<<" 3. 退出"<<endl;
	cout<<"请选择菜单: ";
} 

int opekind;

void main()
{
    ALGraph<string> g;
	opeshow();
	cin>>opekind;
	while(opekind>0 && opekind<4)
	{
		if (opekind==1)
		{
			g.CreateGraph();
			g.DisPlay();
		}
		else if(opekind==2)
			g.TopologicalSort();
		else
		{
			cout<<"程序运行结束，Bye-Bye!"<<endl;
			g.DestroyGraph();
		    break;
		}//if
		opeshow();
		cin>>opekind;
	}//while
}//main