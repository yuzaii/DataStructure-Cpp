#include <iostream>
using namespace std;
#include "ArrayGraph.h"
#include "SPath_FLOYD.h"
#include <string>

void opeshow()
{
	cout<<"*       菜      单        *"<<endl;   
	cout<<" 1. 创建图（数组存储结构）"<<endl; 
	cout<<" 2. 每一对顶点之间的最短路径"<<endl;
	cout<<" 3. 退出"<<endl;
	cout<<"请选择操作：";

}


int opekind;

void main()
{		MGraph<string> g;
		PathMatrix_2 p; // 3维数组
		DistancMatrix d; // 2维数组
		int i,j,k;

	opeshow();
	cin>>opekind;
	while(opekind>0 && opekind<4)
	{
		if (opekind==1)
		{
			cout<<"请选择有向网"<<endl;
		    g.CreateGraph();
			g.DisPlay(); // 输出有向网g
		}
		else if (opekind==2)
		{
			g.ShortestPath_FLOYD(p,d); //求每对顶点间的最短路径
			cout<<"d矩阵:"<<endl;
			for(i = 0;i<g.mgraph.vexnum;i++)
			{
				for(j = 0;j<g.mgraph.vexnum;j++)
				{
					cout<<d[i][j]<<"  ";
				}
				cout<<endl;
			}
			for(i = 0;i<g.mgraph.vexnum;i++)
			{
				for(j = 0;j<g.mgraph.vexnum;j++)
				{
					if(i != j)
						//避免同一顶点之间距离的输出
					{
						cout<<g.mgraph.vexs[i]<<"到"<<g.mgraph.vexs[j]<<"的最短距离为："<<d[i][j]<<endl;
					}
				}
			}
			cout<<"p矩阵:"<<endl;
			for(i = 0;i<g.mgraph.vexnum;i++)
			{
				for(j = 0;j<g.mgraph.vexnum;j++)
				{
					if(i != j)
					{//避免同一顶点之间距离的输出
						cout<<"由"<<g.mgraph.vexs[i]<<"到"<<g.mgraph.vexs[j]<<"经过：";
						for(k = 0;k<g.mgraph.vexnum;k++)
							if(p[i][j][k] == 1)
								cout<<g.mgraph.vexs[k]<<"  ";
						cout<<endl;
					}
				}
			}//for
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