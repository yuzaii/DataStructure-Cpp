#include<string> 
#include "OrLgraph.h"
#include "LinkQueue.h"
#include <iostream>
using namespace std;

template <class T>
bool visit(T v)
{
	cout<<v<<" ";
	return true;
}

void ShowOper()
{
	cout<<"请选择你要的操作"<<endl;
	cout<<"0.  建立图"<<endl;
	cout<<"1.  返回顶点v在图中的位置"<<endl;
	cout<<"2.  返回所需位置的顶点的值"<<endl;
	cout<<"3.  改变某个已知顶点v的值"<<endl;
	cout<<"4.  在图中增加新顶点v"<<endl;
	cout<<"5.  在图中删除顶点v以及所有和顶点v相关联的边或弧"<<endl;
	cout<<"6.  在图中增添一条从顶点v到顶点w的边或弧"<<endl;
	cout<<"7.  在图中删除一条从顶点v到顶点w的边或弧"<<endl;
	cout<<"8.  在图中，从第一个顶点出发深度优先遍历图"<<endl;
	cout<<"9.  在图中，从第一个顶点广度优先遍历图"<<endl;
    cout<<"10. 显示图"<<endl;
	cout<<"11. 销毁图"<<endl;
	cout<<"12. 退出"<<endl;
}
int graphkind;
int opchoice;
 
void main()
{
    int opchoice;
	OLGraph<string> g;//case0
    g.CreateGraph();
    do
	{
		ShowOper();
	    cin>>opchoice;
		switch(opchoice)
				{
				case 0:
					{
						g.CreateGraph();
						cout<<endl;
						break;
					}
					
					
				case 1:
					{
						string a;
						cout<<"请输入您要的所要查询位置的顶点的名称";
						cin>>a;
						cout<<"顶点"<<a<<"在图中的位置为"<<g.LocateVex(a)<<endl;
						cout<<endl;
						break;
					}
					
					
				case 2:
					{
						int index;
						cout<<"请输入您要的所要顶点的位置(int型)";
						cin>>index;
						cout<<"位置为"<<index<<"的顶点为"<<g.GetVex(index)<<endl;
						cout<<endl;
						break;
					}
					
				case 3:
					{
						string v(""),value("");
						cout<<"请输入您要的所要更改的顶点的值";
						cin>>v;
						cout<<"请输入您要的所要更改的顶点的新值";
						cin>>value;
						g.PutVex(v,value);
						cout<<endl;
						break;
					}
					
				case 4:
					{
						string v;
						cout<<"请输入您所要增加的顶点的值";
						cin>>v;
						g.InsertVex(v);
						cout<<endl;
						break;
					}
					
				case 5:
					{
						string v;
						cout<<"请输入您所要删除的顶点的值";
						cin>>v;
						g.DeleteVex(v);
						g.DisPlay();
						cout<<endl;
						break;
					}
					
				case 6:
					{
						string v,w;
						cout<<"请输入您所要增添一条从顶点v到顶点w的边或弧的顶点v和顶点w";
						cin>>v>>w;
						g.InsertArc(v,w);
						cout<<endl;
						break;
					}
					
				case 7:
					{
						string v,w;
						cout<<"请输入您所要删除一条从顶点v到顶点w的边或弧的顶点v和顶点w";
						cin>>v>>w;
						g.DeleteArc(v,w);
						cout<<endl;
						break;
					}
					
				case 8:
					{
						cout<<"从第一个顶点出发深度优先遍历图的序列为"<<endl;
						g.DFSTraverse(visit);
						cout<<endl;
						break;
					}
					
					 
				case 9:
					{
						cout<<"从第一个顶点出发广度优先遍历图的序列为"<<endl;
						g.BFSTraverse(visit);
						cout<<endl;
					break;
					}
					
					 
				case 10:
					{
						g.DisPlay();
						cout<<endl;
						break;
					}
					
				case 11:
					{
						g.DestroyGraph();
						cout<<endl;
						break;
					}
				case 12:
					cout<<"结束运行，Bye-Bye!"<<endl;
					break;
				default:
					cout<<"选择不合理，请重选!"<<endl;
			}//case
		}while(opchoice!=12);
}