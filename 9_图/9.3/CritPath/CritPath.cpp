#include <iostream>
#include <string>
#include "CritPath.h"
using namespace std;
void opeshow()
{//菜单
	cout<<"*           菜      单           *"<<endl;
	cout<<" 1. 创建有向网（图采用邻接表存储）"<<endl;
	cout<<" 2. 求关键路径"<<endl;
	cout<<" 3. 退出"<<endl;
	cout<<"请选择菜单命令: ";
}

int opekind;

void main()
{
	ALGraph<string> g;
	opeshow();
	cin>>opekind;
	while(opekind>0 && opekind<4 )
	{
		if(opekind==1)
		{
			cout<<"将创建有向网!!"<<endl;
		    g.CreateGraph();
		    g.DisPlay();
		}
		else if(opekind==2)
			g.CriticalPath();
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