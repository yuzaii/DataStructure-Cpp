#include<string> 
#include "OrLgraph.h"
 
#include <iostream>
using namespace std;

void opeshow()
{
	cout<<"  1. 创建有向图（图采用十字链表存储结构举例表示）"<<endl; 
	cout<<"  2. 求图强连通分量"<<endl;
	cout<<"  3. 退出"<<endl;
	cout<<"请选择菜单项: ";
}
int opekind;
void main()
{
 OLGraph<string> G;
 opeshow();
	cin>>opekind;
	while(opekind>0 && opekind < 4)
	{
		if (opekind==1)
		{ 
				 
           G.CreateGraph();
		   G.DisPlay();
		   cout<<endl; 
          }
		else if ( opekind==2)
		{
			G.Get_SGraph( );//求十字链表结构储存的有向图G的强连通分量
           cout<<endl;
		}
		else
		{	G.DestroyGraph();
			cout<<"程序运行结束，Bye-Bye!"<<endl;	 
			break;
		}//if
				cout<<endl;
				opeshow();
				cin>>opekind;
	}//while
		 
}
 
