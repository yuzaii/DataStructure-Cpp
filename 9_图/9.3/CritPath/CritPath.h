/*----------------关键路径（图采用邻接表存储结构举例表示）--------------*/

#include "AdjLGraph.h"
#include "SqStack.h"


template <class T>
bool ALGraph<T>::TopologicalOrder(SeqStack<int> &t)
// 求各顶点事件的最早发生时间ve
{
	int j,k,count,indegree[MAX_VERTEX_NUM];
	SeqStack<int> s;
	ArcNode *p;
	FindInDegree(indegree); // 对各顶点求入度indegree[] 函数被两个方法公用，所以在ALGraph.h中实现
	for(j = 0;j<algraph.vexnum;j++)
		//建立0入度栈S
	{
		if(!indegree[j])
		{
			s.Push(j);
		}
	}
	//初始化
	count = 0; 
	for(j = 0;j<algraph.vexnum;j++)
	{
		ve[j] = 0;
	}
	while(!s.IsEmpty())
		//S非空
	{
		s.Pop(j);
		t.Push(j); count++; //j号顶点入T栈并计数
		for(p = algraph.vertices[j].firstarc;p;p = p->nextarc)
			//对j号顶点的每个邻接点的入度减1
		{
			k = p->adjvex;
			if(--indegree[k] == 0)
				//入度减为0则入栈
			{
				s.Push(k);
			}
			if(ve[j] + *(p->info) >ve[k])
			{
				ve[k] = ve[j] + *(p->info);
			}
		}
	}
	if(count<algraph.vexnum)
	{
		cout<<"此有向图有回路"<<endl;
		return false;
	}
	else
	{
		return true;
	}
}

template <class T>
bool ALGraph<T>::CriticalPath()
//输出图的各项关键活动
{
	int vl[MAX_VERTEX_NUM];
	SeqStack<int> t;
	int i,j,k,ee,el,dut;
	ArcNode *p;
	char tag;
	if(!TopologicalOrder(t))
		//产生有向环
	{
		return false;
	}
	j = ve[0];
	for(i = 1;i<algraph.vexnum;i++)
		//j保存ve的最大值
	{
		if(ve[i]>j)
		{
			j = ve[i];
		}
	}
	for(i = 0;i<algraph.vexnum;i++)
		//初始化顶点时间的最迟发生时间（最大值)
	{
		vl[i] = j;//完成点的最早发生时间
	}
	while(!t.IsEmpty())
		//按拓扑逆序求各顶点的vl值
	{
		for(t.Pop(j),p = algraph.vertices[j].firstarc;p;p = p->nextarc)
		{
			k = p->adjvex;
			dut = *(p->info); //dut<j,k>
			if(vl[k]-dut<vl[j])
			{
				vl[j] = vl[k]-dut;
			}
		}
	}
	cout<<"j  k  dut  ee  el  tag"<<endl;
	for(j = 0;j<algraph.vexnum;j++)
		//求ee el和关键活动
	{
		for(p = algraph.vertices[j].firstarc;p;p = p->nextarc)
		{
			k = p->adjvex;
			dut = *(p->info);
			ee = ve[j];
			el = vl[k]-dut;
			tag = (ee == el)?'*':' ';
			cout<<j<<"  "<<k<<"  "<<dut<<"    "<<ee<<"   "<<el<<"   "<<tag<<endl;//输出关键活动
		}
	}
	cout<<"关键路径为："<<endl;
	for(j = 0;j<algraph.vexnum;j++)
		//求ee el和关键活动（同上）
	{
		for(p = algraph.vertices[j].firstarc;p;p = p->nextarc)
		{
			k = p->adjvex;
			dut = *(p->info);
			if(ve[j] == vl[k]-dut)
			{
				cout<<algraph.vertices[j].data<<"->"<<algraph.vertices[k].data<<endl;//输出关键活动
			}
		}
	}
	return true;
}