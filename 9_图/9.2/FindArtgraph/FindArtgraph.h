/*--------------------关节点和重连通分量（图采用邻接表存储结构举例表示）----------------------*/

#include "AdjLGraph.h"
bool flg=false;//有无关节点存在标志

template <class T>
void ALGraph<T>::DFSArticul(int index)//从第index个顶点出发深度优先遍历图，找到并输出关节点
{
	int min,w;
	ArcNode *p;
	visited[index] = min = ++count; //index是第count个访问的顶点的位置
	for(p = algraph.vertices[index].firstarc;p;p = p->nextarc)
		//检查位置为index的顶点的每一个邻接顶点
	{
		w = p->adjvex; //w存放位置为index的顶点的邻接顶点的位置
		if(visited[w] == false)
			//位置为w的顶点未被访问
		{
			DFSArticul(w);//返回前求得low[w]
			if(low[w]<min)
			{
				min = low[w];
			}
			if(low[w]>=visited[index])
			{	
				flg=true;
				cout<<"顶点algraph.vertices["<<index<<"].data是一个关节点："<<" "<<algraph.vertices[index].data<<endl;//输出关节点
			}
		}
		else if(visited[w]<min)
			//w已访问，w是v0在生成树上的祖先
		{
			min = visited[w];
		}
	}
	low[index] = min;
}
	
template <class T>
void ALGraph<T>::FindArticul() //查找并输出G上全部关节点
{
	int i,index;
	ArcNode *p;
	count = 1;//初始化count为1
    low[0] = visited[0] = 1;//将位置为0的顶点设为生成树的根
	for(i = 1;i<algraph.vexnum;i++)
		//初始化尚未访问顶点的访问数组
	{
		visited[i] = 0;
	}
	p = algraph.vertices[0].firstarc;
	index = p->adjvex;
	DFSArticul(index); //从第index个顶点出发深度优先查找关节点
	if(count<algraph.vexnum)
		//生成树的根存在至少两棵子树
	{	
		flg=true;
		cout<<"根 algraph.vertices[0].data是一个关节点："<<algraph.vertices[0].data<<endl;//根是关节点，输出
		while(p->nextarc)
		{
			p = p->nextarc;
			index = p->adjvex;
			if(visited[index] == 0)
			{
				DFSArticul(index);
			}
		}
	}
}