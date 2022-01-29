#include <iostream>
#include <string>
#include "AdjLGraph.h"
#include "FindArtgraph.h" 
using namespace std;

void opeshow()
{
	cout<<"*       菜           单          *"<<endl;   
	cout<<" 1. 创建图（图采用邻接表存储结构）"<<endl;
	cout<<" 2. 关节点和重连通分量"<<endl;
	cout<<" 3. 退出"<<endl;
    cout<<"请选择菜单项: ";
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
		{
			g.FindArticul();
			if (flg==false)  cout<<"此图不存在关节点"<<endl;
			cout<<"此图各顶点计算所得visited和low的函数值如下所列"<<endl;
			cout<<"i\talgraph.vertices[i].data\tvisited[i]\tlow[i]"<<endl;
			for(int i = 0;i<g.algraph.vexnum;i++)
				cout<<i<<'\t'<<g.algraph.vertices[i].data<<"\t\t\t\t"<<g.visited[i]<<"\t\t\t"<<g.low[i]<<endl;
		}
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
  
