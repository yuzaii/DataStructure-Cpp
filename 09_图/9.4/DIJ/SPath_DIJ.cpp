#include <iostream>
using namespace std;
#include "ArrayGraph.h"
#include "SPath_DIJ.h"
#include <string>

void opeshow()
{
	cout<<"*           菜           单          *"<<endl;   
	cout<<" 1. 创建图（数组存储结构）"<<endl;
	cout<<" 2. 求某个源点到其余各个顶点的最短路径"<<endl;
	cout<<" 3. 退出"<<endl;
    cout<<"请选择菜单项：";
}


int opekind;

void main()
{
	MGraph<string> g;
	int i,j;
	PathMatrix_1 p; 
	ShortPathTable d; 
	opeshow();
	cin>>opekind;
	while(opekind>0 && opekind<4)
	{
		
		if (opekind==1)
		{
			cout<<"请选择有向网"<<endl;
		    g.CreateGraph();
			g.DisPlay(); 
		}
		else if(opekind==2)
		{
			g.ShortestPath_DIJ(0,p,d);
		    cout<<"最短路径数组p[i][j]如下: "<<endl;
	        for(i = 0;i<g.mgraph.vexnum;i++)
			{
			   for(j = 0;j<g.mgraph.vexnum;j++)
			   	  cout<<p[i][j]<<" ";
				cout<<endl;
			}
			cout<<g.mgraph.vexs[0]<<"到各顶点的最短路径长度为："<<endl;
			for(i = 1;i<g.mgraph.vexnum;i++)
				if(d[i]==INT_MAX)
                   cout<<g.mgraph.vexs[0]<<"-"<<g.mgraph.vexs[i]<<": ∞"<<endl;
				else
				   cout<<g.mgraph.vexs[0]<<"-"<<g.mgraph.vexs[i]<<":"<<d[i]<<endl;
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