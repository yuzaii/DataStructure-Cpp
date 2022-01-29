#include <iostream>
#include <string> 
#include "DFSForest.h"

using namespace std; 

void opeshow()
{
	cout<<" 1. 创建无向图（图采用邻接表存储结构举例表示）"<<endl; 
	cout<<" 2. 求生成树或森林/连通分量"<<endl;
	cout<<" 3. 退出"<<endl;
	cout<<"  请选择菜单项: ";
}

int opekind;
void main()
{
	ALGraph<string> g;
	CSTree<string> *t;
	opeshow();
	cin>>opekind;
	while(opekind > 0 && opekind < 4)
	{
		if (opekind==1)
		{ 
				cout<<"请选择无向图"<<endl;
				//ALGraph<string> g;
				g.CreateGraph();
				//CSTree<string> *t;
				g.DisPlay();
		}
		else if(opekind==2)
		{
			g.DFSForest(t);
			g.BTreetoForest(t);
		}
		else 
		{   
			g.DestroyGraph();
			cout<<"程序运行结束，Bye-Bye!"<<endl;
			break; }
		cout<<endl;
		opeshow();
		cin>>opekind;
	}

}
