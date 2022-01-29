#include <iostream>
#include <string>
using namespace std;
#include "Minitree_prim.h"
 
void opeshow()
{
	cout<<"  1. 无向网的创建(采用数组存储结构）"<<endl; 
	cout<<"  2. 求最小生成数(Pirm算法)"<<endl;
	cout<<"  3. 退出"<<endl;
	cout<<"请选择菜单项：";
}
int opekind;
void main()
{	
	MGraph<string> g;
	string u;
	opeshow();
    cin>>opekind;
	while(opekind>0 && opekind<4)
	{
	   if (opekind==1)
	   {
		   g.CreateUDN();
		   g.DisPlay();}
	   else if (opekind==2)
	   {
		   cout<<"请输入您所需要的用普利姆算法生成最小生成树的出发顶点u:"<<endl;
           cin>>u;
	       g.MiniSpanTree_PRIM(u);
	   }
       else
	   {
		   g.DestroyGraph();
	       cout<<endl; 
	       cout<<"程序运行结束，Bye-Bye!"<<endl;
	       break;
	   }
	   opeshow();
	   cin>>opekind;
	  }
}
